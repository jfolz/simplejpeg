This project is in no way affiliated with the
[libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo)
project.



# simplejpeg

simplejpeg is a simple package based on the recent versions
of libturbojpeg for the fast JPEG encoding and decoding.



# Why another library?

Pillow and OpenCV are excellent options for handling JPEG
images and a variety of other formats.
If all you want is to read or write a couple of images and
don't worry about the details, this package is not for you.
Keep reading if you care about speed and want more control
over how your JPEGs are handled.

These are the reasons why I started making this:
1. Pillow is **very** slow compared to OpenCV.
1. Pillow only accepts streams as input. Images in memory
   have to be wrapped in `BytesIO` or similar.
   This adds to the slowness.
1. OpenCV is gigantic,
   only accepts Numpy arrays as input,
   and returns images as BGR.
1. Recent versions of libturbojpeg offer impressive speed
   gains on modern processors.
   Linux distributions and libraries tend to ship very old
   versions.

This library is especially for you if you need:
1. Speed.
1. Read and write directly from/to memory.
1. Advanced features of the underlying library.



## Usage

This library provides three functions:
`decode_jpeg_header`, `decode_jpeg`, and `encode_jpeg`.
Uncompressed image data is stored as numpy arrays.
Deconding functions can accept any Python object that supports the
[buffer protocol](https://docs.python.org/3/c-api/buffer.html),
like `bytes`, `bytearray`, `memoryview`, etc.


`decode_jpeg_header(data, min_height=0, min_width=0, min_factor=1)`

Decode only the header of a JPEG image given as JFIF file from memory.
Accepts any input that supports the
[buffer protocol](https://docs.python.org/3/c-api/buffer.html).
Returns height and width in pixels of the image when decoded,
and colorspace and subsampling as string.

 * data:
        JPEG data in memory; must support buffer interface
        (e.g., `bytes`, `memoryview`)
 * min_height:
        minimum height in pixels of the decoded image;
        values <= 0 are ignored
 * min_width:
        minimum width in pixels of the decoded image;
        values <= 0 are ignored
 * min_factor:
        minimum downsampling factor when decoding to smaller size;
        factors smaller than 2 may take longer to decode
 * returns: `(height: int, width: int, colorspace: str, color subsampling: str)`



`def decode_jpeg(
        data: SupportsBuffer,
        colorspace: Text='RGB',
        fastdct: Any=True,
        fastupsample: Any=True,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
)`

Decode a JPEG image given as JFIF file from memory.
Accepts any input that supports the
[buffer protocol](https://docs.python.org/3/c-api/buffer.html).
Returns the image as numpy array in the requested colorspace.

 * data:
        JPEG data in memory; must support buffer interface
        (e.g., `bytes`, `memoryview`)
 * colorspace:
        target colorspace, any of the following:
       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
       'CMYK' may only be used for images already in CMYK space
 * fastdct:
        if True, use fastest DCT method;
        usually no observable difference
 * fastupsample:
        if True, use fastest color upsampling method;
        usually no observable difference
 * min_height:
        minimum height in pixels of the decoded image;
        values <= 0 are ignored
 * param min_width:
        minimum width in pixels of the decoded image;
        values <= 0 are ignored
 * param min_factor:
        minimum downsampling factor when decoding to smaller size;
        factors smaller than 2 may take longer to decode
 * returns: image as `numpy.ndarray`



`def encode_jpeg(
        image: numpy.ndarray,
        quality: SupportsInt=85,
        colorspace: Text='RGB',
        colorsubsampling: Text='444',
        fastdct: Any=True,
)`

Encode an image given as numpy array to JPEG (JFIF) string.
Returns JPEG (JFIF) data.

 * image:
        uncompressed image as numpy array
 * quality:
        JPEG quantization factor;
        0-100, higher equals better quality
 * colorspace:
        source colorspace; one of
        'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
        'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'
 * colorsubsampling:
        subsampling factor for color channels; one of
        '444', '422', '420', '440', '411', 'Gray'.
 * fastdct:
        If True, use fastest DCT method;
        usually no observable difference
 * returns: `bytes` object of encoded image as JPEG (JFIF) data
