package main

import (
	"fmt"
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
	input := strings.Split(string(input_raw), "\n\n")
	before_map := make(map[int][]int)
	after_map := make(map[int][]int)
	{
		rules := strings.Fields(input[0])
		for _, v := range rules {
			pair := strings.Split(v, "|")
			left, err := strconv.Atoi(pair[0])
			if err != nil {
				panic(err)
			}
			right, err := strconv.Atoi(pair[1])
			if err != nil {
				panic(err)
			}
			map_append(before_map, left, right)
			map_append(after_map, right, left)
		}
	}
	updates := make([][]int, 0, 100)
	{
		updates_str := strings.Fields(input[1])
		for _, v := range updates_str {
			update := strings.Split(v, ",")
			arr := make([]int, len(update))
			for i, b := range update {
				number, err := strconv.Atoi(b)
				if err != nil {
					panic(err)
				}
				arr[i] = number
			}
			updates = append(updates, arr)
		}
	}
	//fmt.Println(before_map)
	fmt.Println(updates)
	fmt.Println("rules: ", before_map[97])
	fmt.Println("part1: ", part1(updates, [2]map[int][]int{before_map, after_map}))
}

func part1(updates [][]int, rules [2]map[int][]int) int {
	result := 0

	for _, update := range updates {
		valid := true
		for page := range update {
			valid = validatePageUpdate(update, page, rules)
			if !valid {
				break
			}
		}
		if valid {
			value := update[len(update)/2]
			result += value
			fmt.Println("a: ", value, "from : ", update)
		}
	}

	return result
}

func validatePageUpdate(update []int, page int, rules [2]map[int][]int) bool {
	r := true
	length := len(update)
	pn := update[page]
	for i := page + 1; i < length; i++ {
		n := update[i]
		nn := rules[0][n]
		if slices.Contains(nn, pn) {
			fmt.Println("rules:  of", n, " in", nn)
			return false
		}
	}
	nn := rules[0][pn]
	for i := page - 1; i >= 0; i-- {
		n := update[i]
		if slices.Contains(nn, n) {
			fmt.Println("123orxbaa")
			return false
		}
	}
	return r
}

func map_append(m map[int][]int, key, value int) {
	v, ok := m[key]
	if ok {
		m[key] = append(v, value)
	} else {
		arr := make([]int, 1, 100)
		arr[0] = value
		m[key] = arr
	}
}
