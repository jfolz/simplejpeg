import os
import os.path as pt
import re
import platform
import sys
import urllib.request
import tarfile
import sysconfig
import subprocess
import hashlib

from setuptools import setup
from setuptools import find_packages
from setuptools import Extension
from setuptools.command.build_ext import build_ext


# fall back to system cmake if cmake package is not installed
try:
    from cmake import CMAKE_BIN_DIR
    CMAKE_PATH = pt.join(CMAKE_BIN_DIR, 'cmake')
except ImportError:
    CMAKE_PATH = 'cmake'


# don't require Cython for building
try:
    from Cython.Build import cythonize
    HAVE_CYTHON = True
except ImportError:
    def cythonize(*_, **__):
        pass
    HAVE_CYTHON = False


class NumpyImport:
    def __repr__(self):
        import numpy as np

        return np.get_include()

    __fspath__ = __repr__


PACKAGE_DIR = pt.abspath(pt.dirname(__file__))
OS = platform.system().lower()
NPY_API_VERSION = 'NPY_1_19_API_VERSION'
# build output dir is machine-specific
BUILD_DIR = 'build_' + '_'.join(platform.architecture())
IS64BIT = sys.maxsize > 2**32
ARCH = platform.machine()
if OS == 'darwin':
    # From pybind cmake example:
    # https://github.com/pybind/cmake_example/blob/0e3d4496b4eb1ca904c2f2f5278c5f375f035097/setup.py#L100
    # Cross-compile support for macOS - respect ARCHFLAGS if set
    ARCHFLAGS = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
    # if archflags is given we build in specific subdir
    if ARCHFLAGS:
        BUILD_DIR = 'build_' + '_'.join(ARCHFLAGS)

YASM_VERSION = '1.3.0'
YASM_SOURCE = 'yasm-%s.tar.gz' % YASM_VERSION
YASM_URL = 'https://github.com/yasm/yasm/releases/download/v%s/' % YASM_VERSION + YASM_SOURCE
JPEG_VERSION = '3.1.0'
JPEG_SOURCE = 'libjpeg-turbo-%s.tar.gz' % JPEG_VERSION
JPEG_URL = 'https://github.com/libjpeg-turbo/libjpeg-turbo/archive/%s.tar.gz' % JPEG_VERSION

SKIP_BUILD_NAME = 'skip_build'
SKIP_YASM_BUILD = 'SKIP_YASM_BUILD' in os.environ


def verify_file(path, reference_digest, read_size=128*1024):
    h = hashlib.sha3_256()
    with open(path, 'rb') as fp:
        while True:
            data = fp.read(read_size)
            if not data:
                break
            h.update(data)
    digest = h.hexdigest()
    if reference_digest != digest:
        raise RuntimeError(
            f'Verification of {path} failed, '
            f'expected sha3_256 hash {reference_digest}, '
            f'got {digest}'
        )


def untar_url(url, filename, reference_digest):
    path = filename.rstrip('.tar.gz')
    if not pt.exists(filename):
        os.makedirs(pt.dirname(filename), exist_ok=True)
        print('downloading', url)
        urllib.request.urlretrieve(url, filename)
    if not pt.exists(path):
        print('verifying', filename)
        verify_file(filename, reference_digest)
        os.makedirs(pt.dirname(filename), exist_ok=True)
        with tarfile.open(filename) as t:
            print('extracting', filename)
            t.extractall(pt.dirname(filename))
    return path


# download sources
if not SKIP_YASM_BUILD:
    YASM_DIR = untar_url(
        YASM_URL,
        pt.join(PACKAGE_DIR, 'lib', YASM_SOURCE),
        '56bf07340b7a3bbfec94f89894db2c0d487d534d90c99241ba45b70feaa1a0f3',
    )
JPEG_DIR = untar_url(
    JPEG_URL,
    pt.join(PACKAGE_DIR, 'lib', JPEG_SOURCE),
    '104ff4419619633dd3fb60746d871440d560be0c24780eeca444b6f0a7cf9178',
)


def cvar(name):
    return sysconfig.get_config_var(name)


def make_type():
    if OS in ('linux', 'darwin'):
        return 'Unix Makefiles'
    elif OS == 'windows':
        return 'NMake Makefiles'
    else:
        raise RuntimeError('Platform not supported: %s, %s' % (OS, ARCH))


def touch(path):
    with open(path, 'w') as f:
        pass


