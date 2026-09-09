package leetcode

// Definition for a binary tree node.
type TreeNode2 struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type Signed interface {
	~int | ~int8 | ~int16 | ~int32 | ~int64
}

func abs[T Signed](x T) T {
	if x < 0 {
		return -x
	}
	return x
}

func height(root *TreeNode2) int {
	if root == nil {
		return 0
	}

	leftH := height((*TreeNode2)(root.Left))
	rightH := height((*TreeNode2)(root.Right))

	if leftH == -1 || rightH == -1 {
		return -1
	}

	if abs(leftH-rightH) > 1 {
		return -1
	}

	return max(leftH, rightH) + 1
}

func isBalanced(root *TreeNode2) bool {

	balance_factor := height(root)
	return balance_factor != -1
}
