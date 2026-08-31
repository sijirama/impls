package leetcode

import "strconv"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func solve(root *TreeNode, result *[]string, temp *string) {

	if root == nil {
		return
	}

	*temp = *temp + strconv.Itoa(root.Val)

	if root.Left == nil && root.Right == nil {
		*result = append(*result, *temp)
		return
	}

	solve(root.Left, result, temp)
	solve(root.Right, result, temp)
	return

}

func binaryTreePaths(root *TreeNode) []string {

	var result []string
	var temp string

	solve(root, &result, &temp)

	return result
}
