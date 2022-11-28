package main

type Node struct {
	Letter  rune
	Index   int
	Parents []*Node
}

type Trie struct {
	Nodes   []*Node
	Letters []*Node
}

func NewTrie() *Trie {
	return &Trie{
		Nodes: []*Node{},
	}
}

// NewNode creates a new node and returns it
func (t *Trie) NewNode(letter rune) *Node {
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
	nn := t.NewNode(letter)
	t.Nodes = append(t.Nodes, n)
	n.Parents = append(n.Parents, nn)
	return nn
}

// FindNode finds if there is a parent path for this letter
func (n *Node) FindNode(letter rune) *Node {
	for _, node := range n.Parents {
		if node.Letter == letter {
			return node
		}
	}
	return nil
}

// Add word to the trie
func (t *Trie) Add(word string) {
	// iterate  word in reverse

	r := []rune(word)
	c := r[len(r)-1]
	i := int(c - 'a')

	// if letter is not in the trie, create a new node
	if t.Letters[i] == nil {
		t.Letters[i] = t.NewNode(c)
	}

	node := t.Letters[i]

	// iterate over the rest of the letters
	for j := len(r) - 2; j >= 0; j-- {
		c = r[j]
		i = int(c - 'a')

		// if letter is not in the trie, create a new node
		parent := node.FindNode(c)
		if parent == nil {
			parent = node.NewNode(c, t)
		}
		node = parent
	}

}

// Read line by line
// 'word with typo = correct word'
// from file and add to trie
func main() {
	//	trie := NewTrie()

}
