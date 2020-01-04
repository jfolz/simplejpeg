# stop on errors
# $ErrorActionPreference = "Stop";

# everything happens in lib dir
mkdir -Force lib
cd lib

# download YASM to compile SIMD assembly
if ($env:BITS -eq "64") {
    $arch = "x86_64"
}
else {
    $arch = "i686"
}
$yasm_url = "https://github.com/yasm/yasm/releases/download/v1.3.0/yasm-1.3.0-win" + $env:BITS + ".exe"
Invoke-WebRequest $yasm_url -OutFile yasm.exe
$env:Path += ";" + $(Get-Location)

# checkout specific libjpeg-turbo tag from github
if (!(Test-Path libjpeg-turbo)) {
    git clone --branch 2.0.4 --depth 1 https://github.com/libjpeg-turbo/libjpeg-turbo.git
}

# run vcvarsall - this shitshow is somehow the best "solution"
# first create a temp file
$tempFile = 'vcvars.txt'
# run the vcvarsall.bat with platform name and store the console output in temp file
cmd /c " `"$env:VCVARSALL`" $env:platform && set > `"$tempFile`" "
# parse the temp file and set env vars
Get-Content $tempFile | Foreach-Object {
    if($_ -match "^(.*?)=(.*)$") { 
        Set-Content "env:\$($matches[1])" $matches[2]
    }
}
# remove temp file
Remove-Item $tempFile

# build libjpeg-turbo
cd libjpeg-turbo
mkdir -Force build
cd build
cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="." -DENABLE_SHARED=0 -DREQUIRE_SIMD=1 ..
nmake
cd ..\..\

# copy header and lib to turbojpeg dir
New-Item -Force turbojpeg\windows\$arch -ItemType directory
cp libjpeg-turbo\turbojpeg.h turbojpeg\
cp libjpeg-turbo\build\turbojpeg-static.lib turbojpeg\windows\$arch\

# cleanup
Remove-Item yasm.exe
Remove-Item -Force -Recurse -LiteralPath libjpeg-turbo
cd ..
