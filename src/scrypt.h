#ifndef SCRYPT_H
#define SCRYPT_H

#include <stdint.h>
#include <stdlib.h>

#include "util.h"
#include "net.h"

#ifdef __cplusplus
extern "C" {
#endif

const int SCRYPT_SCRATCHPAD_SIZE = 131072 + 63;

void scrypt_1024_1_1_256_sp(const char *input, char *output, char *scratchpad);
void scrypt_1024_1_1_256(const char *input, char *output);
uint256 scrypt_salted_multiround_hash(const void* input, size_t inputlen, const void* salt, size_t saltlen, const unsigned int nRounds);
uint256 scrypt_salted_hash(const void* input, size_t inputlen, const void* salt, size_t saltlen);
uint256 scrypt_hash(const void* input, size_t inputlen);
uint256 scrypt_blockhash(const void* input);

#ifdef __cplusplus
}
#endif

#endif
