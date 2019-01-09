import io
import sys
import os
import os.path as pt
import re
import platform

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
IS_64BIT = sys.maxsize > 2**32
IS_32BIT = not IS_64BIT
BITNESS = '64' if IS_64BIT else '32'
PLATFORM = platform.system()
IS_LINUX = PLATFORM == 'Linux'
IS_WINDOWS = PLATFORM == 'Windows'
IS_DARWIN = PLATFORM == 'Darwin'


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
                f.write(text)


def make_jpeg_module():
    include_dirs = [
        np.get_include(),
        pt.join(PACKAGE_DIR, 'lib', 'turbojpeg'),
        pt.join(PACKAGE_DIR, 'turbojpeg'),
    ]
    extra_objects = [
        pt.join(PACKAGE_DIR, 'lib', 'turbojpeg',
                'linux64', 'libturbojpeg.a')
    ]
    cythonize(pt.join('turbojpeg', '_jpeg.pyx'))
    remove_c_comments(pt.join('turbojpeg', '_jpeg.c'))
    return Extension(
        'turbojpeg._jpeg',
        [pt.join('turbojpeg', '_jpeg.c')],
        language='C',
        include_dirs=include_dirs,
        extra_objects=extra_objects,
        extra_link_args=['-Wl,--strip-all'],
        extra_compile_args=['-g0'],
    )


# define extensions
ext_modules = []
if not IS_LINUX or IS_32BIT:
    raise RuntimeError('only 64 bit Linux is supported')
elif IS_LINUX and IS_64BIT:
    ext_modules.append(make_jpeg_module())


def read(*names, **kwargs):
    with io.open(
        os.path.join(PACKAGE_DIR, *names),
        encoding=kwargs.get('encoding', 'utf8')
    ) as fp:
        return fp.read()


# pip's single-source version method as described here:
# https://python-packaging-user-guide.readthedocs.io/single_source_version/
def find_version(*file_paths):
    version_file = read(*file_paths)
    version_match = re.search(r'^__version__ = [\'"]([^\'"]*)[\'"]',
                              version_file, re.M)
    if version_match:
        return version_match.group(1)
    raise RuntimeError('Unable to find version string.')


packages = find_packages(
    include=['turbojpeg', 'turbojpeg.*'],
)


package_data = {
    package: [
        '*.py',
        '*.txt',
        '*.json',
    ]
    for package in packages
}


with open(pt.join(PACKAGE_DIR, 'requirements.txt')) as f:
    dependencies = [l.strip(' \n') for l in f]


setup(
    name='turbojpeg',
    version=find_version('turbojpeg', '__init__.py'),
    author='Joachim Folz',
    author_email='joachim.folz@dfki.de',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Science/Research',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
    ],
    keywords='the fastest JPEG package in town',
    packages=packages,
    package_data=package_data,
    setup_requires=['numpy'],
    install_requires=dependencies,
    ext_modules=ext_modules,
)
