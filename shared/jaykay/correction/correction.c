
// A typo word and its correct word is encoded in a trie.
// The typo word is inserted into the trie starting with the last
// letter of the word and going backwards. At the leaf node an offset
// to the correct word is stored. The correct word is stored in a
// separate array.

// If bit 31 is set, the node is a leaf node and the other bits are
// the offset to the correct word.

struct cxnode_t
{
    //uint32_t parent_bits; // each bit stands for a letter starting with 'a'
    uint8_t parent_bits;
    // uint8_t parent_bit[]; // depending on the high 2 bits of parent_bits
    // uint16_t parents[]; // offsets to parent nodes
};

// The trie starts with all the possible letters of the alphabet.
struct cxtrie_t
{
    uint16_t nodes[32];
};
