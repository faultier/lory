#ifndef LORY_FIXTURES_H
#define LORY_FIXTURES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lory/lory.h>

void LoryTestCreateBitmap(void **bitmap, uint16_t size, LoryPixelFormat format);
void LoryTestReleaseBitmap(void *bitmap, uint16_t size, LoryPixelFormat format);

#ifdef __cplusplus
}
#endif

#endif
