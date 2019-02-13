# turbojpeg

turbojpeg is a simple package based on the newest version
of libturbojpeg for the fatest JPEG encoding and decoding.



# Why another library?

Pillow and OpenCV are excellent options for handling JPEG
images.
If all you want is to read or write a couple of images and
don't worry about the details, this package is not for you.
Keep reading if you care about speed and want more control
over how your JPEGs are handled.

These are the reasons why I started making this:
1. Pillow is **very** slow compared to OpenCV.
1. Pillow only accepts streams as input. Images in memory
   have to be wrapped in a BytesIO or similar.
   This adds to the slowness.
1. OpenCV is gigantic,
   only accepts Numpy arrays as input,
   and returns BGR.
1. Recent versions of libturbojpeg offer impressive speed
   gains on modern processors.
   Linux distributions and libraries tend to ship very old
   versions.

This library is especially for you if you need:
1. Speed.
1. Read and write directly from/to memory.
1. Advanced features of the underlying library.



## Usage


`decode_jpeg_header(data, min_height=0, min_width=0, min_factor=1)`
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
    return 0, 0, 'rgb', '444'


def decode_jpeg(
        data: Any,
        colorspace: Text='rgb',
        fastdct: Any=True,
        fastupsample: Any=True,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
) -> np.ndarray:
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
    return np.empty((1, 1, 1))


def encode_jpeg(
        image: np.ndarray,
        quality: SupportsInt=85,
        colorspace: Text='rgb',
        colorsubsampling: Text='444',
        fastdct: Any=True,
):
    """
    Encode an image to JPEG (JFIF) string.
    Returns JPEG (JFIF) data.

    :param image: uncompressed image
    :param quality: JPEG quantization factor
    :param colorspace: source colorspace; one of
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.
    :param colorsubsampling: subsampling factor for color channels; one of
                             '444', '422', '420', '440', '411', 'Gray'.
    :param fastdct: If True, use fastest DCT method;
                    usually no observable difference
    :return: encoded image as JPEG (JFIF) data
    """
    return b''
