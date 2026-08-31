
This project is in no way affiliated with the
`libjpeg-turbo <https://github.com/libjpeg-turbo/libjpeg-turbo>`_
project.



simplejpeg
==========

simplejpeg is a simple package based on recent versions
of libturbojpeg for fast JPEG encoding and decoding.



Why another library?
--------------------

Pillow and OpenCV are excellent options for handling JPEG
images and a variety of other formats.

If all you want is to read or write a couple of images and
don't worry about the details, this package is not for you.

Keep reading if you care about speed and want more control
over how your JPEGs are handled.

These are the reasons why I started making this:

#. Pillow is **very** slow compared to OpenCV.
#. Pillow only accepts streams as input. Images in memory
   have to be wrapped in ``BytesIO`` or similar.
   This adds to the slowness.
#. OpenCV is gigantic,
   only accepts Numpy arrays as input,
   and returns images as BGR instead of RGB.
#. Recent versions of libturbojpeg offer impressive speed
   gains on modern processors.
   Linux distributions and libraries tend to ship very old
   versions.


This library is especially for you if you need:

#. Speed.
#. Read and write directly from/to memory.
#. Advanced features of the underlying library.
#. A lightweight footprint.



Installation
------------

- On Linux (x64, arm64), Windows (x64, arm64), or MacOS (10.9+, x64, arm64)
  you can simply ``pip install simplejpeg``.
  Update ``pip`` if it wants to build from source anyway.
- On other platforms you can try to install from source.
  Make sure your system is setup to build CPython extensions
  and install ``cmake`` as well as either ``nasm`` or ``yasm``.
  Then run ``pip install simplejpeg`` to install from source.
- You can also checkout the repository and run ``python -m build .``,
  ``python setup.py bdist_wheel`` etc. as usual.
- Instead of building and statically linking, you can install
  ``libturbojpeg-dev`` (or similar) and set ``SIMPLEJPEG_DYNAMIC_LINKING=1``
  in your environment to dynamically link it.
  Version 3.x strongly recommended, but 2.0.90+ should work.
  1.x definitely doesn't.
  Importantly, note that
  `libjpeg-turbo != libturbojpeg <https://libjpeg-turbo.org/About/TurboJPEG>`_.



Usage
-----

This library provides four functions:

``decode_jpeg_header``, ``decode_jpeg``, ``encode_jpeg``, ``is_jpeg``.

NumPy is completely optional. By default, decoding returns NumPy arrays if installed,
but functions natively accept and return standard Python objects that support the
`buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_, like ``bytes``,
``bytearray``, and ``memoryview``.



decode_jpeg_header
~~~~~~~~~~~~~~~~~~

::

    decode_jpeg_header(
        data: Any,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
        strict: bool=True,
    ) -> (SupportsInt, SupportsInt, Text, Text)


Decode only the header of a JPEG image given as JPEG (JFIF) data from memory.
Accepts any input that supports the
`buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_.
This is very fast on the order of 100000+ images per second.
Returns height and width in pixels of the image when decoded,
and colorspace and subsampling as string.

- data:
  JPEG data in memory; must support buffer interface
  (e.g., ``bytes``, ``memoryview``)
- min_height:
  minimum height in pixels of the decoded image;
  values <= 0 are ignored
- min_width:
  minimum width in pixels of the decoded image;
  values <= 0 are ignored
- min_factor:
  minimum downsampling factor when decoding to smaller size;
  factors smaller than 2 may take longer to decode
- strict:
  if True, raise ValueError for recoverable errors;
  default True
- returns: ``(height: int, width: int, colorspace: str, color subsampling: str)``



decode_jpeg
~~~~~~~~~~~

::

    def decode_jpeg(
        data: SupportsBuffer,
        colorspace: Text='RGB',
        fastdct: Any=False,
        fastupsample: Any=False,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
        buffer: SupportsBuffer=None,
        strict: bool=True,
        output: Text='numpy',
    ) -> Any

