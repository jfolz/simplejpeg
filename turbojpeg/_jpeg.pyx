# cython: language_level=3
# cython: embedsignature=True
# cython: boundscheck=False
from __future__ import print_function, division, unicode_literals

import cython
import numpy as np
cimport numpy as np
from cpython.bytes cimport PyBytes_FromStringAndSize


np.import_array()


cdef extern from "turbojpeg.h" nogil:
    ctypedef void* tjhandle

    # TJ colorspace constants
    cdef int TJCS_RGB, TJCS_YCbCr, TJCS_GRAY, TJCS_CMYK, TJCS_YCCK

    # TJ pixel format constants
    cdef int TJPF_RGB, TJPF_BGR, TJPF_RGBX, TJPF_BGRX, TJPF_XBGR, TJPF_XRGB
    cdef int TJPF_GRAY, TJPF_RGBA, TJPF_BGRA, TJPF_ABGR, TJPF_ARGB, TJPF_CMYK
    cdef int TJPF_UNKNOWN

    # TJ color subsampling constants
    cdef int TJSAMP_444, TJSAMP_422, TJSAMP_420
    cdef int TJSAMP_GRAY, TJSAMP_440, TJSAMP_411

    # TJ encoding/decoding flags
    cdef int TJFLAG_NOREALLOC, TJFLAG_FASTDCT, TJFLAG_FASTUPSAMPLE

    cdef tjhandle tjInitDecompress()

    cdef tjhandle tjInitCompress()

    cdef void tjFree (unsigned char * buffer)

    cdef int tjDestroy(tjhandle handle)

    cdef char* tjGetErrorStr2(tjhandle handle)

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

    cdef int tjCompress2(
        tjhandle  handle,
		const unsigned char * srcBuf,
		int width,
		int pitch,
		int height,
		int pixelFormat,
		unsigned char ** jpegBuf,
		unsigned long * jpegSize,
		int jpegSubsamp,
		int jpegQual,
		int flags
	)

    cdef const int* tjPixelSize

    cdef int TJPAD(int width)

    ctypedef struct tjscalingfactor:
        int num
        int denom

    cdef tjscalingfactor* tjGetScalingFactors(int* numscalingfactors)

    cdef int TJSCALED(int dimension, tjscalingfactor scalingFactor)


# Create a dict that maps colorspace names to TJ constants.
# Add different cases for convenience.
cdef _cnames = ['RGB', 'YCbCr', 'Gray', 'CMYK', 'YCCK']
cdef _cconst = [TJCS_RGB, TJCS_YCbCr, TJCS_GRAY, TJCS_CMYK, TJCS_YCCK]
cdef COLORSPACES = {}
for name, i in zip(_cnames, _cconst):
    COLORSPACES[name] = i
    COLORSPACES[name.lower()] = i
    COLORSPACES[name.upper()] = i
cdef COLORSPACE_NAMES = {i: c for i, c in zip(_cconst, _cnames)}


# Create a dict that maps TJ constants to colorspace names.
cdef _snames = ['444', '422', '420', 'Gray', '440', '411',]
cdef _sconst = [TJSAMP_444, TJSAMP_422, TJSAMP_420,
                TJSAMP_GRAY, TJSAMP_440, TJSAMP_411]
cdef SUBSAMPLING = {}
for name, sub in zip(_snames, _sconst):
    SUBSAMPLING[name] = sub
    SUBSAMPLING[name.lower()] = sub
    SUBSAMPLING[name.upper()] = sub
cdef SUBSAMPLING_NAMES = {sub: name for name, sub in zip(_snames, _sconst)}


# Create a dict that maps pixel formats names to TJ constants.
# Add different cases for convenience.
cdef _pfnames = ['RGB', 'BGR', 'RGBX', 'BGRX',
                 'XBGR', 'XRGB', 'Gray', 'RGBA',
                 'BGRA', 'ABGR', 'ARGB', 'CMYK']
cdef _pfconst = [TJPF_RGB, TJPF_BGR, TJPF_RGBX, TJPF_BGRX,
                 TJPF_XBGR, TJPF_XRGB, TJPF_GRAY, TJPF_RGBA,
                 TJPF_BGRA, TJPF_ABGR, TJPF_ARGB, TJPF_CMYK]
cdef PIXELFORMATS = {}
for name, pf in zip(_pfnames, _pfconst):
    PIXELFORMATS[name] = pf
    PIXELFORMATS[name.lower()] = pf
    PIXELFORMATS[name.upper()] = pf


