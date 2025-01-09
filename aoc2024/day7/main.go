package main

import (
	"fmt"
	"math"
	"os"
	"slices"
	"strconv"
	"strings"
)

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := inputToIntArr(string(input_raw))
	fmt.Println("part1 :", part1(input))
	fmt.Println("part2 :", part2(input))
	fmt.Println("test: ", toBase3(3))
}

func part1(input [][]int) int {
	r := 0
	for _, equation := range input {
		expected := equation[0]
		factors := equation[1:]
		iterations := math.Pow(2, float64(len(factors)-1))
		var iter uint = 0
		for ; iter < uint(iterations); iter++ {
			re := factors[0]
			for i := 0; i < len(factors)-1; i++ {
				bit := (iter >> i) & 1
				if bit == 0 {
					re = re + factors[i+1]
				} else if bit == 1 {
					re = re * factors[i+1]
				}
			}
			if re == expected {
				r += expected
				break
			}
		}
	}
	return r
}

func part2(input [][]int) int {
	r := 0
	for _, equation := range input {
		expected := equation[0]
		factors := equation[1:]
		iterations := math.Pow(3, float64(len(factors)-1))
		var iter int = 0
		//fmt.Println("for: ", factors)
		for ; iter < int(iterations); iter++ {
			operations_ := toBase3(iter)
			operations := make([]int, len(factors) - len(operations_) - 1)
			operations = slices.Concat(operations, operations_)
			//fmt.Println(operations)
			re := factors[0]
			for i := 0; i < len(factors)-1; i++ {
				bit := 0
				if i < len(operations) {
					bit = operations[i]
				}
				if bit == 0 {
					re = re + factors[i+1]
				} else if bit == 1 {
					re = re * factors[i+1]
				} else if bit == 2 {
					str := fmt.Sprintf("%v%v", re, factors[i+1])
					n, err := strconv.Atoi(str)
					if err != nil {
						panic(err)
					}
					re = n
				}
			}
			if re == expected {
				r += expected
		//		fmt.Println("got for: ", expected, " ", factors, " with: ", operations)
				break
			}
		}
	}
	return r
}

func toBase3(number int) []int {
	r := []int{}
	for {
		if number < 3 {
			r = append(r, number)
			break
		}
		r = append(r, number%3)
		number = number / 3
	}
	slices.Reverse(r)
	return r
}

func inputToIntArr(input string) [][]int {
	splitted := strings.Split(input, "\n")
	r := make([][]int, len(splitted)-1)

	for i, v := range splitted {
		if v == "" {
			break
		}
		s := strings.Fields(v)
		r[i] = make([]int, len(s))
		for k, n := range s {
			if k == 0 {
				n = n[:len(n)-1]
			}
			number, err := strconv.Atoi(n)
			if err != nil {
				panic(err)
			}
			r[i][k] = number
		}
	}
	return r
}

func printTry(expected int, result int, operandis []int, operations []int) {
	return
	op := "+*"
	fmt.Printf("Trying to get %v, with: ", expected)
	for i := range operations {
		fmt.Printf("%v %v ", operandis[i], string(op[operations[i]]))
	}
	fmt.Printf("%v, got = %v\n", operandis[len(operandis)-1], result)
}
