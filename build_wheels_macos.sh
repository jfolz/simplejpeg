#!/bin/bash
set -e -x

# install pyenv
brew install pyenv
eval "$(pyenv init -)"

# Compile wheels
for PYVER in ${PYVERS}; do
    pyenv install "${PYVER}"
    pyenv shell "${PYVER}"
    python -m pip install -U pip
    python -m pip install --only-binary ":all:" -r build_requirements.txt
    python -m pip wheel . -v -w wheelhouse/ --no-deps --use-feature=in-tree-build
    python -m pip uninstall -y numpy oldest-supported-numpy
done

# Bundle external shared libraries into the wheels
pyenv shell 3.8-dev
python -m pip install delocate
for whl in wheelhouse/*.whl; do
    delocate-wheel -w dist -v "${whl}"
done

# Install and test
cd test
for PYVER in ${PYVERS}; do
    pyenv shell "${PYVER}"
    python -m pip install --only-binary ":all:" -r ../test_requirements.txt
    python -m pip install simplejpeg --no-index -f ../dist
    python -m pytest -vv
done
cd ..
