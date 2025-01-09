package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	input_raw, err := os.ReadFile("./input_sample")
	if err != nil {
		panic(err)
	}
	input := strings.Fields(string(input_raw))

	fmt.Println("part1: ", part1(input))
	fmt.Println("part2: ", part2(input))
}

func part1(input []string) int {
	sum := 0
	for y := range input {
		for x := range input[y] {
			sum += checkLine(y, x, input)
			sum += checkDiagonals(y, x, input)
			sum += checkUpDown(y, x, input)
		}
	}
	return sum
}

func part2(input []string) int {
	sum := 0
	m := make([][]byte, len(input))
	for i, v := range input {
		if len(v) != 0 {
			m[i] = []byte(v)
		}
	}
	for y := range m {
		for x, v := range m[y] {
			if v == 'M' || v == 'S' {
				sum += checkXmas(y, x, m)
			}
		}
	}

	// show := make([][]byte, len(input))
	// for y := range show {
	// 	show[y] = make([]byte, len(input[0]))
	// 	for x := range show[y] {
	// 		if m[y][x] == '.' {
	// 			show[y][x] = input[y][x]
	// 		} else {
	// 			show[y][x] = '.'
	// 		}
	// 	}
	// }
	// for _, v := range show {
	// 	fmt.Println(string(v))
	// }
	return sum
}

func checkXmas(y int, x int, str [][]byte) int {
	count := 0
	length := len(str[y])

	if len(str) - y <= 2 {
		return count
	}

	if length - x > 4 && str[y+1][x+1] == 'A' {
		if (str[y][x] == 'M' && str[y+2][x+2] == 'S') || (str[y][x] == 'S' && str[y+2][x+2] == 'M') && (str[y][x+2] == 'M' && str[y+2][x] == 'S') || (str[y][x+2] == 'S' && str[y+2][x] == 'M') {
			//str[y][x] = '.'
			// str[y+2][x+2] = '.'
			// str[y][x+2] = '.'
			// str[y+2][x] = '.'
			// str[y+1][x+1] = '.'
			count += 1
		}
	}
	// if x >= 2 && str[y+1][x-1] == 'A' {
	// 	if (str[y][x] == 'M' && str[y+2][x-2] == 'S') || (str[y][x] == 'S' && str[y+2][x-2] == 'M') && (str[y][x-2] == 'M' && str[y+2][x] == 'S') || (str[y][x-2] == 'S' && str[y+2][x] == 'M') {
	// 		str[y][x] = '.'
	// 		// str[y+2][x-2] = '.'
	// 		// str[y][x-2] = '.'
	// 		// str[y+2][x] = '.'
	// 		// str[y+1][x-1] = '.'
	// 		count += 1
	// 	}
	// }

	return count
}

func checkLine(y int, x int, str []string) int {
	count := 0
	length := len(str[y])
	if length-x >= 4 {
		if str[y][x] == 'X' && str[y][x+1] == 'M' && str[y][x+2] == 'A' && str[y][x+3] == 'S' {
			count += 1
		}
	}
	if x >= 3 {
		if str[y][x] == 'X' && str[y][x-1] == 'M' && str[y][x-2] == 'A' && str[y][x-3] == 'S' {
			count += 1
		}
	}
	return count
}

func checkUpDown(y int, x int, str []string) int {
	count := 0
	line_amount := len(str)

	if line_amount-y >= 4 {
		if str[y][x] == 'X' && str[y+1][x] == 'M' && str[y+2][x] == 'A' && str[y+3][x] == 'S' {
			count += 1
		}
	}
	if y >= 3 {
		if str[y][x] == 'X' && str[y-1][x] == 'M' && str[y-2][x] == 'A' && str[y-3][x] == 'S' {
			count += 1
		}
	}

	return count
}

func checkDiagonals(y int, x int, str []string) int {
	count := 0
	line_length := len(str[y])
	line_amount := len(str)

	if line_length-x >= 4 {
		if line_amount-y >= 4 {
			if str[y][x] == 'X' && str[y+1][x+1] == 'M' && str[y+2][x+2] == 'A' && str[y+3][x+3] == 'S' {
				count += 1
			}
		}
		if y >= 3 {
			if str[y][x] == 'X' && str[y-1][x+1] == 'M' && str[y-2][x+2] == 'A' && str[y-3][x+3] == 'S' {
				count += 1
			}
		}
	}
	if x >= 3 {
		if line_amount-y >= 4 {
			if str[y][x] == 'X' && str[y+1][x-1] == 'M' && str[y+2][x-2] == 'A' && str[y+3][x-3] == 'S' {
				count += 1
			}
		}
		if y >= 3 {
			if str[y][x] == 'X' && str[y-1][x-1] == 'M' && str[y-2][x-2] == 'A' && str[y-3][x-3] == 'S' {
				count += 1
			}
		}
	}

	return count
}

func strcmp(s1, s2 string) bool {
	lens := len(s1)
	if lens > len(s2) {
		lens = len(s2)
	}
	for i := 0; i < lens; i++ {
		if s1[i] != s2[i] {
			return false
		}
	}
	return true
}