class cmake_build_ext(build_ext):
    def run(self):
        skip_path = pt.join(_libdir(), SKIP_BUILD_NAME)
        if not pt.exists(skip_path) or os.getenv('FORCE_BUILD'):
            self.build_cmake_dependencies()
            touch(skip_path)
        else:
            print('Dependencies already built, skipping')
        # build extensions
        super().run()

    def build_cmake_dependencies(self):
        flags = []
        if OS == 'darwin':
            if ARCHFLAGS:
                flags.append("-DCMAKE_OSX_ARCHITECTURES=" + ";".join(ARCHFLAGS))
        if not SKIP_YASM_BUILD:
            self.build_cmake_dependency(YASM_DIR, [
                '-DBUILD_SHARED_LIBS=OFF'
            ])

        cflags = os.getenv('CFLAGS', '')
        ldflags = os.getenv('LDFLAGS', '')
        if OS == 'linux':
            # enable LTO
            cflags = '-flto ' + cflags
            # same as extension
            ldflags = (
                '-flto '
                '-Wl,'  # following are linker options
                '--strip-all,'  # Remove all symbols
                '--exclude-libs,ALL,'  # Do not export symbols
                '--gc-sections '  # Remove unused sections'
            ) + ldflags
        env = {
            # add YASM to the path
            'PATH': pt.join(YASM_DIR, BUILD_DIR) + os.pathsep + os.getenv('PATH', ''),
            # custom CFLAGS - depends on platform
            'CFLAGS': cflags,
            # custom LDFLAGS - depends on platform
            'LDFLAGS': ldflags,
        }
        self.build_cmake_dependency(JPEG_DIR, [
            *flags,
            '-DWITH_CRT_DLL=1',  # fixes https://bugs.python.org/issue24872
            '-DENABLE_SHARED=0',
            '-DREQUIRE_SIMD=1',
            '-DCMAKE_POSITION_INDEPENDENT_CODE=ON',
        ], env=env)

    def build_cmake_dependency(self, path, options, env=None):
        cur_dir = pt.abspath(os.curdir)
        build_dir = pt.join(path, BUILD_DIR)
        if not pt.exists(build_dir):
            os.makedirs(build_dir)
        os.chdir(build_dir)
        config = 'Debug' if self.debug else 'Release'
        env = dict(os.environ, **(env or {}))
        subprocess.check_call([
            CMAKE_PATH,
            '-G' + make_type(), '-Wno-dev',
            '-DCMAKE_BUILD_TYPE=' + config,
            *options,
            pt.join(path)
        ], stdout=sys.stdout, stderr=sys.stderr, env=env)
        if not self.dry_run:
            subprocess.check_call([
                CMAKE_PATH, '--build', '.', '--config', config
            ], stdout=sys.stdout, stderr=sys.stderr, env=env)
        os.chdir(cur_dir)


def _libdir():
    return pt.join(JPEG_DIR, BUILD_DIR)


def _staticlib():
    if OS in ('linux', 'darwin'):
        return 'libturbojpeg.a'
    elif OS == 'windows':
        return 'turbojpeg-static.lib'
    else:
        raise RuntimeError('Platform not supported: %s, %s' % (OS, ARCH))


def make_jpeg_module():
    include_dirs = [
        NumpyImport(),
        pt.join(JPEG_DIR, 'src'),
        pt.join(PACKAGE_DIR, 'simplejpeg'),
    ]
    static_libs = [pt.join(_libdir(), _staticlib())]
    cython_files = [pt.join('simplejpeg', '_jpeg.pyx')]
    for cython_file in cython_files:
        if pt.exists(cython_file):
            cythonize(cython_file)
    sources = [
        pt.join('simplejpeg', '_jpeg.c'),
        pt.join('simplejpeg', '_color.c')
    ]
    extra_link_args = []
    extra_compile_args = []
    macros = [
        ('NPY_NO_DEPRECATED_API', NPY_API_VERSION),
        ('NPY_TARGET_VERSION', NPY_API_VERSION),
    ]
    if OS == 'linux':
        extra_link_args.extend([
            '-Wl,'  # following are linker options
            '--strip-all,'  # Remove all symbols
            '--exclude-libs,ALL,'  # Do not export symbols
            '--gc-sections'  # Remove unused sections
        ])
        extra_compile_args.extend([
            '-flto',  # enable LTO
        ])
    return Extension(
        'simplejpeg._jpeg',
        sources,
        language='C',
        include_dirs=include_dirs,
        extra_objects=static_libs,
        extra_link_args=extra_link_args,
        extra_compile_args=extra_compile_args,
        define_macros=macros,
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


def find_package_data(packages, patterns):
    package_data = {
        package: patterns
        for package in packages
    }
    return package_data


packages = find_packages(
    include=['simplejpeg', 'simplejpeg.*'],
)


include_package_data = find_package_data(packages, ('*.pyi',))
exclude_package_data = find_package_data(packages, ('*.h', '*.c', '*.pyx'))


with open(pt.join(PACKAGE_DIR, 'requirements.txt')) as f:
    dependencies = [l.strip(' \n') for l in f]


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
        with open(self.output_file, encoding='utf-8') as fp:
            self.original_output = fp.read()
        content = [self.original_output]
        for f in self.files:
            with open(f, encoding='utf-8') as fp:
                content.extend([
                    '\n', '\n', self.separator,
                    'Content of: ' + f,
                    self.separator, '\n',
                    fp.read()
                ])
        with open(self.output_file, 'w', encoding='utf-8') as fp:
            fp.write('\n'.join(content))

    def __exit__(self, exception_type, exception_value, traceback):
        with open(self.output_file, 'w', encoding='utf-8') as fp:
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
        packages=packages,
        package_data=include_package_data,
        exclude_package_data=exclude_package_data,
        install_requires=dependencies,
        ext_modules=ext_modules,
        cmdclass={'build_ext': cmake_build_ext},
        zip_safe=False,
    )
