#!/bin/bash
set -e -x

PYTHON_VENVS=(~/venv3.5 ~/venv3.6 ~/venv3.7 ~/venv3.8)

# Compile wheels
for VENV in "${PYTHON_VENVS[@]}"; do
    source ${VENV}/bin/activate
    OLDPIP=$("pip" freeze --all | grep '^pip==' | tr -d '\n')
    OLDWHEEL=$("pip" freeze --all | grep '^wheel==' | tr -d '\n')
    pip install -U pip wheel --no-warn-script-location
    pip install -r build_requirements.txt
    pip wheel . -v -w wheelhouse/ --no-deps
    pip install --force "$OLDPIP" "$OLDWHEEL"
    deactivate
done

# Bundle external shared libraries into the wheels
source ~/venv3.8/bin/activate
pip install delocate
for whl in wheelhouse/*.whl; do
    delocate-wheel -w dist -v "$whl"
done
deactivate

# Install and test
cd test
for VENV in "${PYTHON_VENVS[@]}"; do
    source ${VENV}/bin/activate
    pip install -r ../test_requirements.txt
    pip install simplejpeg --no-index -f ../dist
    python -m pytest -vv
    deactivate
done
cd ..
