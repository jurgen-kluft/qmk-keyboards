#define ENABLE_PASSGEN
#ifdef ENABLE_PASSGEN
#pragma once

int8_t TakeBits(uint64_t* seed, int8_t n);
uint64_t PassWordToSeed(const char* word);
void GenPassword(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int _output_len);

#else

int GenPassword(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int _output_len)
{
    return 0;
}

#endif