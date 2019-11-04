#!/bin/bash
set -e -x

/opt/python/cp37-cp37m/bin/pip install twine
twine upload --skip-existing --disable-progress-bar dist/*
