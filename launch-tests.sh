#!/bin/bash

set -e

BUILD_DIRECTORY="build-in-docker"
CONFIG_TYPE="Debug"
TEST_COMMAND="ctest --output-on-failure --schedule-random"
VERBOSE="NO"

USAGE="$(basename "$0") [OPTIONS] -- launch the unit-tests suite

where:
    -h --help                       show this help text

    -b --build-directory Directory  use provided build directory for build artifacts (on host)
                                    default = build-in-docker
    -t --test-command TestCommand   test command to execute to launch the test-suite.
                                    default = ctest --output-on-failure --schedule-random --verbose

    -r --config-type ConfigType     build type. Release|Debug|RelWithDebInfo|MinSizeRel
                                    default = Debug
    -v --verbose YES/NO             verbose output
                                    default = NO
    "

while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
	-h | --help)
		echo "$USAGE"
		exit
		;;
	-b | --build-directory)
		BUILD_DIRECTORY="$2"
		shift 2
		;;
	-t | --test-command)
		TEST_COMMAND="$2"
		shift 2
		;;
	-r | --config-type)
		CONFIG_TYPE="$2"
		shift 2
		;;
	-v | --verbose)
		VERBOSE="YES"
		shift
		;;
	--)
		shift
		;;
	*)
		shift
		;;
	esac
done

pushd $BUILD_DIRECTORY

if [ "$VERBOSE" == "YES" ]; then
    ${TEST_COMMAND} -C ${CONFIG_TYPE} --verbose
else
    ${TEST_COMMAND} -C ${CONFIG_TYPE}
fi

popd
