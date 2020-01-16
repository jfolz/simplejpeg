
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



Usage
-----

This library provides four functions:

``decode_jpeg_header``, ``decode_jpeg``, ``encode_jpeg``, ``is_jpeg``.

Uncompressed image data is stored as numpy arrays.
Decoding functions can accept any Python object that supports the
`buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_,
like ``array``, ``bytes``, ``bytearray``, ``memoryview``, etc.



decode_jpeg_header
~~~~~~~~~~~~~~~~~~

::

    decode_jpeg_header(
        data: Any,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
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
    ) -> np.ndarray

Decode a JPEG image given as JPEG (JFIF) data from memory.
Accepts any input that supports the
`buffer protocol <https://docs.python.org/3/c-api/buffer.html>`_.
Returns the image as numpy array in the requested colorspace.

- data:
  JPEG data in memory; must support buffer interface
  (e.g., ``bytes``, ``memoryview``)
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
- param min_width:
  minimum width in pixels of the decoded image;
  values <= 0 are ignored
- param min_factor:
  minimum downsampling factor when decoding to smaller size;
  factors smaller than 2 may take longer to decode
- buffer:
  use given object as output buffer;
  must support the buffer protocol and be writable, e.g.,
  numpy ndarray or bytearray;
  use decode_jpeg_header to find out required minimum size
- returns: image as ``numpy.ndarray``



encode_jpeg
~~~~~~~~~~~

::

    def encode_jpeg(
            image: numpy.ndarray,
            quality: SupportsInt=85,
            colorspace: Text='RGB',
            colorsubsampling: Text='444',
            fastdct: Any=True,
    ) -> bytes

Encode an image given as numpy array to JPEG (JFIF) string.
Returns JPEG (JFIF) data.

- image:
  uncompressed image as uint8 array
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



is_jpeg
~~~~~~~

::

    def is_jpeg(data: SupportsBytes)


Check whether a bytes object (or similar) contains JPEG (JFIF) data.

- data: JPEG (JFIF) data
- returns: True if JPEG



Changelog
--------------------

1.3.3
~~~~~

- Fix linker warning for Windows build.

1.3.2
~~~~~

- ``min_width`` and ``min_height`` are now ignored if 0 as stated in the docs.
- CI now builds libjpeg-turbo from source.
- Add Appyevor to CI for Windows builds.
- Distribute manylinux2010 wheels.
- Fix license missing from linux wheels.

1.3.1
~~~~~

- ``decode_jpeg`` requests writable buffer from ``buffer`` argument.

1.3.0
~~~~~

- ``decode_jpeg`` accepts optional ``buffer`` argument.

1.2.6
~~~~~

- Fix memory corruption caused by incorrect GIL handling.

1.2.5
~~~~~

- Initial public release.
