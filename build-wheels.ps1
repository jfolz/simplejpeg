# stop on errors
$ErrorActionPreference = "Stop";

# the list of Python interpreters
$interpreters = $env:INTERPRETERS -split ";"

# Compile wheels
foreach ($python in $interpreters){
    & $python\python.exe -m pip install -U pip wheel --no-warn-script-location
    & $python\python.exe -m pip install -r build-requirements.txt --no-warn-script-location
    & $python\python.exe -m pip wheel . -w dist --no-deps
    & $python\python.exe -m pip install -r test-requirements.txt --no-warn-script-location
    & $python\python.exe -m pip install .
    cd test
    & $python\python.exe -m pytest -vv
    cd ..
}