Decode a JPEG image given as JPEG (JFIF) data from memory.
Accepts any input that supports the
`buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_.
Returns the image data in the format requested by ``output``.

- data:
  JPEG data in memory; must support buffer interface
  (e.g., ``bytes``, ``bytearray``, ``memoryview``);
  row must be C-contiguous
- colorspace:
  target colorspace, any of the following:
  'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
  'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
  'CMYK' may only be used for images already in CMYK space
- fastdct:
  if True, use fastest DCT method;
  speeds up decoding by 4-5% for a minor loss in quality
- fastupsample:
  if True, use fastest color upsampling method;
  speeds up decoding by 4-5% for a minor loss in quality
- min_height:
  minimum height in pixels of the decoded image;
  values <= 0 are ignored
- min_width:
  minimum width in pixels of the decoded image;
  values <= 0 are ignored
- min_factor:
  minimum downsampling factor when decoding to smaller size;
  factors smaller than 2 may take longer to decode
- buffer:
  use given object as output buffer;
  must support the buffer protocol and be writable, e.g.,
  numpy ndarray or bytearray;
  use decode_jpeg_header to find out required minimum size
- strict:
  if True, raise ValueError for recoverable errors;
  default True
- output:
  either ``'numpy'`` (default) or ``'bytes'``.
  ``'numpy'`` returns a numpy ndarray of shape (height, width, channels);
  numpy is imported lazily and must be installed.
  ``'bytes'`` returns a plain bytearray plus its dimensions.
- returns:
  image as ``numpy.ndarray`` (if ``output='numpy'``) OR
  ``(pixels: bytearray, height: int, width: int, channels: int)`` (if ``output='bytes'``)



encode_jpeg
~~~~~~~~~~~

::

    def encode_jpeg(
            image: Any,
            quality: SupportsInt=85,
            colorspace: Text='RGB',
            colorsubsampling: Text='444',
            fastdct: Any=True,
    ) -> bytes

Encode an image given as a multi-dimensional array or memoryview to JPEG (JFIF) string.
Returns JPEG (JFIF) data.

- image:
  uncompressed image as uint8 array; any object supporting the buffer protocol mapped to
  a 3D shape (e.g., a NumPy ndarray, or a flat buffer cast to a 3D memoryview).
- quality:
  JPEG quantization factor;
  0\-100, higher equals better quality
- colorspace:
  source colorspace; one of
  'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
  'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'
- colorsubsampling:
  subsampling factor for color channels; one of
  '444', '422', '420', '440', '411', 'Gray'.
- fastdct:
  If True, use fastest DCT method;
  usually no observable difference
- returns: ``bytes`` object of encoded image as JPEG (JFIF) data



encode_jpeg_yuv_planes
~~~~~~~~~~~~~~~~~~~~~~

::

    def encode_jpeg_yuv_planes(
            Y: Any,
            U: Any,
            V: Any,
            quality: SupportsInt=85,
            fastdct: Any=False,
    ) -> bytes

Encode an image given as three 2D arrays or memoryviews to JPEG (JFIF) bytes.
The color subsampling is deduced from the size of the three arrays.
Returns JPEG (JFIF) data.

- Y:
  uncompressed Y plane as uint8 array; must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
- U:
  uncompressed U plane as uint8 array; must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
- V:
  uncompressed V plane as uint8 array; must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
- quality:
  JPEG quantization factor;
  0\-100, higher equals better quality
- fastdct:
  If True, use fastest DCT method;
  usually no observable difference
- returns: ``bytes`` object of encoded image as JPEG (JFIF) data

*Using encode_jpeg_yuv_planes with OpenCV*

OpenCV has limited support for YUV420 images, but where it does it
will normally represent a ``W x H`` image (``W`` and ``H`` both
assumed even) as an array of height ``H + H // 2`` and width ``W``.

Of these, the first ``H`` rows are the Y plane. Thereafter follow ``H
// 2`` lots of ``W // 2`` bytes (the U plane), and then the same again
for the V plane. Note how we have two rows of U or V in every *array*
row. To unpack such an image for passing to ``encode_jpeg_yuv_planes``
use:

::

    Y = image[:H]
    U = image.reshape(H * 3, W // 2)[H * 2: H * 2 + H // 2]
    V = image.reshape(H * 3, W // 2)[H * 2 + H // 2:]

``encode_jpeg_yuv_planes`` saves us from having to convert first to
RGB and then (within ``encode_jpeg``) back to YUV, all of which costs
time and memory when dealing with large images on resource constrained
platforms.


is_jpeg
~~~~~~~

::

    def is_jpeg(data: SupportsBytes)


Check whether a bytes object (or similar) contains JPEG (JFIF) data.

- data: JPEG (JFIF) data
- returns: True if JPEG
