# cython: language_level=3
# cython: embedsignature=False
# cython: boundscheck=False
from __future__ import print_function, division, unicode_literals

import cython
import numpy as np
cimport numpy as np
from cpython.bytes cimport PyBytes_FromStringAndSize
from cpython cimport PyObject_GetBuffer
from cpython cimport PyBUF_SIMPLE
from cpython cimport PyBUF_WRITABLE
from cpython cimport PyBUF_ANY_CONTIGUOUS
from cpython cimport PyBuffer_Release


np.import_array()


cdef extern from "turbojpeg.h" nogil:
    ctypedef void* tjhandle

    # TJ colorspace constants
    cdef int TJCS_RGB, TJCS_YCbCr, TJCS_GRAY, TJCS_CMYK, TJCS_YCCK

    # TJ pixel format constants
    cdef int TJPF_RGB, TJPF_BGR, TJPF_RGBX, TJPF_BGRX
    cdef int TJPF_XBGR, TJPF_XRGB, TJPF_GRAY, TJPF_RGBA
    cdef int TJPF_BGRA, TJPF_ABGR, TJPF_ARGB, TJPF_CMYK
    cdef int TJPF_UNKNOWN

    # TJ color subsampling constants
    cdef int TJSAMP_444, TJSAMP_422, TJSAMP_420
    cdef int TJSAMP_GRAY, TJSAMP_440, TJSAMP_411
    cdef int TJSAMP_UNKNOWN, TJ_NUMSAMP

    # TJ encoding/decoding flags
    cdef int TJFLAG_NOREALLOC, TJFLAG_FASTDCT, TJFLAG_FASTUPSAMPLE

    # TJ error enum
    cdef int TJERR_WARNING, TJERR_FATAL

    cdef tjhandle tjInitDecompress()

    cdef tjhandle tjInitCompress()

    cdef void tjFree (unsigned char * buffer)

    cdef int tjDestroy(tjhandle handle)

    cdef int tjGetErrorCode(tjhandle handle)

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

    cdef int tjCompressFromYUVPlanes(
        tjhandle handle,
        const unsigned char **srcPlanes,
        int width,
        const int *strides,
        int height,
        int jpegSubsamp,
        unsigned char ** jpegBuf,
        unsigned long * jpegSize,
        int jpegQual,
        int flags
    )

    cdef const int* tjPixelSize

    ctypedef struct tjscalingfactor:
        int num
        int denom

    cdef tjscalingfactor* tjGetScalingFactors(int* numscalingfactors)

    cdef int TJSCALED(int dimension, tjscalingfactor scalingFactor)


cdef extern from "_color.h" nogil:
    cdef void cmyk2gray(unsigned char* cmyk, unsigned char* out, int npixels)
    cdef void cmyk2color(unsigned char* cmyk, unsigned char* out,
                         int npixels, int pixelformat)


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
cdef _snames = ['444', '422', '420', 'Gray', '440', '411']
cdef _sconst = [TJSAMP_444, TJSAMP_422, TJSAMP_420,
                TJSAMP_GRAY, TJSAMP_440, TJSAMP_411]
cdef SUBSAMPLING = {}
for name, sub in zip(_snames, _sconst):
    SUBSAMPLING[name] = sub
    SUBSAMPLING[name.lower()] = sub
    SUBSAMPLING[name.upper()] = sub
# add 'unknown' in case tjDecompressHeader3 cannot determine subsampling
_snames.append('unknown')
_sconst.append(TJ_NUMSAMP)
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
) noexcept nogil:
    # find the minimum scaling factor that satisfies
    # both min_width and min_height (if given).
    cdef int numscalingfactors
    cdef tjscalingfactor* factors = tjGetScalingFactors(&numscalingfactors)
    cdef tjscalingfactor fac
    cdef int f = -1
    cdef int height_ = height[0]
    cdef int width_ = width[0]
    min_height = min(height_, min_height)
    min_width = min(width_, min_width)
    if min_height > 0 or min_width > 0:
        for f in range(numscalingfactors-1, -1, -1):
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
        bint strict=True,
):
    """
    Decode the header of a JPEG image.
    Returns height and width in pixels
    and colorspace and subsampling as string.

    Parameters:
        data: JPEG data
        min_height: height should be >= this minimum
                    height in pixels; values <= 0 are ignored
        min_width: width should be >= this minimum
                   width in pixels; values <= 0 are ignored
        min_factor: minimum scaling factor when decoding to smaller
                    ize; factors smaller than 2 may take longer to
                    decode; default 1
        strict: if True, raise ValueError for recoverable errors;
                default True

    Returns:
        height, width, colorspace, color subsampling
    """
    cdef const unsigned char* data_p = &data[0]
    cdef unsigned long data_len = len(data)
    cdef int retcode
    cdef int width = -1
    cdef int height = -1
    cdef int jpegSubsamp = -1
    cdef int jpegColorspace = -1
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
        if retcode != 0 and (strict or tjGetErrorCode(decoder) == TJERR_FATAL):
            with gil:
                msg = __tj_error(decoder)
                tjDestroy(decoder)
                raise ValueError(msg)
        tjDestroy(decoder)
        calc_height_width(&height, &width, min_height, min_width, min_factor)
    return (
        height,
        width,
        COLORSPACE_NAMES[jpegColorspace],
        SUBSAMPLING_NAMES[jpegSubsamp],
    )


