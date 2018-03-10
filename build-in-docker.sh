#!/bin/sh

set -e

BUILD_DIR="build-in-docker"
CMAKE_GENERATOR="Ninja"
COMPILER="gcc"
FORCE_REBUILD="OFF"
RELEASE_TYPE="Debug"
SOURCE_DIRECTORY=".."
DEFAULT_TARGET=""
TOOLCHAIN_ARGS=""
VERBOSE="ON"
BUILD_WITH_CODE_COVERAGE="OFF"
BUILD_AND_RUN_EXAMPLES="ON"
BUILD_AND_RUN_BENCHMARK="ON"
USAGE="$(basename "$0") [OPTIONS] -- execute a build toolchain

where:
    -h --help                       show this help text
    -c --compiler gcc|clang         select the compiler to use
                                    default = gcc
    -g --cmake-generator Generator  use provided cmake generator
                                    default = Unix Makefiles
    -b --build-directory Directory  use provided build directory for build artifacts (on host)
                                    default = build-in-docker
    -s --source-directory Directory use provided source directory to compile
                                    default = ..
    -t --target Target              build target passed to the generated toolchain (make target)
                                    default = all
    -r --release-type ReleaseType   build type. Release|Debug|RelWithDebInfo|MinSizeRel
                                    default = Debug

    -v --verbose                    if passed, enable verbose to underlying commands

    -f --force                      empty build directory to force a full rebuild

    -o --coverage                   run gcovr coverage tool

    -m --benchmark                  build the benchmark suite

    -e --examples                   build the examples
    
    --                              end of arguments for script, pass the rest to the toolchain via cmake -- ...
                                    useful for passing -jX to make
    "

while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
	-h | --help)
		echo "$USAGE"
		exit
		;;
	-f | --force)
		FORCE_REBUILD="ON"
		shift
		;;
	-v | --verbose)
		VERBOSE="ON"
		shift
		;;
	-o | --coverage)
		BUILD_WITH_CODE_COVERAGE="OFF"
		shift
		;;
	-m | --benchmark)
		BUILD_AND_RUN_BENCHMARK="OFF"
		shift
		;;
	-e | --examples)
		BUILD_AND_RUN_EXAMPLES="OFF"
		shift
		;;
	-c | --compiler)
		COMPILER="$2"
		shift 2
		;;
	-g | --cmake-generator)
		CMAKE_GENERATOR="$2"
		shift 2
		;;
	-b | --build-directory)
		BUILD_DIR="$2"
		shift 2
		;;
	-s | --source-directory)
		SOURCE_DIRECTORY="$2"
		shift 2
		;;
	-t | --target)
		DEFAULT_TARGET="$2"
		shift 2
		;;
	-r | --release-type)
		RELEASE_TYPE="$2"
		shift 2
		;;
	--)
		shift
		;;
	*)
		TOOLCHAIN_ARGS="$TOOLCHAIN_ARGS $1"
		shift
		;;
	esac
done

# compiler switch
if [ "$COMPILER" == "gcc" ]; then
	CC="gcc"
	CXX="g++"
else
	CC="clang"
	CXX="clang++"
fi

# docker call
docker run --name docker-builder \
	--interactive --tty --detach --rm \
	--mount type=bind,source="$(pwd)",target=/workspace \
	mroynard/ubuntu-toolset:testing
docker exec docker-builder sh -c "export CC=$CC && export CXX=$CXX && $CXX --version"
docker exec docker-builder sh -c "mkdir -p $BUILD_DIR && cd $BUILD_DIR"
# if [ "$FORCE_REBUILD" == "ON" ]; then docker exec docker-builder sh -c "rm -rf ./*"; fi
if [ "$VERBOSE" == "ON" ]; then docker exec docker-builder sh -c "set -x"; fi
docker exec docker-builder sh -c \
	"cmake -G $CMAKE_GENERATOR " \
	"-DWITH_CODE_COVERAGE=$BUILD_WITH_CODE_COVERAGE " \
	"-DWITH_EXAMPLES=$BUILD_AND_RUN_EXAMPLES " \
	"-DWITH_BENCHMARK=$BUILD_AND_RUN_BENCHMARK " \
	"$SOURCE_DIRECTORY " \
	"-- $TOOLCHAIN_ARGS"
docker exec docker-builder sh -c "cmake --build . --target $DEFAULT_TARGET --config $RELEASE_TYPE"
docker stop docker-builder
