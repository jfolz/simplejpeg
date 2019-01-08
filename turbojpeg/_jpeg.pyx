# cython: language_level=3
# cython: embedsignature=True
from __future__ import print_function, division, unicode_literals

import cython
import numpy as np
cimport numpy as np


np.import_array()


cdef extern from "turbojpeg.h" nogil:
    ctypedef void* tjhandle

    cdef int TJCS_RGB
    cdef int TJCS_YCbCr
    cdef int TJCS_GRAY
    cdef int TJCS_CMYK
    cdef int TJCS_YCCK

    cdef int TJPF_RGB
    cdef int TJPF_BGR
    cdef int TJPF_RGBX
    cdef int TJPF_BGRX
    cdef int TJPF_XBGR
    cdef int TJPF_XRGB
    cdef int TJPF_GRAY
    cdef int TJPF_RGBA
    cdef int TJPF_BGRA
    cdef int TJPF_ABGR
    cdef int TJPF_ARGB
    cdef int TJPF_CMYK
    cdef int TJPF_UNKNOWN

    cdef int TJSAMP_444
    cdef int TJSAMP_422
    cdef int TJSAMP_420
    cdef int TJSAMP_GRAY
    cdef int TJSAMP_440
    cdef int TJSAMP_411

    cdef tjhandle tjInitDecompress()

    cdef int tjDecompressHeader3(
        tjhandle handle,
        const unsigned char * jpegBuf,
        unsigned long jpegSize,
        int * width,
        int * height,
        int * jpegSubsamp,
        int * jpegColorspace
    )

    cdef int tjDecompress2(
        tjhandle handle,
        const unsigned char * jpegBuf,
        unsigned long jpegSize,
        unsigned char * dstBuf,
        int width,
        int pitch,
        int height,
        int pixelFormat,
        int flags
    )

    cdef char* tjGetErrorStr2(tjhandle handle)

    cdef const int* tjPixelSize

    cdef int TJPAD(int width)

    cdef int tjDestroy(tjhandle handle)

    cdef int TJFLAG_NOREALLOC
    cdef int TJFLAG_FASTDCT
    cdef int TJFLAG_FASTUPSAMPLE

    ctypedef struct tjscalingfactor:
        int num
        int denom

    cdef tjscalingfactor* tjGetScalingFactors(int* numscalingfactors)

    cdef int TJSCALED(int dimension, tjscalingfactor scalingFactor)


cdef _cnames = ['RGB', 'YCbCr', 'Gray', 'CMYK', 'YCCK']
cdef _cs = [TJCS_RGB, TJCS_YCbCr, TJCS_GRAY, TJCS_CMYK, TJCS_YCCK]
cdef COLORSPACES = {}
for c, i in zip(_cnames, _cs):
    COLORSPACES[c] = i
    COLORSPACES[c.lower()] = i
    COLORSPACES[c.upper()] = i
    c = c.encode('utf-8')
    COLORSPACES[c] = i
    COLORSPACES[c.lower()] = i
    COLORSPACES[c.upper()] = i
cdef COLORSPACE_NAMES = {
    i: c for i, c in zip(_cs, _cnames)
}


cdef _snames = ['444', '422', '420', 'Gray', '440', '411',]
cdef _ss = [
    TJSAMP_444, TJSAMP_422, TJSAMP_420, TJSAMP_GRAY, TJSAMP_440, TJSAMP_411
]
SUBSAMPLING_NAMES = {
    sub: name for name, sub in zip(_snames, _ss)
}


cdef _pfnames = [
'RGB',
'BGR',
'RGBX',
'BGRX',
'XBGR',
'XRGB',
'Gray',
'RGBA',
'BGRA',
'ABGR',
'ARGB',
'CMYK',
]
cdef _pfs = [
    TJPF_RGB,
    TJPF_BGR,
    TJPF_RGBX,
    TJPF_BGRX,
    TJPF_XBGR,
    TJPF_XRGB,
    TJPF_GRAY,
    TJPF_RGBA,
    TJPF_BGRA,
    TJPF_ABGR,
    TJPF_ARGB,
    TJPF_CMYK,
]
cdef PIXELFORMATS = {}
for name, pf in zip(_pfnames, _pfs):
    PIXELFORMATS[name] = pf
    PIXELFORMATS[name.lower()] = pf
    PIXELFORMATS[name.upper()] = pf
    name = name.encode('utf-8')
    PIXELFORMATS[name] = pf
    PIXELFORMATS[name.lower()] = pf
    PIXELFORMATS[name.upper()] = pf


cdef __tj_error(tjhandle decoder_):
    cdef char * error = tjGetErrorStr2(decoder_)
    if error == NULL:
        return 'unknown JPEG error'
    else:
        return error.decode('UTF-8', 'replace')


