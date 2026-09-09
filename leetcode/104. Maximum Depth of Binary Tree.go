package leetcode

import "errors"

type Queue[T any] struct {
	elements []*T
}

func (q *Queue[T]) Enqueue(value *T) {
	q.elements = append(q.elements, value)
}
func (q *Queue[T]) Dequeue() (*T, error) {
	if len(q.elements) == 0 {
		return nil, errors.New("queue is empty")
	}
	value := q.elements[0]
	q.elements[0] = nil
	q.elements = q.elements[1:]
	return value, nil
}
func (q *Queue[T]) isEmpty() bool {
	return len(q.elements) == 0
}
func (q *Queue[T]) size() int {
	return len(q.elements)
}

func maxDepth(root *TreeNode) int {

	if root == nil {
		return 0
	}

	q := &Queue[TreeNode]{}

	q.Enqueue(root)
	max_depth := 0

	for !q.isEmpty() {
		size := q.size()
		for i := 0; i < size; i++ {
			node, err := q.Dequeue()
			if err != nil {
				break
			}
			if node == nil {
				break
			}
			if node.Left != nil {
				q.Enqueue(node.Left)
			}
			if node.Right != nil {
				q.Enqueue(node.Right)
			}

		}
		max_depth++
	}

	return max_depth
}
