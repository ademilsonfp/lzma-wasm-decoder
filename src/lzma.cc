
#include <emscripten/val.h>
#include <LzmaUtil.c>

#include "lzma.hh"

SRes lzma_read(const ISeqInStream *pp, void *data, size_t *size) {
  lzma_in_stream_t *p = CONTAINER_FROM_VTBL(pp, lzma_in_stream_t, vt);

  if (*size) {
    size_t rest = p->size - p->offset;

    if (rest < (*size)) {
      *size = rest;
    }

    memcpy(data, &p->buffer[p->offset], *size);

    p->offset += (*size);
  }

  return SZ_OK;
}

size_t lzma_write(const ISeqOutStream *pp, const void *data, size_t size) {
  lmza_out_stream_t *p = CONTAINER_FROM_VTBL(pp, lmza_out_stream_t, vt);

  if (size) {
    if (p->buffer != NULL) {
      memcpy(&p->buffer[p->cursor], data, size);
    }

    (p->cursor) += size;
  }

  return size;
}

emscripten::val lzma_decompress(emscripten::val buffer) {
  std::string bufstr = buffer.as<std::string>();
  std::vector<uint8_t> bufvec(bufstr.begin(), bufstr.end());

  uint8_t *in_buffer = &bufvec[0];

  uint64_t out_size = (
    ((uint64_t) in_buffer[5]) |
    (((uint64_t) in_buffer[6]) << 8) |
    (((uint64_t) in_buffer[7]) << 16) |
    (((uint64_t) in_buffer[8]) << 24) |
    (((uint64_t) in_buffer[9]) << 32) |
    (((uint64_t) in_buffer[10]) << 40) |
    (((uint64_t) in_buffer[11]) << 48) |
    (((uint64_t) in_buffer[12]) << 56)
  );

  uint8_t out_buffer[out_size];

  lzma_in_stream_t in_stream;
  in_stream.vt.Read = lzma_read;
  in_stream.size = buffer["byteLength"].as<size_t>();
  in_stream.buffer = in_buffer;
  in_stream.offset = 0;

  lmza_out_stream_t out_stream;
  out_stream.vt.Write = lzma_write;
  out_stream.buffer = out_buffer;
  out_stream.cursor = 0;

  Decode(&out_stream.vt, &in_stream.vt);

  emscripten::val out_val = emscripten::val(emscripten::typed_memory_view(
    out_stream.cursor, out_buffer));

  out_val = emscripten::val::global("Uint8Array").new_(out_val);

  return out_val;
}
