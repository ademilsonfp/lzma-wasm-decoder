
#include <7zTypes.h>
#include <LzmaDec.h>

#ifndef __LZMA_UTIL_H
#define __LZMA_UTIL_H

#define IN_BUF_SIZE (1 << 16)
#define OUT_BUF_SIZE (1 << 16)

static SRes Decode2(CLzmaDec *state, ISeqOutStream *outStream,
    ISeqInStream *inStream, UInt64 unpackSize);

static SRes Decode(ISeqOutStream *outStream, ISeqInStream *inStream);

#endif
