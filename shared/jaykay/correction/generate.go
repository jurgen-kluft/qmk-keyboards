package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strings"
)

func StringHash(s string) uint32 {
	hash := uint32(0)
	for i := 0; i < len(s); i++ {
		hash += uint32(s[i])
		hash += (hash << 10)
		hash ^= (hash >> 6)
	}
	hash += (hash << 3)
	hash ^= (hash >> 11)
	hash += (hash << 15)
	return hash
}

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

type Typo struct {
	Hash      uint32
	Typo      string
	Word      string
	Offset    int
	DiffAt    int
	TypoIndex int
	WordIndex int
}

func main() {
	file := "typos_dictionary.txt"
	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	links := []Typo{}
	words := []string{}
	typos := []string{}

	hashes := map[uint32]bool{}
	hashPools := map[byte]int{}

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

		typoLink := len(typos)
		wordLink := len(words)

		typos = append(typos, parts[0])
		words = append(words, corrections[0])

		// compute the position of the character where the typo and the word differ
		diffAt := 0
		for p := 0; p < len(parts[0]) && p < len(corrections[0]); p++ {
			if parts[0][p] != corrections[0][p] {
				diffAt = p
				break
			}
		}

		typo := Typo{
			Typo:      parts[0],
			Word:      corrections[0],
			TypoIndex: typoLink,
			WordIndex: wordLink,
			DiffAt:    diffAt,
		}

		// generate a 32-bit hash of typo.Typo
		typo.Hash = StringHash(typo.Typo) & 0xffffffc0

		ht := byte(typo.Hash >> 24)
		hashPools[ht]++

		// check if hash is unique
		if hashes[typo.Hash] {
			// fatal error
			log.Fatal("hash collision")
		}
		hashes[typo.Hash] = true

		links = append(links, typo)

		if len(typo.Typo) < minLen {
			minLen = len(typo.Typo)
		}
		if len(typo.Typo) > maxLen {
			maxLen = len(typo.Typo)
		}
	}

	fmt.Printf("minLen: %d\n", minLen)
	fmt.Printf("maxLen: %d\n", maxLen)
	fmt.Printf("count: %d\n", len(links))

	// sort links array by hash
	sort.Slice(links, func(i, j int) bool {
		return links[i].Hash < links[j].Hash
	})

	outputFile := "typos_dictionary.gen"
	f, err = os.Create(outputFile)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	w := bufio.NewWriter(f)

	estimatedMemory := 0

	for i := minLen; i <= maxLen; i++ {

		// Compute the offset of each typo string in the typo_strs array
		// and the offset of each word string in the word_strs array
		typos := []Typo{}
		for j := 0; j < len(links); j++ {
			if len(links[j].Typo) == i {
				typos = append(typos, links[j])
			}
		}

		// sort typos array by typo string and compute the offsets
		sort.Slice(typos, func(a, b int) bool {
			return typos[a].Typo < typos[b].Typo
		})

		typoOffset := 0
		for j := 0; j < len(typos); j++ {
			typos[j].Offset = typoOffset
			typoOffset += len(typos[j].Typo) + len(typos[j].Word) + 1
		}

		fmt.Fprintf(w, "static const char strs_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprint(w, "    ")
			for _, c := range link.Typo {
				if c == '\'' {
					fmt.Fprintf(w, "'\\%c',", c)
				} else {
					fmt.Fprintf(w, "'%c',", FilterMultiChar(c))
				}
			}

			// emit the diffAt position
			fmt.Fprintf(w, "%d,", link.DiffAt)

			for p, c := range link.Word {
				if p >= link.DiffAt {
					if c == '\'' {
						fmt.Fprintf(w, "'\\%c',", c)
					} else {
						fmt.Fprintf(w, "'%c',", FilterMultiChar(c))
					}
				}
			}
			fmt.Fprintf(w, "0,\n")
			estimatedMemory += len(link.Typo) + 1 + (len(link.Word) - link.DiffAt) + 1
		}
		fmt.Fprintf(w, "};\n\n")

		// sort typos by hash
		sort.Slice(typos, func(a, b int) bool {
			return typos[a].Hash < typos[b].Hash
		})
		fmt.Fprintf(w, "static const uint32_t hashes_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprintf(w, "    0x%08x, // %s -> %s\n", link.Hash, link.Typo, link.Word)
		}
		fmt.Fprintf(w, "};\n\n")

		estimatedMemory += len(typos) * 4

		fmt.Fprintf(w, "static const uint16_t offsets_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprintf(w, "    %d,\n", link.Offset)
		}
		fmt.Fprintf(w, "};\n\n")

		estimatedMemory += len(typos) * 2
	}

	fmt.Fprintf(w, "typedef struct\n")
	fmt.Fprintf(w, "{\n")
	fmt.Fprintf(w, "    uint32_t* hashes;\n")
	fmt.Fprintf(w, "    uint16_t* offsets;\n")
	fmt.Fprintf(w, "    char*     strs;\n")
	fmt.Fprintf(w, "} correx_t;\n\n")
	fmt.Fprintf(w, "static const correx_t correx_data[] = {\n")
	for i := 0; i <= maxLen; i++ {
		if i < minLen {
			fmt.Fprintf(w, "    { NULL, NULL, NULL },\n")
		} else {
			fmt.Fprintf(w, "    { hashes_%d, offsets_%d, strs_%d },\n", i, i, i)
		}
	}
	fmt.Fprintf(w, "};\n\n")

	estimatedMemory += (maxLen + 1) * (3 * 4)

	fmt.Fprintf(w, "#define CORREX_MIN_LEN %d\n", minLen)
	fmt.Fprintf(w, "#define CORREX_MAX_LEN %d\n\n", maxLen)

	estimatedMemory += 4 * 3

	fmt.Printf("Memory size ~= %d\n", estimatedMemory)

	w.Flush()
}
