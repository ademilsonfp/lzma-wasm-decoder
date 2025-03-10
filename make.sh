#/bin/bash

emcc -lembind \
  src/bindings.cc \
  -O3 \
  -s ENVIRONMENT="web" \
  -s MODULARIZE=1 \
  -s ALLOW_MEMORY_GROWTH \
  -s STACK_SIZE=1MB \
  -s STACK_OVERFLOW_CHECK \
  -s NO_DISABLE_EXCEPTION_CATCHING \
  -o build/lzma.js  \
  -Ilib/lzmasdk \
  -Wno-multichar \
  -Wno-enum-constexpr-conversion \
  -std=c++14 \
  --no-entry
