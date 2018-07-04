Param(
    [String]$Compiler = "gcc",
    [String]$CmakeGenerator = "Ninja",
    [String]$BuildDirectory = "build-in-docker",
    [String]$SourceDirectory = "..",
    [String]$Target = "",
    [String]$ConfigType = "Debug",
    [String]$Coverage = "OFF",
    [String]$Clean = "OFF",
    [String]$ConanUser = "dutiona",
    [String]$ConanRepoName = "dutiona-lrde",
    [String]$ConanRepoURL = "https://api.bintray.com/conan/dutiona/lrde",
    [String]$ConanAPIKey = "e2a665548385e82bf1ecbb4739d3582b83b8235f"
)

$DockerImageToolset = "mroynard/ubuntu-toolset:local"
$DockerImageDoctoolset = "mroynard/ubuntu-doctoolset:local"
$ConanProfile = "$Compiler-$ConfigType".ToLower()

Write-Host "Compiler: $Compiler"
Write-Host "CmakeGenerator: $CmakeGenerator"
Write-Host "BuildDirectory: $BuildDirectory"
Write-Host "SourceDirectory: $SourceDirectory"
Write-Host "Target: $Target"
Write-Host "ConfigType: $ConfigType"
Write-Host "Clean: $Clean"
Write-Host "ConanUser: $ConanUser"
Write-Host "ConanRepoName: $ConanRepoName"
Write-Host "ConanRepoURL: $ConanRepoURL"
Write-Host "ConanAPIKey: $ConanAPIKey"
Write-Host "ConanProfile: $ConanProfile"
Write-Host "DockerImageToolset: $DockerImageToolset"

# compiler switch
If($Compiler -eq "gcc") {
    $CC = "gcc"
    $CXX = "g++"
}
Else {
    $CC = "clang"
    $CXX = "clang++"
}

# starting container
$PwdPath = (Get-Location).Path

Write-Host "*** BUILDING BINARIES ***"
$ContainerID = docker run -itd --rm --mount type=bind,source="$PwdPath",target=/workspace $DockerImageToolset
Write-Host "Running in container $ContainerID"
Trap {
    docker exec $ContainerID true
    Write-Host "Aborting..."
    docker stop $ContainerID
}

# making build directory
$Workdir = docker exec $ContainerID sh -c "mkdir -p $BuildDirectory && cd $BuildDirectory && pwd"
Write-Host "Building in $BuildDirectory (host) -> $Workdir (docker)"

# cleaning if needed
If ($Clean -eq "ON") {
    docker exec --workdir $Workdir $ContainerID sh -c "rm -rf ./*"
}

# configure & make
$DockerCmd = @"
export CC=$CC && \
export CXX=$CXX && \
$CXX --version && \
conan remote add $ConanRepoName $ConanRepoURL && \
conan user -p $ConanAPIKey -r $ConanRepoName $ConanUser && \
conan remote list && \
conan install .. --build missing -pr $ConanProfile && \
cmake $CmakeGenerator -DWITH_TESTS=ON $SourceDirectory && 
cmake --build . --target $Target --config $ConfigType && \
ctest -C $ConfigType --output-on-failure --schedule-random --verbose
"@

docker exec -w $Workdir $ContainerID sh -c "$DockerCmd"

# stopping container
Write-Host "Stopping container $ContainerID"
docker stop $ContainerID
