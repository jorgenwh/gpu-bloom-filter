CMD_ARGS=""

RELEASE=0
VALGRIND=0
COMPILE=0

for var in "$@" 
do
  if [ "$var" = "-r" ]; then # Release build (optimizied)
    RELEASE=1
  elif [ "$var" = "-v" ]; then # Run valgrind 
    VALGRIND=1
  elif [ "$var" = "-c" ]; then # Only compile without running the output
    COMPILE=1
  fi
done

function ensure_build_dir_exists() {
  if [ ! -d temp/ ]; then
    mkdir temp/
  fi
}

function get_num_cores() {
  NUM_CORES=$(grep -c ^processor /proc/cpuinfo)
}

function run_cmake() {
  CMAKE_ARGS=""

  if [ $RELEASE = 1 ]; then
    CMAKE_ARGS+="-D CMAKE_BUILD_TYPE=Release"
  else
    CMAKE_ARGS+="-D CMAKE_BUILD_TYPE=Debug"
  fi

  cmake .. $CMAKE_ARGS
}

function run_output() {
  printf -- "\n---------- PROGRAM OUTPUT ----------\n"
  ./temp/cubf $CMD_ARGS
}

function run_valgrind() {
  printf -- "\n---------- PROGRAM OUTPUT ----------\n"

  valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --log-file=valgrind-out.txt \
    ./temp/cubf $CMD_ARGS

  printf -- "\n---------- VALGRIND OUTPUT ----------\n"
  cat valgrind-out.txt
  rm valgrind-out.txt
}

ensure_build_dir_exists
cd temp
run_cmake
get_num_cores
make -j${NUM_CORES}
cd ..

# If run valgrind
if [ $VALGRIND = 1 ]; then
  run_valgrind
  exit 0
fi

# Run output
if [ $COMPILE = 0 ]; then
  run_output
  exit 0
fi
