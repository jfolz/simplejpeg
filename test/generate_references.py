"""
Generate the reference data used by the test suite.

By default libjpeg-turbo's djpeg utility built from source is used.
Alternatively make sure a djpeg binary is on the PATH or set the
SIMPLEJPEG_DJPEG env var to use a specific binary.

Decoded references are stored in a numpy archive, with one delta-encoded
(a PNG-style 'Up' filter) 'rgb' (h, w, 3) array per JPEG keyed by the
image name.
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
    for build_dir in sorted(glob.glob(
            pt.join(ROOT, '..', 'lib', 'libjpeg-turbo-*', 'build*'))):
        path = os.environ.get('PATH', os.defpath)
        os.environ['PATH'] = build_dir + os.pathsep + path
    djpeg = shutil.which('djpeg-static') or shutil.which('djpeg')
    if not djpeg:
        raise RuntimeError(
            'djpeg not found: build the vendored libjpeg-turbo first or set '
            'SIMPLEJPEG_DJPEG'
        )
    return djpeg


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


def run_djpeg(djpeg, *arguments):
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
            rgb = run_djpeg(djpeg, image_path)
        except subprocess.CalledProcessError as e:
            raise RuntimeError(f'djpeg failed on {image_path}') from e
        arrays[name] = delta_encode(rgb)
    np.savez_compressed(REFERENCE_PATH, **arrays)


if __name__ == '__main__':
    main()
