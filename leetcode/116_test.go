package leetcode

import (
	"fmt"
	"testing"
)

func TestConnectPerfectTree(t *testing.T) {
	root := &Node{Val: 1}
	root.Left = &Node{Val: 2}
	root.Right = &Node{Val: 3}
	root.Left.Left = &Node{Val: 4}
	root.Left.Right = &Node{Val: 5}
	root.Right.Left = &Node{Val: 6}
	root.Right.Right = &Node{Val: 7}

	connect(root)

	fmt.Printf("level 0: %d -> %v\n", root.Val, valueOf(root.Next))
	fmt.Printf("level 1: %d -> %d -> %v\n",
		root.Left.Val,
		root.Left.Next.Val,
		valueOf(root.Right.Next),
	)
	fmt.Printf("level 2: %d -> %d -> %d -> %v\n",
		root.Left.Left.Val,
		root.Left.Left.Next.Val,
		root.Left.Right.Next.Val,
		valueOf(root.Right.Right.Next),
	)

	if root.Next != nil {
		t.Errorf("root.Next = %v, want nil", root.Next.Val)
	}
	if root.Left.Next != root.Right {
		t.Errorf("2.Next = %v, want 3", valueOf(root.Left.Next))
	}
	if root.Right.Next != nil {
		t.Errorf("3.Next = %v, want nil", root.Right.Next.Val)
	}
	if root.Left.Left.Next != root.Left.Right {
		t.Errorf("4.Next = %v, want 5", valueOf(root.Left.Left.Next))
	}
	if root.Left.Right.Next != root.Right.Left {
		t.Errorf("5.Next = %v, want 6", valueOf(root.Left.Right.Next))
	}
	if root.Right.Left.Next != root.Right.Right {
		t.Errorf("6.Next = %v, want 7", valueOf(root.Right.Left.Next))
	}
	if root.Right.Right.Next != nil {
		t.Errorf("7.Next = %v, want nil", root.Right.Right.Next.Val)
	}
}

func TestConnectEmptyTree(t *testing.T) {
	if got := connect(nil); got != nil {
		t.Errorf("connect(nil) = %v, want nil", got)
	}
}

func valueOf(node *Node) any {
	if node == nil {
		return nil
	}
	return node.Val
}
