package main

import (
	"bufio"
	"log"
	"os"
	"strings"
)

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
		Letters: []*Node{},
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

func main() {
	file := "typos_dictionary.txt"
	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	links := map[int]int{}
	wordTrie := NewTrie()
	typoTrie := NewTrie()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		parts := strings.Split(scanner.Text(), "=")
		if len(parts) != 2 {
			continue
		}

		typoLink := typoTrie.Add(strings.TrimSpace(parts[0]))
		wordLink := wordTrie.Add(strings.TrimSpace(parts[1]))
		links[typoLink] = wordLink
	}
}
