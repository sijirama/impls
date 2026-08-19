
import (
	"fmt"
)

func binominalCoeff(line, digit int) int {

	res := 1

	if digit > (line - digit) {
		digit = line - digit
	}

	for i := 0; i < digit; i++ {
		res *= line - i
		res /= i + 1
	}

	return res
}

func generate(numRows int) [][]int {
	//var total = math.Pow(2, float64(numRows-1))
	var response [][]int

	for line := 0; line < numRows; line++ {
		var row []int
		for digit := 0; digit <= line; digit++ {
			row = append(row, binominalCoeff(line, digit))
		}
		response = append(response, row)
	}

	fmt.Println(response)
	return response
}