cdef str __tj_error(tjhandle decoder_):
    '''
    Extract the error message created by TJ.
    '''
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
) nogil:
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
    Returns height and width in pixels
    and colorspace and subsampling as string.

    :param data: JPEG data
    :param min_height: height should be >= this minimum
                       height in pixels; values <= 0 are ignored
    :param min_width: width should be >= this minimum
                      width in pixels; values <= 0 are ignored
    :param min_factor: minimum scaling factor when decoding to smaller
                       size; factors smaller than 2 may take longer to
                       decode; default 1
    :return: height, width, colorspace, color subsampling
    """
    cdef const unsigned char* data_p = &data[0]
    cdef unsigned long data_len = len(data)
    cdef int retcode
    cdef int width
    cdef int height
    cdef int jpegSubsamp
    cdef int jpegColorspace
    cdef tjhandle decoder
    with nogil:
        decoder = tjInitDecompress()
        if decoder == NULL:
            raise RuntimeError('could not create JPEG decoder')
        retcode = tjDecompressHeader3(
            decoder,
            data_p,
            data_len,
            &width,
            &height,
            &jpegSubsamp,
            &jpegColorspace
        )
        if retcode != 0:
            tjDestroy(decoder)
            raise ValueError(__tj_error(decoder))
        tjDestroy(decoder)
        calc_height_width(&height, &width, min_height, min_width, min_factor)
    return (
        height,
        width,
        COLORSPACE_NAMES[jpegColorspace],
        SUBSAMPLING_NAMES[jpegSubsamp],
    )


def decode_jpeg(
        const unsigned char[:] data not None,
        str colorspace='rgb',
        bint fastdct=True,
        bint fastupsample=True,
        int min_height=0,
        int min_width=0,
        float min_factor=1,
):
    """
    Decode a JPEG (JFIF) string.
    Returns a numpy array.

    :param data: JPEG data
    :param colorspace: target colorspace, any of the following:
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
                       'CMYK' may be used for images already in CMYK space.
    :param fastdct: If True, use fastest DCT method;
                    usually no observable difference
    :param fastupsample: If True, use fastest color upsampling method;
                         usually no observable difference
    :param min_height: height should be >= this minimum in pixels;
                       values <= 0 are ignored
    :param min_width: width should be >= this minimum in pixels;
                      values <= 0 are ignored
    :param min_factor: minimum scaling factor (original size / decoded size);
                       factors smaller than 2 may take longer to decode;
                       default 1
    :return: image as numpy array
    """
    cdef const unsigned char* data_p = &data[0]
    cdef unsigned long data_len = len(data)
    cdef int retcode
    cdef int width
    cdef int height
    cdef int jpegSubsamp
    cdef int jpegColorspace
    cdef tjhandle decoder
    with nogil:
        decoder = tjInitDecompress()
        if decoder == NULL:
            raise RuntimeError('could not create JPEG decoder')
        retcode = tjDecompressHeader3(
            decoder,
            data_p,
            data_len,
            &width,
            &height,
            &jpegSubsamp,
            &jpegColorspace
        )
        if retcode != 0:
            tjDestroy(decoder)
            raise ValueError(__tj_error(decoder))
        calc_height_width(&height, &width, min_height, min_width, min_factor)

    # create the output array
    cdef int colorspace_ = PIXELFORMATS[colorspace]
    cdef np.npy_intp * dims = [height, width, tjPixelSize[colorspace_]]
    cdef np.ndarray[np.uint8_t, ndim = 3] out = np.PyArray_EMPTY(3, dims, np.NPY_UINT8, 0)
    cdef int flags
    with nogil:
        flags = TJFLAG_NOREALLOC
        if fastdct:
            flags |= TJFLAG_FASTDCT
        if fastupsample:
            flags |= TJFLAG_FASTUPSAMPLE
        # decompress the image
        retcode = tjDecompress2(
            decoder,
            data_p,
            data_len,
            &out[0, 0, 0],
            width,
            0,
            height,
            colorspace_,
            flags
        )
        if retcode != 0:
            tjDestroy(decoder)
            raise ValueError(__tj_error(decoder))
        tjDestroy(decoder)
    return out


def encode_jpeg(
        const unsigned char[:, :, :] image not None,
        int quality=85,
        str colorspace='rgb',
        str colorsubsampling='444',
        bint fastdct=True,
):
    """
    Encode an image to JPEG (JFIF) string.
    Returns JPEG (JFIF) data.

    :param data: uncompressed image
    :param colorspace: source colorspace, any of the following:
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.
    :param fastdct: If True, use fastest DCT method;
                    usually no observable difference
    :return: encoded image as JPEG (JFIF) data
    """
    cdef const unsigned char* image_p = &image[0, 0, 0]
    cdef int retcode
    cdef int height = image.shape[0]
    cdef int width = image.shape[1]
    cdef int channels = image.shape[2]
    cdef int colorspace_ = PIXELFORMATS[colorspace]
    if tjPixelSize[colorspace_] != channels:
        raise ValueError('%d channels does not match given colorspace %s'
                         % (channels, colorspace))
    cdef int colorsubsampling_ = SUBSAMPLING[colorsubsampling]
    cdef unsigned char * jpegbuf = NULL
    cdef unsigned char ** jpegbufbuf = &jpegbuf
    cdef unsigned long jpegsize = 0
    cdef int flags
    cdef tjhandle encoder
    with nogil:
        encoder = tjInitCompress()
        if encoder == NULL:
            raise RuntimeError('could not create JPEG encoder')
        flags = 0
        if fastdct:
            flags |= TJFLAG_FASTDCT
        retcode = tjCompress2(
            encoder,
            image_p,
            width,
            0,
            height,
            colorspace_,
            jpegbufbuf,
            &jpegsize,
            colorsubsampling_,
            quality,
            flags
        )
        if retcode != 0:
            tjDestroy(encoder)
            raise ValueError(__tj_error(encoder))
    jpeg = PyBytes_FromStringAndSize(<char *> jpegbuf, jpegsize)
    tjFree(jpegbuf)
    tjDestroy(encoder)
    return jpeg
