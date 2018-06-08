#!/bin/bash

set -e

COMPILER="gcc"
CMAKE_GENERATOR="Ninja"
BUILD_DIRECTORY="build-in-docker"
SOURCE_DIRECTORY=".."
TARGET=""
CONFIG_TYPE="Debug"
CLEAN="OFF"
CLEAN_ONLY="OFF"
COVERAGE="OFF"
EXAMPLES="OFF"
BENCHMARKS="OFF"
DOCUMENTATION="OFF"
DOCKER_IMAGE_TOOLSET="mroynard/ubuntu-toolset:local"
DOCKER_IMAGE_DOCTOOLSET="mroynard/ubuntu-doctoolset:local"
VERBOSE_TESTS="OFF"
CONAN_REMOTE_NAME="dutiona-lrde"
CONAN_REMOTE_URL="https://api.bintray.com/conan/dutiona/lrde"
CONAN_USER="dutiona"
CONAN_API_KEY="e2a665548385e82bf1ecbb4739d3582b83b8235f"

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

    -f --clean                      empty build directory to force a full rebuild

	--clean-only					only empty build directory and stop

    -o --coverage                   run gcovr coverage tool

    -m --benchmarks                 build the benchmark suite

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
	-m | --benchmarks)
		BENCHMARKS="ON"
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

CONAN_PROFILE="${CC}-${CONFIG_TYPE,,}"
echo "Conan profile : $CONAN_PROFILE"
# configure & build
DOCKER_CMD=$(cat <<- EOM
    export CC=$CC && \
    export CXX=$CXX && \
    $CXX --version && \
    conan remote add $CONAN_REMOTE_NAME $CONAN_REMOTE_URL && \
    conan remote list && \
    conan user -p $CONAN_API_KEY -r $CONAN_REMOTE_NAME $CONAN_USER && \
    conan install $SOURCE_DIRECTORY --build missing -pr $CONAN_PROFILE && _
    cmake -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=$COVERAGE -DWITH_EXAMPLES=$EXAMPLES -DWITH_BENCHMARKS=$BENCHMARKS $SOURCE_DIRECTORY && \
    cmake --build . --target $TARGET --config $CONFIG_TYPE
EOM
)

docker exec -w $WORKDIR $CONTAINER_ID sh -c "$DOCKER_CMD"

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
    # echo "Building in $DOC_BUILD_DIR (host) -> $WORKDIR (docker)"

    # cleaning if needed
    if [ "$CLEAN" == "ON" ]; then
        docker exec --workdir $WORKDIR $CONTAINER_ID sh -c "rm -rf ./*"
    fi

    DOCKER_DOC_CMD=$(cat <<- EOM
    conan remote add $CONAN_REMOTE_NAME $CONAN_REMOTE_URL && \
    conan remote list && \
    conan user -p $CONAN_API_KEY -r $CONAN_REMOTE_NAME $CONAN_USER && \
    conan install $SOURCE_DIRECTORY --build missing -pr $CONAN_PROFILE && \_
    cmake -G $CMAKE_GENERATOR -DWITH_CODE_COVERAGE=OFF -DWITH_EXAMPLES=OFF -DWITH_BENCHMARKS=OFF -DWITH_TESTS=OFF $SOURCE_DIRECTORY
    cmake --build . --target docs
EOM
)
    # configure & make
    docker exec -w $WORKDIR $CONTAINER_ID sh -c "$DOCKER_DOC_CMD"

    # stopping container
    echo "Stopping container $CONTAINER_ID"
    docker stop $CONTAINER_ID > /dev/null

fi
