import io
import os
import os.path as pt
import re
import platform
import glob
import sys
from shutil import copyfile

from setuptools import setup
from setuptools import find_packages
from setuptools import Extension
# don't require Cython for building
try:
    from Cython.Build import cythonize
    HAVE_CYTHON = True
except ImportError:
    def cythonize(*_, **__):
        pass
    HAVE_CYTHON = False
import numpy as np


PACKAGE_DIR = pt.abspath(pt.dirname(__file__))
PLATFORM = platform.system().lower()
IS64BIT = sys.maxsize > 2**32
ARCH = 'x64' if IS64BIT else 'x86'


def remove_c_comments(*file_paths):
    """
    https://stackoverflow.com/a/241506/6862913
    """
    def replacer(match):
        s = match.group(0)
        return ' ' if s.startswith('/') else s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    for fp in file_paths:
        with open(fp) as f:
            text = f.read()
        new_text = re.sub(pattern, replacer, text)
        if new_text != text:
            with open(fp, 'w') as f:
                f.write(new_text)


def _libdir():
    return pt.join(PACKAGE_DIR, 'lib', 'turbojpeg', PLATFORM, ARCH)


def _staticlib():
    if PLATFORM == 'linux':
        return 'libturbojpeg.a'
    elif PLATFORM == 'windows':
        return 'turbojpeg-static.lib'
    else:
        raise RuntimeError('Platform not supported: %s, %s' % (PLATFORM, ARCH))


def make_jpeg_module():
    include_dirs = [
        np.get_include(),
        pt.join(PACKAGE_DIR, 'lib', 'turbojpeg'),
        pt.join(PACKAGE_DIR, 'simplejpeg'),
    ]
    static_libs = [pt.join(_libdir(), _staticlib())]
    cython_files = [pt.join('simplejpeg', '_jpeg.pyx')]
    for cython_file in cython_files:
        if pt.exists(cython_file):
            cythonize(cython_file)
    remove_c_comments(pt.join('simplejpeg', '_jpeg.c'))
    sources = [
        pt.join('simplejpeg', '_jpeg.c'),
        pt.join('simplejpeg', '_color.c')
    ]
    return Extension(
        'simplejpeg._jpeg',
        sources,
        language='C',
        include_dirs=include_dirs,
        extra_objects=static_libs,
        extra_link_args=['-Wl,--strip-all,--exclude-libs,ALL'],
        extra_compile_args=['-g0'],
    )


# define extensions
ext_modules = [make_jpeg_module()]


def read(*names):
    with open(pt.join(PACKAGE_DIR, *names), encoding='utf8') as f:
        return f.read()


# pip's single-source version method as described here:
# https://python-packaging-user-guide.readthedocs.io/single_source_version/
def find_version(*file_paths):
    version_file = read(*file_paths)
    version_match = re.search(r'^__version__ = [\'"]([^\'"]*)[\'"]',
                              version_file, re.M)
    if version_match:
        return version_match.group(1)
    raise RuntimeError('Unable to find version string.')


def find_package_data(packages):
    package_data = {
        package: [
            '*.pyi'
        ]
        for package in packages
    }
    return package_data


packages = find_packages(
    include=['simplejpeg', 'simplejpeg.*'],
)


package_data = find_package_data(packages)


with open(pt.join(PACKAGE_DIR, 'requirements.txt')) as f:
    dependencies = [l.strip(' \n') for l in f]


with open(pt.join(PACKAGE_DIR, 'build-requirements.txt')) as f:
    build_dependencies = [l.strip(' \n') for l in f]


with open(pt.join(PACKAGE_DIR, 'README.rst')) as f:
    description = f.read()


setup(
    name='simplejpeg',
    version=find_version('simplejpeg', '__init__.py'),
    author='Joachim Folz',
    author_email='joachim.folz@dfki.de',
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Science/Research',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'License :: OSI Approved :: MIT License',
    ],
    description='A simple package for fast JPEG encoding and decoding.',
    long_description=description,
    long_description_content_type='text/x-rst; charset=UTF-8',
    keywords='the fastest JPEG encoding decoding package in town',
    packages=packages,
    package_data=package_data,
    setup_requires=build_dependencies,
    install_requires=dependencies,
    ext_modules=ext_modules,
    project_urls={
        'Documentation': 'https://gitlab.com/jfolz/simplejpeg/blob/master/README.rst',
        'Source': 'https://gitlab.com/jfolz/simplejpeg',
        'Tracker': 'https://gitlab.com/jfolz/simplejpeg/issues',
    }
)