cdef int DECODE_BUFFER_FLAGS = PyBUF_SIMPLE|PyBUF_WRITABLE|PyBUF_ANY_CONTIGUOUS


def decode_jpeg(
        const unsigned char[:] data not None,
        str colorspace='rgb',
        bint fastdct=False,
        bint fastupsample=False,
        int min_height=0,
        int min_width=0,
        float min_factor=1,
        buffer=None,
        bint strict=True,
):
    """
    Decode a JPEG (JFIF) string.
    Returns a numpy array.

    Parameters:
        data: JPEG data
        colorspace: target colorspace, any of the following:
                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
                   'CMYK' may be used for images already in CMYK space.
        fastdct: If True, use fastest DCT method;
                 speeds up decoding by 4-5% for a minor loss in quality
        fastupsample: If True, use fastest color upsampling method;
                      speeds up decoding by 4-5% for a minor loss
                      in quality
        min_height: height should be >= this minimum in pixels;
                    values <= 0 are ignored
        min_width: width should be >= this minimum in pixels;
                   values <= 0 are ignored
        min_factor: minimum scaling factor (original size / decoded size);
                    factors smaller than 2 may take longer to decode;
                    default 1
        buffer: use given object as output buffer;
                must support the buffer protocol and be writable, e.g.,
                numpy ndarray or bytearray;
                use decode_jpeg_header to find out required minimum size
                if image dimensions are unknown
        strict: if True, raise ValueError for recoverable errors;
                default True

    Returns:
        image as numpy array
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
            with gil:
                msg = __tj_error(decoder)
                tjDestroy(decoder)
                raise ValueError(msg)
        calc_height_width(&height, &width, min_height, min_width, min_factor)

    # get colorspace constants
    cdef int tmp_colorspace = PIXELFORMATS[colorspace]
    cdef int output_colorspace = PIXELFORMATS[colorspace]
    cdef bint is_cmyk = 0
    # check whether JPEG is in CMYK/YCCK colorspace
    if jpegColorspace == TJCS_CMYK or jpegColorspace == TJCS_YCCK:
        tmp_colorspace = TJPF_CMYK
        is_cmyk = 1

    # some variables that may be needed
    cdef np.npy_intp outlen = height * width * tjPixelSize[output_colorspace]
    cdef np.ndarray[np.uint8_t, ndim = 3] tmp
    cdef np.ndarray[np.uint8_t, ndim = 3] out
    cdef unsigned char* tmp_p
    cdef unsigned char* out_p
    cdef Py_buffer view
    cdef np.npy_intp bufferlen = 0

    # no buffer is given, make new output array
    cdef np.npy_intp * dims = [height, width, tjPixelSize[output_colorspace]]
    if buffer is None:
        out = np.PyArray_EMPTY(3, dims, np.NPY_UINT8, 0)
        out_p = &out[0, 0, 0]
    # attempt to create output array from given buffer
    else:
        if PyObject_GetBuffer(buffer, &view, DECODE_BUFFER_FLAGS) != 0:
            raise ValueError('buffer object must support buffer interface '
                             'and must be writable and contiguous')
        # check memoryview size and extract pointer
        bufferlen = view.len
        if bufferlen < outlen:
            PyBuffer_Release(&view)
            raise ValueError('%d byte buffer is too small to decode (%d, %d, %d) image'
                             % (bufferlen, height, width, tjPixelSize[output_colorspace]))
        out = np.frombuffer(
            buffer, np.uint8, outlen
        ).reshape((height, width, tjPixelSize[output_colorspace]))
        out_p = <unsigned char*> view.buf
        PyBuffer_Release(&view)

    # if temp is not output colorspace temporary array must be created
    if tmp_colorspace != output_colorspace:
        dims[:] = [height, width, tjPixelSize[tmp_colorspace]]
        tmp = np.PyArray_EMPTY(3, dims, np.NPY_UINT8, 0)
        tmp_p = &tmp[0, 0, 0]
    # otherwise use output array as temp array
    else:
        tmp_p = out_p

    # decode image
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
            tmp_p,
            width,
            0,
            height,
            tmp_colorspace,
            flags
        )
        if retcode != 0 and (strict or tjGetErrorCode(decoder) == TJERR_FATAL):
            with gil:
                msg = __tj_error(decoder)
                tjDestroy(decoder)
                raise ValueError(msg)
        tjDestroy(decoder)

    # JPEG is CMYK color, but output is RGB, apply color conversion
    if is_cmyk and output_colorspace != TJPF_CMYK:
        # pre-fill alpha channel
        if output_colorspace == TJPF_RGBA \
          or output_colorspace == TJPF_BGRA \
          or output_colorspace == TJPF_ABGR \
          or output_colorspace == TJPF_ARGB:
            np.PyArray_FILLWBYTE(out, 255)
        if output_colorspace == TJPF_GRAY:
            cmyk2gray(tmp_p, out_p, height*width)
        else:
            cmyk2color(tmp_p, out_p, height*width, output_colorspace)

    # done
    return out


def encode_jpeg(
        const unsigned char[:, :, :] image not None,
        int quality=85,
        str colorspace='rgb',
        str colorsubsampling='444',
        bint fastdct=False,
):
    """
    Encode an image to JPEG (JFIF) string.
    Returns JPEG (JFIF) data.

    Parameters:
        image: uncompressed image as uint8 array
        quality: JPEG quantization factor
        colorspace: source colorspace; one of
                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.
        colorsubsampling: subsampling factor for color channels; one of
                          '444', '422', '420', '440', '411', 'Gray'.
        fastdct: If True, use fastest DCT method;
                 speeds up encoding by 4-5% for a minor loss in quality

    Returns:
        encoded image as JPEG (JFIF) data
    """
    cdef const unsigned char* image_p = &image[0, 0, 0]
    cdef int retcode
    cdef int height = image.shape[0]
    cdef int width = image.shape[1]
    cdef int channels = image.shape[2]

    cdef int pitch
    if image.strides is None:
        pitch = 0
    elif image.strides[0] == 0:
        raise ValueError('broadcasting rows is not supported')
    elif image.strides[1] != channels or image.strides[2] not in (0, 1):
        raise ValueError('image must have C contiguous rows, but strides are %r for shape %r' % (image.strides, image.shape))
    else:
        pitch = image.strides[0]

    cdef int colorspace_ = PIXELFORMATS[colorspace]
    if tjPixelSize[colorspace_] != channels:
        raise ValueError('%d channels does not match given colorspace %s'
                         % (channels, colorspace))
    cdef int colorsubsampling_ = TJSAMP_GRAY
    if colorspace_ != TJPF_GRAY:
        colorsubsampling_ = SUBSAMPLING[colorsubsampling]
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
            pitch,
            height,
            colorspace_,
            jpegbufbuf,
            &jpegsize,
            colorsubsampling_,
            quality,
            flags
        )
        if retcode != 0:
            with gil:
                msg = __tj_error(encoder)
                tjDestroy(encoder)
                raise ValueError(msg)
    jpeg = PyBytes_FromStringAndSize(<char *> jpegbuf, jpegsize)
    tjFree(jpegbuf)
    tjDestroy(encoder)
    return jpeg


def encode_jpeg_yuv_planes(
        const unsigned char[:, :] Y not None,
        const unsigned char[:, :] U,
        const unsigned char[:, :] V,
        int quality=85,
        bint fastdct=False,
):
    """
    Encode an image in a YUV planar format to JPEG (JFIF) string.
    U and V planes may be None to encode grayscale, but if one is given,
    the other must be as well.
    Returns JPEG (JFIF) data.

    Parameters:
        Y: uncompressed Y plane of the YUV image as uint8 array
        U: uncompressed U plane of the YUV image as uint8 array
        V: uncompressed V plane of the YUV image as uint8 array
        quality: JPEG quantization factor
        fastdct: If True, use fastest DCT method;
                 speeds up encoding by 4-5% for a minor loss in quality

    Returns:
        encoded image as JPEG (JFIF) data
    """
    cdef const unsigned char** planes = [
        &Y[0,0],
        &U[0,0],
        &V[0,0],
    ]
    cdef int retcode
    cdef int height = Y.shape[0]
    cdef int width = Y.shape[1]
    cdef int strides[3]
    cdef int colorsubsampling_ = TJSAMP_UNKNOWN
    cdef unsigned char * jpegbuf = NULL
    cdef unsigned char ** jpegbufbuf = &jpegbuf
    cdef unsigned long jpegsize = 0
    cdef int flags
    cdef tjhandle encoder

    if U is None and V is None:
        colorsubsampling_ = TJSAMP_GRAY
    elif U is None or V is None:
        raise ValueError(
            f'either both U {"(missing)" if U is None else "(present)"} and V '
            f'{"(missing)" if V is None else "(present)"} planes must be given, or neither'
        )
    elif U.shape[0] != V.shape[0] or U.shape[1] != V.shape[1]:
        raise ValueError(
            f'U and V planes must have matching shape, got {U.shape} and {V.shape}'
        )
    elif U.shape[0] == height:
        # Subsampling schemes with full vertical resolution:
        #
        # 4:4:4 - full resolution
        # oooo
        # oooo
        #
        # 4:2:2 - half horizontal resolution
        # o-o-
        # o-o-
        #
        # 4:1:1 - quarter horizontal resolution
        # o----
        # o----
        #
        if U.shape[1] == width:
            colorsubsampling_ = TJSAMP_444
        elif U.shape[1] * 2 in (width, width+1):
            colorsubsampling_ = TJSAMP_422
        elif U.shape[1] * 4 in (width, width+1, width+2, width+3):
            colorsubsampling_ = TJSAMP_411
    elif U.shape[0] * 2 in (height, height+1):
        # Subsampling schemes with half vertical resolution:
        #
        # 4:4:0 - half vertical resolution
        # oooo
        # ----
        #
        # 4:2:0 - half horizontal and vertical resolution
        # o-o-
        # ----
        #
        if U.shape[1] == width:
            colorsubsampling_ = TJSAMP_440
        elif U.shape[1] * 2 in (width, width+1):
            colorsubsampling_ = TJSAMP_420

    if colorsubsampling_ == TJSAMP_UNKNOWN:
        raise ValueError(
            'cannot determine chroma subsampling for planes of shape '
            f'Y={Y.shape} U={U.shape} V={V.shape}'
        )

    if Y.strides is None:
        strides[0] = 0
    elif Y.strides[0] == 0:
        raise ValueError('broadcasting Y plane rows is not supported')
    elif Y.strides[1] != 1:
        raise ValueError('Y plane must have C contiguous rows, but strides are %r for shape %r' % (Y.strides, Y.shape))
    else:
        strides[0] = Y.strides[0]

    if U is None or U.strides is None:
        strides[1] = 0
    elif U.strides[0] == 0:
        raise ValueError('broadcasting U plane rows is not supported')
    elif U.strides[1] != 1:
        raise ValueError('U plane must have C contiguous rows, but strides are %r for shape %r' % (U.strides, U.shape))
    else:
        strides[1] = U.strides[0]

    if V is None or V.strides is None:
        strides[2] = 0
    elif V.strides[0] == 0:
        raise ValueError('broadcasting V plane rows is not supported')
    elif V.strides[1] != 1:
        raise ValueError('V plane must have C contiguous rows, but strides are %r for shape %r' % (V.strides, V.shape))
    else:
        strides[2] = V.strides[0]

    with nogil:
        encoder = tjInitCompress()
        if encoder == NULL:
            raise RuntimeError('could not create JPEG encoder')
        flags = 0
        if fastdct:
            flags |= TJFLAG_FASTDCT
        retcode = tjCompressFromYUVPlanes(
            encoder,
            planes,
            width,
            strides,
            height,
            colorsubsampling_,
            jpegbufbuf,
            &jpegsize,
            quality,
            flags
        )
        if retcode != 0:
            with gil:
                msg = __tj_error(encoder)
                tjDestroy(encoder)
                raise ValueError(msg)
    jpeg = PyBytes_FromStringAndSize(<char *> jpegbuf, jpegsize)
    tjFree(jpegbuf)
    tjDestroy(encoder)
    return jpeg
