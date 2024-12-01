#ifndef __ENABLE_PASSGEN_H__
#define __ENABLE_PASSGEN_H__
#pragma once

int8_t take_bits(uint64_t* seed, int8_t n);
uint64_t word_to_seed(const char* word);
int32_t generate_pass(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int32_t _output_len);

#else

int32_t generate_pass(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int32_t _output_len)
{
    return 0;
}

#endif