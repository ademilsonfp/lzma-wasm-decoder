
#include <emscripten/bind.h>
#include "lzma.cc"

EMSCRIPTEN_BINDINGS(lzma) {
  emscripten::function("decompress", &lzma_decompress);
}
