#include QMK_KEYBOARD_H

// The letters, numbers, symbols used for the token generator.
static const char* c_letters = "abcdefghijklmnopqrstuvwxyzabcdef";
static const char* c_numbers = "1234567890123456";
static const char* c_symbols = "!@#$x+_-";

// Take a number of bits from the seed and return them.
// Note: Maximum number of bits that can be taken is 8.
int8_t take_bits(uint64_t* seed, int8_t n)
{
    if (n == 0)
        return 0;

    int8_t result = *seed & ((1 << n) - 1);
    *seed >>= n;
    *seed = *seed | (result << 64 - n);
    return result;
}

// result is 64 bits
// Note: word must be null-terminated
uint64_t word_to_seed(const char* word)
{
    uint64_t hval = 0;
    while (*word != '\0')
    {
        hval ^= (uint64_t)*word++;
        hval *= ((uint64_t)0x100000001b3ULL);
    }
    return hval;
}

int32_t generate_pass(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int32_t _output_len)
{
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
    int8_t type;
    int8_t index;
    char   c;
    int    output_len;
    
    uint64_t randomizer = seed;

    output_len = 0;
    while (output_len < _output_len)
    {
    skip_char:        
        type = take_bits(&seed, 2);
        switch (type)
        {
            case 0:
                index = take_bits(&seed, 5);
                c = c_letters[index];
                break;
            case 1:
                index = take_bits(&seed, 4);
                c     = c_numbers[index];
                break;
            case 2:
                index = take_bits(&seed, 5);
                if (_uppercase)
                {
                    c = c_letters[index] - 'a' + 'A';
                }
                else
                {
                    c = c_letters[index];
                }
                break;
            case 3:
                index = take_bits(&seed, 3);
                c     = c_symbols[index];
                break;
        }
        _output_str[output_len++] = c;
        take_bits(&seed, take_bits(&randomizer, 1)); // Randomize the seed bit stream
    }

    _output_str[output_len] = '\0';
    return _output_len;
}
