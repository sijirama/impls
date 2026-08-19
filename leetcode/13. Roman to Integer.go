import "fmt"

var romanMap = map[string]int{
	"I": 1,
	"V": 5,
	"X": 10,
	"L": 50,
	"C": 100,
	"D": 500,
	"M": 1000,
}

func romanToInt(s string) int {
	var total int

	prevValue := 0
	for i := len(s) - 1; i >= 0; i-- {
		currentValue := romanMap[string(s[i])]

		if currentValue >= prevValue {
			total += currentValue
		}
		if currentValue < prevValue {
			total -= currentValue
		}
		prevValue = currentValue
	}

	return total
}

func main() {
	fmt.Println(romanToInt("LVIII"))
}
