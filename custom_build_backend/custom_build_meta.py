import shutil

from setuptools import build_meta as _orig
from setuptools.build_meta import *


def _get_cmake_dep():
    if shutil.which('cmake') is None:
        return ['cmake>=3.6.3']
    return []


def get_requires_for_build_editable(config_settings=None):
    return _orig.get_requires_for_build_editable(config_settings) + _get_cmake_dep()


def get_requires_for_build_wheel(config_settings=None):
    return _orig.get_requires_for_build_wheel(config_settings) + _get_cmake_dep()
