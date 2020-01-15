import os
import os.path as pt
import re
import platform
import sys
import urllib.request
import tarfile
import sysconfig

from setuptools import setup
from setuptools import find_packages
from setuptools import Extension
from setuptools.command.build_ext import build_ext
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
YASM_VERSION = '1.3.0'
YASM_SOURCE = 'yasm-%s.tar.gz' % YASM_VERSION
YASM_URL = 'https://github.com/yasm/yasm/releases/download/v%s/' % YASM_VERSION + YASM_SOURCE
JPEG_VERSION = '2.0.4'
JPEG_SOURCE = 'libjpeg-turbo-%s.tar.gz' % JPEG_VERSION
JPEG_URL = 'https://github.com/libjpeg-turbo/libjpeg-turbo/archive/%s.tar.gz' % JPEG_VERSION


def untar_url(url, filename):
    path = filename.rstrip('.tar.gz')
    if not pt.exists(path):
        if not pt.exists(filename):
            os.makedirs(pt.dirname(filename), exist_ok=True)
            print('downloading', url)
            urllib.request.urlretrieve(url, filename)
        os.makedirs(pt.dirname(filename), exist_ok=True)
        with tarfile.open(filename) as t:
            print('extracting', filename)
            t.extractall(pt.dirname(filename))
    return path


# download sources
YASM_DIR = untar_url(YASM_URL, pt.join(PACKAGE_DIR, 'lib', YASM_SOURCE))
JPEG_DIR = untar_url(JPEG_URL, pt.join(PACKAGE_DIR, 'lib', JPEG_SOURCE))


def cvar(name):
    return sysconfig.get_config_var(name)


def make_type():
    if PLATFORM in ('linux', 'darwin'):
        return 'Unix Makefiles'
    elif PLATFORM == 'windows':
        return 'NMake Makefiles'
    else:
        raise RuntimeError('Platform not supported: %s, %s' % (PLATFORM, ARCH))


class cmake_build_ext(build_ext):
    def run(self):
        self.build_cmake_dependency(YASM_DIR, [
            '-DBUILD_SHARED_LIBS=OFF'
        ])
        self.build_cmake_dependency(JPEG_DIR, [
            '-DASM_NASM=' + pt.join(YASM_DIR, 'build', 'yasm'),
            '-DENABLE_SHARED=0',
            '-DREQUIRE_SIMD=1',
            '-DCMAKE_POSITION_INDEPENDENT_CODE=ON'
        ])
        # build extensions
        super().run()

    def build_cmake_dependency(self, path, options):
        if PLATFORM == 'windows':
            # MSVC build environment
            from setuptools.msvc import EnvironmentInfo
            info = EnvironmentInfo(ARCH)
            for k in dir(info):
                print(k, getattr(info, k))
            os.environ['PATH'] = os.pathsep.join(info.VCTools + info.SdkTools + [
                'C:\\Program Files (x86)\\Windows Kits\\10\\bin\\10.0.18362.0\\' + ARCH,
                os.environ.get('PATH', '')
            ])
            os.environ['INCLUDE'] = os.pathsep.join(info.OSIncludes + info.VCIncludes + info.UCRTIncludes)
            os.environ['LIB'] = os.pathsep.join(info.OSLibraries + info.VCLibraries + info.UCRTLibraries)
        cur_dir = pt.abspath(os.curdir)
        build_dir = pt.join(path, 'build')
        if not pt.exists(build_dir):
            os.makedirs(build_dir)
        os.chdir(build_dir)
        config = 'Debug' if self.debug else 'Release'
        self.spawn([
            'cmake',
            '-G' + make_type(),
            '-DCMAKE_BUILD_TYPE=' + config,
            *options,
            pt.join(path)
        ])
        if not self.dry_run:
            self.spawn(['cmake', '--build', '.', '--config', config])
        os.chdir(cur_dir)


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


def normalize_windows_paths(*file_paths):
    for fp in file_paths:
        with open(fp) as f:
            text = f.read()
        new_text = text.replace(r'\\', '/')
        if new_text != text:
            with open(fp, 'w') as f:
                f.write(new_text)


def _libdir():
    return pt.join(JPEG_DIR, 'build')


def _staticlib():
    if PLATFORM in ('linux', 'darwin'):
        return 'libturbojpeg.a'
    elif PLATFORM == 'windows':
        return 'turbojpeg-static.lib'
    else:
        raise RuntimeError('Platform not supported: %s, %s' % (PLATFORM, ARCH))


def make_jpeg_module():
    include_dirs = [
        np.get_include(),
        pt.join(JPEG_DIR),
        pt.join(PACKAGE_DIR, 'simplejpeg'),
    ]
    static_libs = [pt.join(_libdir(), _staticlib())]
    cython_files = [pt.join('simplejpeg', '_jpeg.pyx')]
    for cython_file in cython_files:
        if pt.exists(cython_file):
            cythonize(cython_file)
    remove_c_comments(pt.join('simplejpeg', '_jpeg.c'))
    normalize_windows_paths(pt.join('simplejpeg', '_jpeg.c'))
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


class ConcatFiles:
    """
    Context manager that appends an arbitrary number of files to the end
    of a given output file.

    Inspired by how numpy handles license files:
    https://github.com/numpy/numpy/blob/c28fc48328e9621160debae4d0d99feeff3b8fdf/setup.py#L193
    """
    def __init__(self, output_file, *files, separator='='*80):
        self.output_file = output_file
        self.original_output = None
        self.files = files
        self.separator = separator

    def __enter__(self):
        with open(self.output_file) as fp:
            self.original_output = fp.read()
        content = [self.original_output]
        for f in self.files:
            with open(f) as fp:
                content.extend([
                    '\n', '\n', self.separator,
                    'Content of: ' + f,
                    self.separator, '\n',
                    fp.read()
                ])
        with open(self.output_file, 'w') as fp:
            fp.write('\n'.join(content))

    def __exit__(self, exception_type, exception_value, traceback):
        with open(self.output_file, 'w') as fp:
            fp.write(self.original_output)
        self.original_output = None


LICENSE_FILES = [
    'LICENSE',
    pt.join(JPEG_DIR, 'LICENSE.md'),
    pt.join(JPEG_DIR, 'README.ijg')
]
with ConcatFiles(*LICENSE_FILES):
    setup(
        name='simplejpeg',
        version=find_version('simplejpeg', '__init__.py'),
        author='Joachim Folz',
        author_email='joachim.folz@dfki.de',
        license='MIT',
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
        cmdclass={'build_ext': cmake_build_ext},
        zip_safe=False,
        project_urls={
            'Documentation': 'https://gitlab.com/jfolz/simplejpeg/blob/master/README.rst',
            'Source': 'https://gitlab.com/jfolz/simplejpeg',
            'Tracker': 'https://gitlab.com/jfolz/simplejpeg/issues',
        },
    )
