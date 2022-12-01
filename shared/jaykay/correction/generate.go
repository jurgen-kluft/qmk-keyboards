package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
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

type Node struct {
	Letter   rune
	Index    int
	Word     int
	Parent   *Node
	Children []*Node
}

type Trie struct {
	Nodes   []*Node
	Letters []*Node
}

func NewTrie() *Trie {
	return &Trie{
		Nodes:   []*Node{},
		Letters: make([]*Node, 32),
	}
}

// NewNode creates a new node and returns it
func (t *Trie) NewNode(letter rune, parent *Node) *Node {
	n := &Node{
		Letter: letter,
		Index:  len(t.Nodes),
	}
	t.Nodes = append(t.Nodes, n)
	return n
}

// FindNode finds a node in the trie
func (t *Trie) FindNode(letter rune) *Node {
	for _, node := range t.Nodes {
		if node.Letter == letter {
			return node
		}
	}
	return nil
}

// NewNode creates a new node and returns it
func (n *Node) NewNode(letter rune, t *Trie) *Node {
	nn := t.NewNode(letter, n)
	t.Nodes = append(t.Nodes, n)
	n.Children = append(n.Children, nn)
	return nn
}

// FindNode finds if there is a child path for this letter
func (n *Node) FindNode(letter rune) *Node {
	for _, node := range n.Children {
		if node.Letter == letter {
			return node
		}
	}
	return nil
}

// Add word to the trie
func (t *Trie) Add(typo string) int {

	r := []rune(typo)
	c := r[0]
	i := int(c - 'a')

	// if letter is not in the trie, create a new node
	if t.Letters[i] == nil {
		t.Letters[i] = t.NewNode(c, nil)
	}
	node := t.Letters[i]

	// iterate over the rest of the letters
	for _, c := range r[1:] {
		i = int(c - 'a')

		// if letter is not in the trie, create a new node
		child := node.FindNode(c)
		if child == nil {
			child = node.NewNode(c, t)
		}
		node = child
	}
	return node.Index
}

func writeTrie(t *Trie, writer *bufio.Writer) {
	for _, node := range t.Nodes {
		writer.Write([]byte{byte(node.Letter), 0})
		if node.Parent == nil {
			writer.Write([]byte{0, 0})
		} else {
			writer.Write([]byte{byte(node.Parent.Index >> 8), byte(node.Parent.Index & 0xff)})
		}
	}
}

type Typo struct {
	Hash      uint32
	Typo      string
	Word      string
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
	wordTrie := NewTrie()
	typoTrie := NewTrie()

	hashes := map[uint32]bool{}
	hashPools := map[byte]int{}

	scanner := bufio.NewScanner(f)

	typoStringMem := 0

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

		typoLink := typoTrie.Add(parts[0])
		wordLink := wordTrie.Add(parts[1])

		typo := Typo{
			Typo:      parts[0],
			Word:      parts[1],
			TypoIndex: typoLink,
			WordIndex: wordLink,
		}

		typoStringMem += len(typo.Typo) + len(typo.Word) + 2

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

	// runtime:
	// - current length of the typed word
	//   - go into the correction table and get the sub-table for that length
	//   - hash the current typed word
	//   - using the hash of the typed word see if there is an identical typo hash
	//   - if found get the offset to the typo word and compare with the current typed word
	//   - if current typed word == typo word get the offset to the correct word
	//   - correct the typed word

}
