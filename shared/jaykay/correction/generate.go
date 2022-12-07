package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func FilterMultiChar(c rune) rune {
	if c == 'è' || c == 'é' || c == 'ê' || c == 'ë' {
		c = 'e'
	} else if c == 'î' || c == 'ï' || c == 'ì' || c == 'í' || c == 'ı' {
		c = 'i'
	} else if c == 'ô' || c == 'ö' {
		c = 'o'
	} else if c == 'û' || c == 'ü' {
		c = 'u'
	} else if c == 'à' || c == 'á' || c == 'â' || c == 'ã' || c == 'ä' || c == 'å' {
		c = 'a'
	} else if c == 'ç' {
		c = 'c'
	}
	return c
}

func ReverseWord(word string) string {
	chars := []rune(word)
	for i, j := 0, len(chars)-1; i < j; i, j = i+1, j-1 {
		chars[i], chars[j] = chars[j], chars[i]
	}
	return string(chars)
}

type Node struct {
	Letter     rune
	Index      int
	ChildArray []*Node
	EndWords   []string
}

type Typo struct {
	Hash      uint32
	Typo      string
	Word      string
	Offset    int
	DiffAt    int
	TypoIndex int
	WordIndex int
}

type EndWordTable struct {
	EndWordArray    []string
	EndWordToOffset map[string]uint32
	Letters         map[rune]int
}

func NewEndWordTable() *EndWordTable {
	t := &EndWordTable{
		EndWordArray:    make([]string, 0),
		EndWordToOffset: make(map[string]uint32),
		Letters:         make(map[rune]int),
	}

	// prepare the letters array
	letters := []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789' ")
	for i, c := range letters {
		t.Letters[c] = i
	}
	return t
}

func (e *EndWordTable) LetterToByte(c rune) uint8 {
	return uint8(e.Letters[c])
}

func BuildEndWordTable(tree []*Node) *EndWordTable {
	table := NewEndWordTable()
	offset := uint32(0)
	for _, node := range tree {
		for _, word := range node.EndWords {
			if _, ok := table.EndWordToOffset[word]; !ok {
				table.EndWordArray = append(table.EndWordArray, word)

				// Collect the runes
				for _, c := range word {
					if _, ok := table.Letters[c]; !ok {
						table.Letters[c] = len(table.Letters)
					}
				}

				// Align the length including the null terminator to 4 bytes, by doing
				// this we can manage 65536 * 4 = 256KB of end word data.
				table.EndWordToOffset[word] = uint32(offset)
				offset += (uint32(len(table.EndWordArray)+3) & uint32(0xfffffffc))
			}
		}
	}
	return table
}

func WriteEndWords(w *bufio.Writer, endwords *EndWordTable) {
	for _, word := range endwords.EndWordArray {
		for _, c := range word {
			b := endwords.LetterToByte(c)
			w.WriteByte(b)
		}
		w.WriteByte(0)

		// Align the length including the null terminator to 4 bytes
		l := len(word) + 1
		for l&3 != 0 {
			w.WriteByte(0)
			l++
		}
	}
}

func WriteLettersArray(w *bufio.Writer, endwords *EndWordTable) {

	// collect the letters in a linear array
	letters := make([]rune, len(endwords.Letters))
	for c, i := range endwords.Letters {
		letters[i] = c
	}

	fmt.Fprintf(w, "static const uint16_t letters_array[] = {\n")
	for i, c := range letters {
		if c >= 'a' && c <= 'z' {
			fmt.Fprintf(w, "KC_%c, ", 'A'+(c-'a'))
		} else if c >= 'A' && c <= 'Z' {
			fmt.Fprintf(w, "S(KC_%c), ", c)
		} else if c >= '0' && c <= '9' {
			fmt.Fprintf(w, "KC_%c, ", c)
		} else if c == ' ' {
			fmt.Fprintf(w, "KC_SPC, ")
		} else if c == '\'' {
			fmt.Fprintf(w, "KC_QUOT, ")
		} else if c == '.' {
			fmt.Fprintf(w, "KC_DOT, ")
		} else if c == ',' {
			fmt.Fprintf(w, "KC_COMM, ")
		} else if c == '-' {
			fmt.Fprintf(w, "KC_MINS, ")
		} else if c == '_' {
			fmt.Fprintf(w, "KC_UNDS, ")
		} else {
			// later we can add some unicode support
		}
		if i%8 == 7 {
			fmt.Fprintf(w, "\n")
		}
	}
	fmt.Fprintf(w, "\n};\n\n")
}

