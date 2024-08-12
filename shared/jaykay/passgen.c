#include QMK_KEYBOARD_H

// The letters, numbers, symbols used for the token generator.
static const char* c_letters = "abcdefghijklmnopqrstuvwxyz";
static const char* c_numbers = "1234567890";
static const char* c_symbols = "!@#$&+=-";

void GenPassword(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* output_str, int _output_len)
{
    // seed is 64 bits, maximum 12 character word

    // 2 bits -> 0 = letters, 1 = numbers, 2 = symbols
    // letters = 5 bits
    // numbers = 4 bits
    // symbols = 3 bits

    // The seed is a word that is used to generate the password:
    // - take 2 bits from the seed
    // - if the bit is 0, take 5 bits and use it to obtain a letter
    // - if the bit is 1, take 4 bits and use it to obtain a number
    // - if the bit is 2, take 3 bits and use it to obtain a symbol
    // - adjust the character set based on the options
    // - repeat until the output length is reached

}
