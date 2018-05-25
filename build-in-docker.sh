#!/bin/bash

set -e

COMPILER="gcc"
CMAKE_GENERATOR="Ninja"
BUILD_DIRECTORY="build-in-docker"
TOOLCHAIN_FILE=""
SOURCE_DIRECTORY=".."
TARGET=""
CONFIG_TYPE="Debug"
CLEAN="OFF"
CLEAN_ONLY="OFF"
COVERAGE="OFF"
EXAMPLES="OFF"
BENCHMARK="OFF"
DOCUMENTATION="OFF"
DOCKER_IMAGE_TOOLSET="mroynard/ubuntu-toolset:local"
DOCKER_IMAGE_DOCTOOLSET="mroynard/ubuntu-doctoolset:local"
VERBOSE_TESTS="OFF"

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
    -r --config-type ConfigType     build type. Release|Debug|RelWithDebInfo|MinSizeRel
                                    default = Debug
    -n --toolchain ToolchainFile    path to the toolchain file (passed with -T to cmake).

    -f --clean                      empty build directory to force a full rebuild

	--clean-only					only empty build directory and stop

    -o --coverage                   run gcovr coverage tool

    -m --benchmark                  build the benchmark suite

    -e --examples                   build the examples

    -d --doc                        build the documentation

	-v --verbose-tests				verbose output for unit tests
    "

while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
	-h | --help)
		echo "$USAGE"
		exit
		;;
	-f | --clean)
		CLEAN="ON"
		shift
		;;
	--clean-only)
		CLEAN="ON"
		CLEAN_ONLY="ON"
		shift
		;;
	-o | --coverage)
	    # FIXME : not working
		# COVERAGE="ON"
		shift
		;;
	-m | --benchmark)
		BENCHMARK="ON"
		shift
		;;
	-e | --examples)
		EXAMPLES="ON"
		shift
		;;
	-d | --doc)
		DOCUMENTATION="ON"
		shift
		;;
	-v | --verbose-tests)
		VERBOSE_TESTS="ON"
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
		BUILD_DIRECTORY="$2"
		shift 2
		;;
	-s | --source-directory)
		SOURCE_DIRECTORY="$2"
		shift 2
		;;
	-t | --target)
		TARGET="$2"
		shift 2
		;;
    -n | --toolchain)
        TOOLCHAIN_FILE="$2"
        shift 2
        ;;
	-r | --config-type)
		CONFIG_TYPE="$2"
		shift 2
		;;
	--)
		shift
		;;
	*)
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


echo "*** BUILDING BINARIES ***"

# Handle toolchain file
if [ !  -z "${TOOLCHAIN_FILE// }" ]; then
    TOOLCHAIN_FILE="-T $TOOLCHAIN_FILE"
fi

# starting container
CONTAINER_ID=$(docker run -itd --rm --mount type=bind,source="$(pwd)",target=/workspace $DOCKER_IMAGE_TOOLSET)
trap "docker exec $CONTAINER_ID true 2> /dev/null && echo 'Aborting...' && docker stop $CONTAINER_ID > /dev/null" EXIT
echo "Running in container $CONTAINER_ID"

# making build directory
WORKDIR=$(docker exec $CONTAINER_ID sh -c "mkdir -p $BUILD_DIRECTORY && cd $BUILD_DIRECTORY && pwd")
echo "Building in $BUILD_DIRECTORY (host) -> $WORKDIR (docker)"

# cleaning if needed
if [ "$CLEAN" == "ON" ]; then
	echo "Cleaning directory $WORKDIR ..."
	docker exec --workdir $WORKDIR $CONTAINER_ID sh -c "rm -rf ./*"
	if [ "$CLEAN_ONLY" == "ON" ]; then
		exit 0
	fi
fi

# configure & build
docker exec -w $WORKDIR $CONTAINER_ID sh -c "export CC=$CC && export CXX=$CXX && $CXX --version && cmake $TOOLCHAIN_FILE -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=$COVERAGE -DWITH_EXAMPLES=$EXAMPLES -DWITH_BENCHMARK=$BENCHMARK $SOURCE_DIRECTORY"
docker exec -w $WORKDIR $CONTAINER_ID sh -c "cmake --build . --target $TARGET --config $CONFIG_TYPE"

# launch unit tests
if [ "VERBOSE_TESTS" == "ON" ]; then
	docker exec -w $WORKDIR $CONTAINER_ID sh -c "ctest --output-on-failure --schedule-random -C $CONFIG_TYPE --verbose"
else
	docker exec -w $WORKDIR $CONTAINER_ID sh -c "ctest --output-on-failure --schedule-random -C $CONFIG_TYPE"
fi

# stopping container
echo "Stopping container $CONTAINER_ID"
docker stop $CONTAINER_ID > /dev/null

# Building documentation
if [ "$DOCUMENTATION" == "ON" ]; then

    echo "*** BUILDING DOCUMENTATION ***"

    CONTAINER_ID=$(docker run -itd --rm --mount type=bind,source="$(pwd)",target=/workspace $DOCKER_IMAGE_DOCTOOLSET)
    trap "docker exec $CONTAINER_ID true 2> /dev/null && echo 'Aborting...' && docker stop $CONTAINER_ID > /dev/null" EXIT
    echo "Running in container $CONTAINER_ID"

    # making build directory
    DOC_BUILD_DIR="$BUILD_DIRECTORY-doc"
    WORKDIR=$(docker exec $CONTAINER_ID sh -c "mkdir -p $DOC_BUILD_DIR && cd $DOC_BUILD_DIR && pwd")
    echo "Building in $DOC_BUILD_DIR (host) -> $WORKDIR (docker)"

    # cleaning if needed
    if [ "$CLEAN" == "ON" ]; then
        docker exec --workdir $WORKDIR $CONTAINER_ID sh -c "rm -rf ./*"
    fi

    # configure & make
    docker exec -w $WORKDIR $CONTAINER_ID sh -c "cmake -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=OFF -DWITH_EXAMPLES=OFF -DWITH_BENCHMARK=OFF -DWITH_TESTS=OFF $SOURCE_DIRECTORY"
    docker exec -w $WORKDIR $CONTAINER_ID sh -c "cmake --build . --target docs"

    # stopping container
    echo "Stopping container $CONTAINER_ID"
    docker stop $CONTAINER_ID > /dev/null

fi
