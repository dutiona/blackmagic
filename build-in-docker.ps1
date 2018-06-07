Param(
    [String]$Compiler = "gcc",
    [String]$CmakeGenerator = "Ninja",
    [String]$BuildDirectory = "build-in-docker",
    [String]$SourceDirectory = "..",
    [String]$Target = "",
    [String]$ConfigType = "Debug",
    [String]$Coverage = "OFF",
    [String]$Clean = "OFF",
    [String]$Benchmark = "OFF",
    [String]$Examples = "OFF",
    [String]$Documentation = "OFF",
	[String]$TestsVerbose = "OFF"
)

$DockerImageToolset = "mroynard/ubuntu-toolset:local"
$DockerImageDoctoolset = "mroynard/ubuntu-doctoolset:local"

Write-Host "Compiler: $Compiler"
Write-Host "CmakeGenerator: $CmakeGenerator"
Write-Host "BuildDirectory: $BuildDirectory"
Write-Host "SourceDirectory: $SourceDirectory"
Write-Host "Target: $Target"
Write-Host "ConfigType: $ConfigType"
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
docker exec -w $Workdir $ContainerID sh -c "export CC=$CC && export CXX=$CXX && $CXX --version && cmake -G $CmakeGenerator -DWITH_CODE_COVERAGE=$Coverage -DWITH_EXAMPLES=$Examples -DWITH_BENCHMARKS=$Benchmark $SourceDirectory"
docker exec -w $Workdir $ContainerID sh -c "cmake --build . --target $Target --config $ConfigType"

# Launch tests
If ($TestsVerbose -eq "ON") {
	docker exec -w $Workdir $ContainerID sh -c "ctest --output-on-failure --schedule-random -C $ConfigType --verbose"
}
Else {
	docker exec -w $Workdir $ContainerID sh -c "ctest --output-on-failure --schedule-random -C $ConfigType"
}


# stopping container
Write-Host "Stopping container $ContainerID"
docker stop $ContainerID


if ($Documentation -eq "ON") {
    Write-Host "*** BUILDING DOCUMENTATION ***"

    $ContainerID = docker run -itd --rm --mount type=bind,source="$PwdPath",target=/workspace $DockerImageDoctoolset
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
    docker exec --workdir $Workdir $ContainerID sh -c "cmake -G $CmakeGenerator -DWITH_CODE_COVERAGE=OFF -DWITH_EXAMPLES=OFF -DWITH_BENCHMARKS=OFF -DWITH_TESTS=OFF $SourceDirectory"
    docker exec --workdir $Workdir $ContainerID sh -c "cmake --build . --target docs"

    # stopping container
    Write-Host "Stopping container $ContainerID"
    docker stop $ContainerID
}
