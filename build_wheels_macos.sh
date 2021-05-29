#!/bin/bash
set -e -x

# install pyenv
brew install pyenv
eval "$(pyenv init --path)"

# Compile wheels
for PYVER in ${PYVERS}; do
    pyenv install "${PYVER}"
    pyenv global "${PYVER}"
    pip install -U pip
    pip install -q build
    python -m build --wheel
done

# Bundle external shared libraries into the wheels
pyenv global 3.8-dev
pip install delocate
for whl in wheelhouse/*.whl; do
    delocate-wheel -w dist -v "${whl}"
done

# Install and test
cd test
for PYVER in ${PYVERS}; do
    pyenv global "${PYVER}"
    pip install --only-binary ":all:" -r ../test_requirements.txt
    pip install simplejpeg --no-index -f ../dist
    python -m pytest -vv
done
cd ..
