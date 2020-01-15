# stop on errors
$ErrorActionPreference = "Stop";

# the list of Python interpreters
$interpreters = $env:INTERPRETERS -split ";"

# Compile wheels
foreach ($python in $interpreters){
    & $python\python.exe -m pip install -U pip wheel --no-warn-script-location
    & $python\python.exe -m pip install -r build-requirements.txt --no-warn-script-location
    & $python\python.exe setup.py bdist_wheel --dist-dir=dist
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
}

# Install and test
cd test
foreach ($python in $interpreters){
    & $python\python.exe -m pip install -r ..\test-requirements.txt --no-warn-script-location
    & $python\python.exe -m pip install simplejpeg --no-index -f ..\dist
    & $python\python.exe -m pytest -vv
    if ($LASTEXITCODE -ne 0) { throw "test failed with exit code $LASTEXITCODE" }
}
cd ..
