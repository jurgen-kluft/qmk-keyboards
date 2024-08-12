#include QMK_KEYBOARD_H

// The letters, numbers, symbols used for the token generator.
static const char* c_letters = "abcdefghijklmnopqrstuvwxyz";
static const char* c_numbers = "1234567890";
static const char* c_symbols = "!@#$&+=-";

// Take a number of bits from the seed and return them.
// Note: Maximum number of bits that can be taken is 8.
int8_t TakeBits(uint64_t* seed, int8_t n)
{
    int8_t result = *seed & ((1 << n) - 1);
    *seed >>= n;
    *seed = *seed | (result << 64 - n);
    return result;
}

// seed is 64 bits, maximum 12 character word
// Note: word must be null-terminated and can only contain lowercase alpha characters.
uint64_t PassWordToSeed(const char* word)
{
    uint64_t seed = 0;
    while (*word)
    {
        seed = seed << 5;
        seed = seed | (*word - 'a');
        word++;
    }
    return seed;
}

int GenPassword(uint64_t seed, bool _uppercase, bool _numbers, bool _symbols, char* _output_str, int _output_len)
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
    char c;
    int output_len;

    output_len = 0;
    while (output_len < _output_len)
    {
        type = TakeBits(&seed, 2);
        switch (type)
        {
            case 0:
                index = TakeBits(&seed, 5);
                if (_uppercase)
                {
                    c = c_letters[index] - 'a' + 'A';
                }
                else
                {
                    c = c_letters[index];
                }
                break;
            case 1:
                index = TakeBits(&seed, 4);
                c = c_numbers[index];
                break;
            case 2:
            case 3:
                index = TakeBits(&seed, 3);
                c = c_symbols[index];
                break;
        }
        _output_str[output_len++] = c;
    }

    _output_str[_output_len] = '\0';
}
