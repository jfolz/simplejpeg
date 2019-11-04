#!/bin/bash
set -e -x

/opt/python/cp37/pip install twine
twine upload --skip-existing --disable-progress-bar dist/*
