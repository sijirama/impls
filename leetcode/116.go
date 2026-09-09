package leetcode

import "fmt"

type Node struct {
	Val   int
	Left  *Node
	Right *Node
	Next  *Node
}

func connect(root *Node) *Node {
	if root == nil {
		return root
	}

	q := &Queue[Node]{}
	q.Enqueue(root)
	var temp []*Node

	for !q.isEmpty() {

		size := q.size()
		temp = make([]*Node, 0, size)

		for i := 0; i < size; i++ {
			node, err := q.Dequeue()
			if err != nil {
				break
			}
			if node == nil {
				break
			}

			if node != nil {
				temp = append(temp, node)
				fmt.Println(node.Val)
			}
			if node.Left != nil {
				q.Enqueue(node.Left)
			}
			if node.Right != nil {
				q.Enqueue(node.Right)
			}
		}

		var point *Node = nil
		for i := len(temp) - 1; i >= 0; i-- {
			temp[i].Next = point
			point = temp[i]
		}

	}

	return root
}
