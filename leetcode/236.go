package leetcode

var buffer [2]bool = [2]bool{false, false} // p, q

func LCH(root, p, q, result *TreeNode) {
	if root == nil {
		return
	}

	lowestCommonAncestor(root.Left, p, q)
	lowestCommonAncestor(root.Right, p, q)

	if buffer[0] && buffer[1] {
		result = root
		return
	}

	if root == p && buffer[1] == true {
		result = root
		return
	}

	if root == q && buffer[0] == true {
		result = root
		return
	}

	if root == p {
		buffer[0] = true
	}

	if root == q {
		buffer[1] = true
	}

}

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {

	result := new(TreeNode)
	result = root

	LCH(root, p, q, result)

	return result
}
