#pragma once

#include <emscripten/val.h>
#include <LzmaUtil.h>

typedef struct {
  ISeqInStream vt;
  size_t size;
  size_t offset;
  uint8_t *buffer;
} lzma_in_stream_t;

typedef struct {
  ISeqOutStream vt;
  size_t cursor;
  uint8_t *buffer;
} lmza_out_stream_t;

SRes lzma_read(const ISeqInStream *, void *, size_t *);
size_t lzma_write(const ISeqOutStream *, const void *, size_t);
emscripten::val lzma_decompress(emscripten::val);
