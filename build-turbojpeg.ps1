# stop on errors
$ErrorActionPreference = "Stop";

# everything happens in lib dir
mkdir -Force lib
cd lib

# download YASM to compile SIMD assembly
if ([Environment]::Is64BitOperatingSystem) {
    $bits = 64
    $arch = "AMD64"
}
else {
    $bits = 32
    $arch = "x86"
}
$yasm_url = "https://github.com/yasm/yasm/releases/download/v1.3.0/yasm-1.3.0-win" + $bits + ".exe"
Invoke-WebRequest $yasm_url -OutFile yasm.exe
$env:Path += ";" + $(Get-Location)
$env:Path += ";" + "C:\Users\riDDi\Miniconda3\Library\bin"

# checkout specific libjpeg-turbo tag from github
if (!(Test-Path libjpeg-turbo)) {
    git clone --quiet --branch 2.0.4 --depth 1 https://github.com/libjpeg-turbo/libjpeg-turbo.git
}

# run vcvarsall - this shitshow is somehow the best "solution"
# first create a temp file
$tempFile = [IO.Path]::GetTempFileName()
# locate appropriate vcvars.bat for system
$vcvars = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars" + $bits  + ".bat"
# run the vcvars.bat and store the console output in temp file
cmd /c " `"$vcvars`" && set > `"$tempFile`" "
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
