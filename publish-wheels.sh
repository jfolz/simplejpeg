#!/bin/bash
set -e -x

/opt/python/cp37-cp37m/pip install twine
twine upload --skip-existing --disable-progress-bar dist/*
