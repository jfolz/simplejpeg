# cython: language_level=3
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


cdef COLORSPACES = {
    'rgb': TJPF_RGB,
    'bgr': TJPF_BGR,
    'rgbx': TJPF_RGBX,
    'bgrx': TJPF_BGRX,
    'xbgr': TJPF_XBGR,
    'xrgb': TJPF_XRGB,
    'gray': TJPF_GRAY,
    'rgba': TJPF_RGBA,
    'bgra': TJPF_BGRA,
    'abgr': TJPF_ABGR,
    'argb': TJPF_ARGB,
    'cmyk': TJPF_CMYK,
}


cdef COLORSPACE_NAMES = {
    TJPF_RGB: 'rgb',
    TJPF_BGR: 'bgr',
    TJPF_RGBX: 'rgbx',
    TJPF_BGRX: 'bgrx',
    TJPF_XBGR: 'xbgr',
    TJPF_XRGB: 'xrgb',
    TJPF_GRAY: 'gray',
    TJPF_RGBA: 'rgba',
    TJPF_BGRA: 'bgra',
    TJPF_ABGR: 'abgr',
    TJPF_ARGB: 'argb',
    TJPF_CMYK: 'cmyk',
}


cdef SUBSAMPLING_NAMES = {
    TJSAMP_444: '444',
    TJSAMP_422: '422',
    TJSAMP_420: '420',
    TJSAMP_GRAY: 'gray',
    TJSAMP_440: '440',
    TJSAMP_411: '411',
}


cdef __tj_error(tjhandle decoder_):
    cdef char * error = tjGetErrorStr2(decoder_)
    if error == NULL:
        return 'unknown JPEG error'
    else:
        return error.decode('UTF-8', 'replace')


@cython.cdivision(True)
def decode_jpeg_header(const unsigned char[:] data not None):
    """
    Decode the header of a JPEG image.
    Returns height and width as pixels
    and colorspace and subsampling as strings.

    :param data: JPEG data
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

    return (
        height,
        width,
        COLORSPACE_NAMES[jpegColorspace],
        SUBSAMPLING_NAMES[jpegSubsamp],
    )


@cython.cdivision(True)
def decode_jpeg(
        const unsigned char[:] data not None,
        colorspace='rgb',
        fastdct=True,
        fastupsample=True,
        min_height=0,
        min_width=0,
        min_factor=2,
):
    """
    Decode a JPEG image into a numpy array.

    :param data: JPEG data
    :param colorspace: target colorspace, any of the following:
                       'rgb', 'bgr', 'rgbx', 'bgrx', 'xbgr', 'xrgb',
                       'gray', 'rgba', 'bgra', 'abgr', 'argb', 'cmyk'
    :param fastdct: If True, use fastest DCT method
    :param fastupsample: If True, use fast color upsampling
    :param min_height: decode image to greater than this minimum
                       height in pixels
    :param min_width: decode image to greater than this minimum
                      width in pixels
    :param min_factor: minimum scaling factor when decoding to smaller
                       size; factors smaller than 2 may be slower to
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
    cdef int min_height_ = min_height
    cdef int min_width_ = min_width
    cdef int min_factor_ = min_factor

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

    # find the minimum scaling factor that satisfies
    # both min_width and min_height (if given).
    cdef int numscalingfactors
    cdef tjscalingfactor * factors = tjGetScalingFactors(&numscalingfactors)
    cdef tjscalingfactor fac
    cdef int f = -1
    min_height_ = min(height, min_height_ or height)
    min_width_ = min(width, min_width_ or width)
    if min_height_ > 0 or min_width_ > 0:
        for f in range(numscalingfactors-1, -1, -1):
            fac = factors[f]
            if fac.num == fac.denom:
                break
            if TJSCALED(width, fac) >= min_width_ \
            and TJSCALED(height, fac) >= min_height_:
                break
    # recalculate output width and height if scale factor was found
    # and it is larger than min_factor
    if f >= 0 and fac.denom / fac.num > min_factor_:
        width = TJSCALED(width, fac)
        height = TJSCALED(height, fac)

    # create the output array
    cdef int colorspace_ = COLORSPACES[colorspace]
    cdef np.npy_intp * dims = [height, width, tjPixelSize[colorspace_]]
    cdef np.ndarray[np.uint8_t, ndim = 3] out = np.PyArray_EMPTY(3, dims, np.NPY_UINT8, 0)
    #cdef np.ndarray[np.uint8_t, ndim = 3] out = np.empty(
    #        (height, width, tjPixelSize[colorspace_]),
    #        np.uint8
    #    )
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
