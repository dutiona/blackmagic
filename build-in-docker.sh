#!/bin/sh

set -e

BUILD_DIR="build-in-docker"
CMAKE_GENERATOR="Ninja"
COMPILER="gcc"
FORCE_REBUILD="OFF"
RELEASE_TYPE="Debug"
SOURCE_DIRECTORY=".."
DEFAULT_TARGET=""
TOOLCHAIN_ARGS="-- "
BUILD_WITH_CODE_COVERAGE="OFF"
BUILD_AND_RUN_EXAMPLES="OFF"
BUILD_AND_RUN_BENCHMARK="OFF"
BUILD_DOCUMENTATION="OFF"
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

    -f --force                      empty build directory to force a full rebuild

    -o --coverage                   run gcovr coverage tool

    -m --benchmark                  build the benchmark suite

    -e --examples                   build the examples

    -d --doc                        build the documentation

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
	-o | --coverage)
	    # FIXME : not working
		# BUILD_WITH_CODE_COVERAGE="ON"
		shift
		;;
	-m | --benchmark)
		BUILD_AND_RUN_BENCHMARK="ON"
		shift
		;;
	-e | --examples)
		BUILD_AND_RUN_EXAMPLES="ON"
		shift
		;;
	-d | --doc)
		BUILD_DOCUMENTATION="ON"
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


echo "*** BUILDING BINARIES ***"
# cleaning if needed
if [ "$FORCE_REBUILD" == "ON" ]; then
	rm -rf $BUILD_DIR
fi

# starting container
BIN_CONTAINER_ID=$(docker run -itd --rm --mount type=bind,source="$(pwd)",target=/workspace mroynard/ubuntu-toolset:local)
trap "docker exec $BIN_CONTAINER_ID true 2> /dev/null && echo 'Aborting...' && docker stop $BIN_CONTAINER_ID > /dev/null" EXIT
echo "Running in container $BIN_CONTAINER_ID"

# making build directory
WORKDIR=$(docker exec $BIN_CONTAINER_ID sh -c "mkdir -p $BUILD_DIR && cd $BUILD_DIR && pwd")
echo "Building in $BUILD_DIR (host) -> $WORKDIR (docker)"

# configure & make
docker exec -w $WORKDIR $BIN_CONTAINER_ID sh -c "export CC=$CC && export CXX=$CXX && $CXX --version && cmake -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=$BUILD_WITH_CODE_COVERAGE -DWITH_EXAMPLES=$BUILD_AND_RUN_EXAMPLES -DWITH_BENCHMARK=$BUILD_AND_RUN_BENCHMARK $SOURCE_DIRECTORY"
docker exec -w $WORKDIR $BIN_CONTAINER_ID sh -c "cmake --build . --target $DEFAULT_TARGET --config $RELEASE_TYPE"

# stopping container
echo "Stopping container $BIN_CONTAINER_ID"
docker stop $BIN_CONTAINER_ID > /dev/null

if [ "$BUILD_DOCUMENTATION" == "ON" ]; then

    echo "*** BUILDING DOCUMENTATION ***"
    DOC_BUILD_DIR="$BUILD_DIR-doc"
    # cleaning if needed
    if [ "$FORCE_REBUILD" == "ON" ]; then
        rm -rf $DOC_BUILD_DIR
    fi

    DOC_CONTAINER_ID=$(docker run -itd --rm --mount type=bind,source="$(pwd)",target=/workspace mroynard/ubuntu-doctoolset:local)
    trap "docker exec $DOC_CONTAINER_ID true 2> /dev/null && echo 'Aborting...' && docker stop $DOC_CONTAINER_ID > /dev/null" EXIT
    echo "Running in container $DOC_CONTAINER_ID"

    # making build directory
    WORKDIR=$(docker exec $DOC_CONTAINER_ID sh -c "mkdir -p $DOC_BUILD_DIR && cd $DOC_BUILD_DIR && pwd")
    echo "Building in $DOC_BUILD_DIR (host) -> $WORKDIR (docker)"

    # configure & make
    docker exec -w $WORKDIR $DOC_CONTAINER_ID sh -c "cmake -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=OFF -DWITH_EXAMPLES=OFF -DWITH_BENCHMARK=OFF -DWITH_TESTS=OFF $SOURCE_DIRECTORY"
    docker exec -w $WORKDIR $DOC_CONTAINER_ID sh -c "cmake --build . --target docs"

    # stopping container
    echo "Stopping container $DOC_CONTAINER_ID"
    docker stop $DOC_CONTAINER_ID >/dev/null

fi