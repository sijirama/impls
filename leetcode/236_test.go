package leetcode

import "testing"

func TestLowestCommonAncestorExample1(t *testing.T) {
	root, nodes := lcaExampleTree()
	got := lowestCommonAncestor(root, nodes[5], nodes[1])

	if got != nodes[3] {
		t.Errorf("LCA(5, 1) = %v, want 3", nodeValue(got))
	}
}

func TestLowestCommonAncestorExample2(t *testing.T) {
	root, nodes := lcaExampleTree()
	got := lowestCommonAncestor(root, nodes[5], nodes[4])

	if got != nodes[5] {
		t.Errorf("LCA(5, 4) = %v, want 5", nodeValue(got))
	}
}

func TestLowestCommonAncestorExample3(t *testing.T) {
	root := &TreeNode{Val: 1}
	root.Left = &TreeNode{Val: 2}

	got := lowestCommonAncestor(root, root, root.Left)

	if got != root {
		t.Errorf("LCA(1, 2) = %v, want 1", nodeValue(got))
	}
}

func lcaExampleTree() (*TreeNode, map[int]*TreeNode) {
	nodes := map[int]*TreeNode{}
	for _, value := range []int{3, 5, 1, 6, 2, 0, 8, 7, 4} {
		nodes[value] = &TreeNode{Val: value}
	}

	nodes[3].Left = nodes[5]
	nodes[3].Right = nodes[1]
	nodes[5].Left = nodes[6]
	nodes[5].Right = nodes[2]
	nodes[1].Left = nodes[0]
	nodes[1].Right = nodes[8]
	nodes[2].Left = nodes[7]
	nodes[2].Right = nodes[4]

	return nodes[3], nodes
}

func nodeValue(node *TreeNode) any {
	if node == nil {
		return nil
	}
	return node.Val
}
