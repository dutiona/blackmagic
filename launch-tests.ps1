Param(
    [String]$BuildDirectory = "build-in-docker",
    [String]$ConfigType = "Debug",
    [String]$TestCommand = "ctest --output-on-failure --schedule-random",
    [String]$Verbose = "No"
)

pushd $BUILD_DIRECTORY

If($Verbose -eq "Yes") {
  $TEST_COMMAND - C $CONFIG_TYPE-- verbose
}
Else {
    $TEST_COMMAND - C $CONFIG_TYPE
}

popd
