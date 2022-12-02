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

type Typo struct {
	Hash       uint32
	Typo       string
	TypoOffset int
	Word       string
	WordOffset int
	TypoIndex  int
	WordIndex  int
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
		parts[1] = strings.ToLower(parts[1])

		typoLink := len(typos)
		wordLink := len(words)

		typos = append(typos, parts[0])
		words = append(words, parts[1])

		typo := Typo{
			Typo:      parts[0],
			Word:      parts[1],
			TypoIndex: typoLink,
			WordIndex: wordLink,
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

	// sort links array by hash
	sort.Slice(links, func(i, j int) bool {
		return links[i].Hash < links[j].Hash
	})

	// write-out in C source code format (according to the code in 'correx.c')

	outputFile := "typos_dictionary.c"
	f, err = os.Create(outputFile)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	w := bufio.NewWriter(f)

	// struct correx_t
	// {
	//     int32_t   count;
	//     uint32_t* hashes;
	//     uint16_t* typo_jmps;
	//     uint8_t*  typo_strs;
	//     uint16_t* corr_jmps;
	//     uint8_t*  corr_strs;
	// };

	fmt.Fprintf(w, "struct correx_t\n")
	fmt.Fprintf(w, "{\n")
	fmt.Fprintf(w, "    int32_t   count;\n")
	fmt.Fprintf(w, "    uint32_t* hashes;\n")
	fmt.Fprintf(w, "    uint16_t* typo_jmps;\n")
	fmt.Fprintf(w, "    uint8_t*  typo_strs;\n")
	fmt.Fprintf(w, "    uint16_t* corr_jmps;\n")
	fmt.Fprintf(w, "    uint8_t*  corr_strs;\n")
	fmt.Fprintf(w, "};\n\n")

	// struct correx_table_t
	// {
	//     int8_t   minlen;
	//     int8_t   maxlen;
	//     correx_t* lengths;
	// };

	fmt.Fprintf(w, "struct correx_table_t\n")
	fmt.Fprintf(w, "{\n")
	fmt.Fprintf(w, "    int8_t   minlen;\n")
	fmt.Fprintf(w, "    int8_t   maxlen;\n")
	fmt.Fprintf(w, "    correx_t* lengths;\n")
	fmt.Fprintf(w, "};\n\n")

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
		wordOffset := 0
		for j := 0; j < len(typos); j++ {
			typos[j].TypoOffset = typoOffset
			typos[j].WordOffset = wordOffset

			typoOffset += len(typos[j].Typo) + 1
			wordOffset += len(typos[j].Word) + 1
		}

		fmt.Fprintf(w, "uint8_t typo_strs_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprint(w, "    ")
			for _, c := range link.Typo {
				fmt.Fprintf(w, "'%c',", c)
			}
			fmt.Fprintf(w, "0,\n")
		}
		fmt.Fprintf(w, "};\n\n")

		fmt.Fprintf(w, "uint8_t word_strs_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprint(w, "    ")
			for _, c := range link.Word {
				fmt.Fprintf(w, "'%c',", c)
			}
			fmt.Fprintf(w, "0,\n")
		}
		fmt.Fprintf(w, "};\n\n")

		// sort typos by hash
		sort.Slice(typos, func(a, b int) bool {
			return typos[a].Hash < typos[b].Hash
		})
		fmt.Fprintf(w, "uint32_t hashes_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprintf(w, "    0x%08x, // %s\n", link.Hash, link.Typo)
		}
		fmt.Fprintf(w, "};\n\n")

		fmt.Fprintf(w, "uint16_t typo_jmps_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprintf(w, "    %d,\n", link.TypoOffset)
		}
		fmt.Fprintf(w, "};\n\n")

		fmt.Fprintf(w, "uint16_t word_jmps_%d[] = {\n", i)
		for _, link := range typos {
			fmt.Fprintf(w, "    %d,\n", link.WordOffset)
		}
		fmt.Fprintf(w, "};\n\n")
	}

	fmt.Fprintf(w, "correx_t typo_table[] = {\n")
	for i := minLen; i <= maxLen; i++ {
		fmt.Fprintf(w, "    { %d, hashes_%d, typo_jmps_%d, typo_strs_%d, word_jmps_%d, word_strs_%d },\n", i, i, i, i, i, i)
	}
	fmt.Fprintf(w, "};\n\n")

	fmt.Fprintf(w, "correx_table_t correx_table = {\n")
	fmt.Fprintf(w, "    %d, %d, typo_table\n", minLen, maxLen)
	fmt.Fprintf(w, "};\n\n")

	w.Flush()
}