@cython.cdivision(True)
cdef void calc_height_width(
        int* height,
        int* width,
        int min_height,
        int min_width,
        float min_factor,
):
    # find the minimum scaling factor that satisfies
    # both min_width and min_height (if given).
    cdef int numscalingfactors
    cdef tjscalingfactor * factors = tjGetScalingFactors( & numscalingfactors)
    cdef tjscalingfactor fac
    cdef int f = -1
    cdef int height_ = height[0]
    cdef int width_ = width[0]
    min_height = min(height_, min_height or height_)
    min_width = min(width_, min_width or width_)
    if min_height > 0 or min_width > 0:
        for f in range(numscalingfactors - 1, -1, -1):
            fac = factors[f]
            if fac.num == fac.denom:
                break
            if TJSCALED(width_, fac) >= min_width \
                    and TJSCALED(height_, fac) >= min_height:
                break
    # recalculate output width and height if scale factor was found
    # and it is larger than min_factor
    if f >= 0 and fac.denom >= min_factor * fac.num:
        height[0] = TJSCALED(height_, fac)
        width[0] = TJSCALED(width_, fac)


def decode_jpeg_header(
        const unsigned char[:] data not None,
        int min_height=0,
        int min_width=0,
        float min_factor=1,
):
    """
    Decode the header of a JPEG image.
    Returns height and width as pixels
    and colorspace and subsampling as strings.

    :param data: JPEG data
    :param min_height:
    :param min_width:
    :return: height, width, colorspace, color subsampling
    """
    cdef tjhandle decoder_ = tjInitDecompress()
    if decoder_ == NULL:
        raise RuntimeError('could not create JPEG decoder')

    cdef const unsigned char* data_p = &data[0]
    cdef unsigned long data_len = len(data)
    cdef int retcode
    cdef int width
    cdef int height
    cdef int jpegSubsamp
    cdef int jpegColorspace
    with nogil:
        retcode = tjDecompressHeader3(
            decoder_,
            data_p,
            data_len,
            &width,
            &height,
            &jpegSubsamp,
            &jpegColorspace
        )

    if retcode != 0:
        tjDestroy(decoder_)
        raise ValueError(__tj_error(decoder_))

    tjDestroy(decoder_)

    calc_height_width(&height, &width, min_height, min_width, min_factor)

    return (
        height,
        width,
        COLORSPACE_NAMES[jpegColorspace],
        SUBSAMPLING_NAMES[jpegSubsamp],
    )

def decode_jpeg(
        const unsigned char[:] data not None,
        colorspace='rgb',
        bint fastdct=True,
        bint fastupsample=True,
        int min_height=0,
        int min_width=0,
        float min_factor=2,
):
    """
    Decode a JPEG image into a numpy array.

    :param data: JPEG data
    :param colorspace: target colorspace, any of the following:
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'
    :param fastdct: If True, use fastest DCT method;
                    usually no observable difference
    :param fastupsample: If True, use fastest color upsampling method;
                         usually no observable difference
    :param min_height: output height should be >= this minimum
                       height in pixels; values <= 0 are ignored
    :param min_width: output width should be >= this minimum
                      width in pixels; values <= 0 are ignored
    :param min_factor: minimum scaling factor when decoding to smaller
                       size; factors smaller than 2 may take longer to
                       decode
    """
    cdef tjhandle decoder_ = tjInitDecompress()
    if decoder_ == NULL:
        raise RuntimeError('could not create JPEG decoder')

    cdef const unsigned char* data_p = &data[0]
    cdef unsigned long data_len = len(data)
    cdef int retcode
    cdef int width
    cdef int height

    # get metadata
    cdef int jpegSubsamp
    cdef int jpegColorspace
    with nogil:
        retcode = tjDecompressHeader3(
            decoder_,
            data_p,
            data_len,
            &width,
            &height,
            &jpegSubsamp,
            &jpegColorspace
        )

    if retcode != 0:
        tjDestroy(decoder_)
        raise ValueError(__tj_error(decoder_))

    calc_height_width(&height, &width, min_height, min_width, min_factor)

    # create the output array
    cdef int colorspace_ = PIXELFORMATS[colorspace]
    cdef np.npy_intp * dims = [height, width, tjPixelSize[colorspace_]]
    cdef np.ndarray[np.uint8_t, ndim = 3] out = np.PyArray_EMPTY(3, dims, np.NPY_UINT8, 0)
    cdef unsigned char* out_p = <unsigned char*> out.data

    # combine flags
    # TJFLAG_NOREALLOC = the output buffer is managed by numpy,
    #                    do not attempt to reallocate
    # TJFLAG_FASTDCT = use fastest DCT method
    # TJFLAG_FASTUPSAMPLE = use fastest color upsampling method
    cdef int flags = TJFLAG_NOREALLOC
    if fastdct:
        flags |= TJFLAG_FASTDCT
    if fastupsample:
        flags |= TJFLAG_FASTUPSAMPLE

    # decompress the image
    with nogil:
        retcode = tjDecompress2(
            decoder_,
            data_p,
            data_len,
            out_p,
            width,
            0,
            height,
            colorspace_,
            flags
        )

    if retcode != 0:
        tjDestroy(decoder_)
        raise ValueError(__tj_error(decoder_))

    tjDestroy(decoder_)
    return out
