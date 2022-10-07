# English Dictionary, Correction, Prediction?

Some thoughts on English correction and prediction.

## Characters

- bit 31 = Valid end-of-word
- bit 30 = First letter is upper-case
- bit 29 = Whole word is upper-case
- maximum of 28 characters
- a to z (26)
- -      (1)
- '      (1)

## Tree for Storage

struct wdb_t
{
    u32 branch_letter;        // each bit is a letter (sorted) and the number of set bits is the number of branches
    u32 branch_array_offset;  // offset to array of child nodes (0 = no branch)
};

## Compression by reuse

There are many word endings that can be shared, for example the end part 'ing' or "tions" could be *shared* and thus
saving memory.

As a simple example, all 'a' to 'z' letters that appear at the end of words can be shared.

This can be computed by generating a hash (256 bit) of each node and afterwards build a database of [hash]*node and
use that to remove duplicate (sub-trees) from the tree.

## Dynamic Preference Tracking for Words

Over time we are typing and entering words, how could we mark them as a first preference for selecting the correct word.
We need some augmentation on the Data Structure to track this but we do not have unlimited memory so we should also put
a limit on the number of words we can track.

## String Comparison

### Levenshtein Distance

https://github.com/mcaputto/similitude/blob/master/src/levenshtein.c

### Horner's Rule (hashing)

```c++
    #define HORNER_NUMBER 11
    uint32 horner(char* word) {
        int32  i = 0;
        uint32 total = 0;
        int32  multiple = 1;
        char letter;
        while (word[i] != '\0') {
            char letter = word[i];
            if (letter >= 'A' && letter <= 'Z') {
                letter = letter - 'A';
            } else {
                letter = letter - 'a';
            }
            total = total + (letter * multiple);
            multiple *= HORNER_NUMBER;
            i++;
        }
        return total;
    }
```

## Pseudo Code

uint8_t typing_history[128];     // power-of-2 size
uint8_t typing_history_ri = 0;
uint8_t typing_history_wi = 0;

Fill the typing history on each key press and when 'space' is pressed see if we can complete the word, when completing the word
we should emit the additional characters (and also add them to the typing history).
Backspace should remove the last character from the typing history.

e.g typing 'firetru' and then 'space' should emit 'firetruck' (1st branch)
    typing 'foundat' and then 'space' should emit 'foundation' (1st branch)
    typing 'softwa' and then 'space' should emit 'software' (1st branch)

More complicated:

With look-ahead, after typing 'enginee' we should be able to type 'gs' to complete the word to 'engineerings'.
Or typing 'enginee' and then 'd' it should be able to complete to 'engineered'.

e.g.
'enginee' r
'enginee' red
'enginee' ring
'enginee' rings
'enginee' rs
