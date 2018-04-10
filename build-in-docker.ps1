Param(
    [String]$Compiler = "gcc",
    [String]$CmakeGenerator = "Ninja",
    [String]$BuildDirectory = "build-in-docker",
    [String]$SourceDirectory = "..",
    [String]$Target = "",
    [String]$ReleaseType = "Debug",
    [String]$Coverage = "OFF",
    [String]$Clean = "OFF",
    [String]$Benchmark = "OFF",
    [String]$Examples = "OFF",
    [String]$Documentation = "OFF"
)

Write-Host "Compiler: $Compiler"
Write-Host "CmakeGenerator: $CmakeGenerator"
Write-Host "BuildDirectory: $BuildDirectory"
Write-Host "SourceDirectory: $SourceDirectory"
Write-Host "Target: $Target"
Write-Host "ReleaseType: $ReleaseType"
Write-Host "Coverage: $Coverage"
Write-Host "Clean: $Clean"
Write-Host "Benchmark: $Benchmark"
Write-Host "Examples: $Examples"
Write-Host "Documentation: $Documentation"

# compiler switch
If($Compiler -eq "gcc") {
    $CC = "gcc"
    $CXX = "g++"
}
Else {
    $CC = "clang-6.0"
    $CXX = "clang++-6.0"
}

# starting container
$PwdPath = (Get-Location).Path

Write-Host "*** BUILDING BINARIES ***"
$ContainerID = docker run -itd --rm --mount type=bind,source="$PwdPath",target=/workspace mroynard/ubuntu-toolset:local
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
docker exec -w $Workdir $ContainerID sh -c "export CC=$CC && export CXX=$CXX && $CXX --version && cmake -G $CmakeGenerator -DWITH_CODE_COVERAGE=$Coverage -DWITH_EXAMPLES=$Examples -DWITH_BENCHMARK=$Benchmark $SourceDirectory"
docker exec -w $Workdir $ContainerID sh -c "cmake --build . --target $Target --config $ReleaseType"

# stopping container
Write-Host "Stopping container $ContainerID"
docker stop $ContainerID


if ($Documentation -eq "ON") {
    Write-Host "*** BUILDING DOCUMENTATION ***"

    $ContainerID = docker run -itd --rm --mount type=bind,source="$PwdPath",target=/workspace mroynard/ubuntu-doctoolset:local
    Write-Host "Running in container $ContainerID"
    Trap {
        docker exec $ContainerID true
        Write-Host "Aborting..."
        docker stop $ContainerID
    }

    # making build directory
    $DocBuildDirectory = "$BuildDirectory-doc"
    $Workdir = docker exec $ContainerID sh -c "mkdir -p $DocBuildDirectory && cd $DocBuildDirectory && pwd"
    Write-Host "Building in $DocBuildDirectory (host) -> $Workdir (docker)"

    # cleaning if needed
    If ($Clean -eq "ON") {
        docker exec --workdir $Workdir $ContainerID sh -c "rm -rf ./*"
    }

    # configure & make
    docker exec --workdir $Workdir $ContainerID sh -c "cmake -G $CmakeGenerator -DWITH_CODE_COVERAGE=OFF -DWITH_EXAMPLES=OFF -DWITH_BENCHMARK=OFF -DWITH_TESTS=OFF $SourceDirectory"
    docker exec --workdir $Workdir $ContainerID sh -c "cmake --build . --target docs"

    # stopping container
    Write-Host "Stopping container $ContainerID"
    docker stop $ContainerID
}
