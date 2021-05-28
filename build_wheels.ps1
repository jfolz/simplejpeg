# do not stop on errors, manually catch errors based on exit code
$ErrorActionPreference = "Continue";

# the list of Python interpreters
$pyvers = $env:PYVERS -split ";"

# Compile wheels
foreach ($python in $pyvers){
    & $python\python.exe -m pip install -U pip --no-warn-script-location
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
    & $python\python.exe -m pip install --only-binary ":all:" -r build_requirements.txt --no-warn-script-location
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
    & $python\python.exe -m pip wheel . -v -w dist/ --no-deps --use-feature=in-tree-build
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
    & $python\python.exe -m pip uninstall -r build_requirements.txt
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
}

# Install and test
cd test
foreach ($python in $pyvers){
    & $python\python.exe -m pip install --only-binary ":all:" -r ..\test_requirements.txt --no-warn-script-location
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
    & $python\python.exe -m pip install simplejpeg --no-index -f ..\dist
    if ($LASTEXITCODE -ne 0) { throw "build failed with exit code $LASTEXITCODE" }
    & $python\python.exe -m pytest -vv
    if ($LASTEXITCODE -ne 0) { throw "test failed with exit code $LASTEXITCODE" }
}
cd ..