func BuildTree(words []string, maxdepth int) []*Node {
	root := &Node{Index: 0, ChildArray: make([]*Node, 0), EndWords: make([]string, 0)}
	nodes := []*Node{root}
	for _, word := range words {
		node := root
		for i, c := range word {

			if i == maxdepth {
				if (i + 1) < len(word) {
					node.EndWords = append(node.EndWords, word[i+1:])
				} else {
					node.EndWords = append(node.EndWords, "")
				}
				break
			}

			found := false
			for _, child := range node.ChildArray {
				if child.Letter == c {
					found = true
					node = child
					break
				}
			}
			if !found {
				child := &Node{Letter: c, Index: len(nodes), ChildArray: []*Node{}, EndWords: []string{}}
				nodes = append(nodes, child)
				node.ChildArray = append(node.ChildArray, child)
				node = child
			}
		}
	}
	return nodes
}

func WriteTree(w *bufio.Writer, tree []*Node, endwords *EndWordTable) {

	fmt.Fprintf(w, "typedef struct {\n")
	fmt.Fprintf(w, "  uint8_t letter;\n")
	fmt.Fprintf(w, "  uint8_t child_array_size;\n")
	fmt.Fprintf(w, "  uint16_t child_array_offset;\n")
	fmt.Fprintf(w, "} cxnode_t;\n\n")

	fmt.Fprintf(w, "typedef struct {\n")
	fmt.Fprintf(w, "  uint16_t count;\n")
	fmt.Fprintf(w, "  uint8_t child_array_size;\n")
	fmt.Fprintf(w, "  uint16_t child_array_offset;\n")
	fmt.Fprintf(w, "} cxendwords_t;\n\n")

	// write out the node array
	fmt.Fprintf(w, "static const cxnode_t cx_node_array[] = {\n")
	offset := uint32(0)
	for _, node := range tree {
		fmt.Fprintf(w, "  { '%c', %d, %d },\n", node.Letter, len(node.ChildArray), offset)
		offset += uint32(len(node.ChildArray))
	}
	fmt.Fprintf(w, "};\n\n")

	// write out the child array's
	fmt.Fprintf(w, "static const uint16_t cx_child_arrays[] = {\n")
	for _, node := range tree {
		for _, child := range node.ChildArray {
			fmt.Fprintf(w, "  %d,", child.Index)
		}
		fmt.Fprintf(w, "\n")
	}
	fmt.Fprintf(w, "};\n\n")

	// write out each node's end word array:
	// for each node the end words are concatenated into a single byte stream, for each
	// word the first byte is the length of the word, followed by the word itself.

	fmt.Fprintf(w, "static const uint8_t cx_endword_arrays[] = {\n")
	offset = 0
	for _, node := range tree {

}

func main() {
	file := "typos_dictionary.txt"
	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	typos := []Typo{}

	scanner := bufio.NewScanner(f)

	minLen := 100
	maxLen := 0
	for scanner.Scan() {
		parts := strings.Split(scanner.Text(), "=")
		if len(parts) != 2 {
			continue
		}

		parts[0] = strings.TrimSpace(parts[0])
		parts[1] = strings.TrimSpace(parts[1])
		parts[0] = strings.ToLower(parts[0])
		corrections := strings.Split(parts[1], ",")
		for i := range corrections {
			corrections[i] = strings.TrimSpace(corrections[i])
		}

		wrong := ReverseWord(parts[0])
		correct := ReverseWord(corrections[0])

		// compute the position of the character where the typo and the word differ
		diffAt := 0
		for p := 0; p < len(wrong) && p < len(correct); p++ {
			if wrong[p] != correct[p] {
				diffAt = p
				break
			}
		}

		typo := Typo{
			Typo:   wrong,
			Word:   correct,
			DiffAt: diffAt,
		}

		typos = append(typos, typo)

		if len(typo.Typo) < minLen {
			minLen = len(typo.Typo)
		}
		if len(typo.Typo) > maxLen {
			maxLen = len(typo.Typo)
		}
	}

	fmt.Printf("minLen: %d\n", minLen)
	fmt.Printf("maxLen: %d\n", maxLen)
	fmt.Printf("count: %d\n", len(typos))

	outputFile := "typos_dictionary.gen"
	f, err = os.Create(outputFile)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	w := bufio.NewWriter(f)

	estimatedMemory := 0

	fmt.Fprintf(w, "#define CORREX_MIN_LEN %d\n", minLen)
	fmt.Fprintf(w, "#define CORREX_MAX_LEN %d\n\n", maxLen)

	estimatedMemory += 4 * 3

	fmt.Printf("Memory size ~= %d\n", estimatedMemory)

	w.Flush()
}
