"""
Generate the reference data used by the test suite.

The decoding tests compare simplejpeg's output against reference pixel
arrays that were produced by libjpeg-turbo's own djpeg utility from the
JPEG images in test/images.  Both use the same libjpeg-turbo version, so
the references pin the codec version precisely; they must be regenerated
with this script whenever SIMPLEJPEG_JPEG_VERSION changes.  The encoding
tests generate their content on the fly and validate round trips; they
do not use reference data.

References are stored as a single compressed numpy archive, with one
delta-encoded (a PNG-style 'Up' filter) 'rgb' (h, w, 3) array per JPEG
keyed by the image name.

The script needs numpy and the built libjpeg-turbo tools (djpeg); it does
not import simplejpeg or Pillow.
Run:  python3 test/update_references.py
"""
import glob
import os
import os.path as pt
import shutil
import subprocess

import numpy as np

ROOT = pt.abspath(pt.dirname(__file__))
IMAGES_DIR = pt.join(ROOT, 'images')
REFERENCE_PATH = pt.join(ROOT, 'reference_data.npz')


def find_djpeg():
    override = os.environ.get('SIMPLEJPEG_DJPEG')
    if override:
        return override
    for candidate in sorted(glob.glob(pt.join(ROOT, '..', 'lib',
                                              'libjpeg-turbo-*',
                                              'build*', 'djpeg-static'))):
        if os.access(candidate, os.X_OK):
            return candidate
    djpeg = shutil.which('djpeg')
    if djpeg:
        return djpeg
    raise RuntimeError(
        'djpeg not found: build the vendored libjpeg-turbo first or set '
        'SIMPLEJPEG_DJPEG'
    )


def parse_pnm(data):
    fields, i = [], 2
    while len(fields) < 3:
        while data[i:i + 1].isspace():
            i += 1
        if data[i:i + 1] == b'#':
            i = data.index(b'\n', i) + 1
            continue
        j = i
        while not data[j:j + 1].isspace():
            j += 1
        fields.append(int(data[i:j]))
        i = j
    width, height, maxval = fields
    if maxval != 255:
        raise ValueError(f'unexpected max value {maxval}')
    i += 1  # single whitespace byte after the max value
    channels = 3 if data[:2] == b'P6' else 1
    count = height * width * channels
    if len(data) - i < count:
        raise ValueError('truncated PNM payload')
    array = np.frombuffer(data[i:i + count], dtype=np.uint8)
    return array.reshape(height, width, channels)


def run_djpeg(djpeg, arguments):
    completed = subprocess.run([djpeg, *arguments], capture_output=True, check=True)
    return parse_pnm(completed.stdout)


def delta_encode(array):
    # PNG-style 'Up' filter: every row is stored as a wrapped uint8
    # difference to the row above (the first row against zero)
    delta = array.copy()
    delta[1:] = array[1:] - array[:-1]
    return delta


def main():
    djpeg = find_djpeg()
    arrays = {}
    for image_path in sorted(glob.glob(pt.join(IMAGES_DIR, '*.jpg'))):
        name = pt.splitext(pt.basename(image_path))[0]
        try:
            rgb = run_djpeg(djpeg, [image_path])
        except subprocess.CalledProcessError as e:
            raise RuntimeError(f'djpeg failed on {image_path}') from e
        arrays[name] = delta_encode(rgb)
    np.savez_compressed(REFERENCE_PATH, **arrays)


if __name__ == '__main__':
    main()
