package main

import (
	"fmt"
	"os"
	"strings"
	"strconv"
	"math"
)

func abs(v int) int{
	if v < 0 {
		return -v
	}
	return v
}


var column_left, column_right []int

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := strings.Fields(string(input_raw))
	column_left = make([]int, 0)
	column_right = make([]int, 0)
	for i, v:= range(input) {
		number, err := strconv.Atoi(v)
		if err != nil {
			panic(err)
		}
		if i % 2 == 0 {
			column_left = append(column_left, number)
		} else {
			column_right = append(column_right, number)
		}
	}
	
	part2()
	part1()
}

func part2() {
	sum := 0
	for _, v1 := range column_left {
		repeat_sum := 0
		for _, v2 := range column_right {
			if v1 == v2 {
				repeat_sum += 1
			}
		}
		sum += v1 * repeat_sum
	}
	fmt.Println("part2: ", sum)
}

func part1() {
	count := 0
	for ; ; {
		min1_index := 0
		min1 := int(math.MaxUint >> 1)
		for i, value := range column_left {
			if value < 0 {
				continue
			}
			if (value < min1) {
				min1 = value
				min1_index = i
			}
		}
		min2_index := 0
		min2 := int(math.MaxUint >> 1)
		for i, value := range column_right {
			if value < 0 {
				continue
			}
			if (value < min2) {
				min2 = value
				min2_index = i
			}
		}
		if min1 == int(math.MaxUint >> 1) {
			break
		}
		count += abs(min1 - min2)
		column_left[min1_index] = -1
		column_right[min2_index] = -1
	}
	fmt.Println("part1: ", count)
}
