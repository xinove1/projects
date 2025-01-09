package main

import (
	"fmt"
	"os"
	"strconv"
	//"strings"
	"unicode"
)

type Indentifier int

const (
	IdEmpty Indentifier = iota
	IdMul
	IdDo
	IdDoNot
)

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := string(input_raw)

	count_all := 0
	count_enabled_only := 0
	enabled := true

	command := input[:]
	for range command {
		id, pos := getNextIdentifier(command)
		if id == IdMul {
			n := readMul(command[pos+4:])
			count_all += n
			if enabled {
				count_enabled_only += n
			}
		} else if id == IdDo {
			enabled = true
		} else if id == IdDoNot {
			enabled = false
		} else if id == IdEmpty {
			break
		} else {
			panic("uepa");
		}
		command = command[pos+1:]
	}

	fmt.Println("part 1: ", count_all)
	fmt.Println("part 2: ", count_enabled_only)
}

func getNextIdentifier(command string) (Indentifier, int) {
	for i := range command {
		if strcmp("mul(", command[i:]) {
			return IdMul, i
		}
		if strcmp("do()", command[i:]) {
			return IdDo, i
		}
		if strcmp("don't()", command[i:]) {
			return IdDoNot, i
		}
	}
	return IdEmpty, -1
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

func readMul(command string) int {
	n1, end := readNumber(command, ',')
	if end == -1 {
		return 0
	}
	n2, end := readNumber(command[end:], ')')
	if end == -1 {
		return 0
	}
	return n1 * n2
}

func readNumber(command string, stopper rune) (int, int) {
	number := 0
	end := 0

	for i, c := range command {
		if c == stopper {
			end = i
			break
		}
		if !unicode.IsDigit(c) {
			end = -1
			break
		}
	}
	if end != -1 {
		n, err := strconv.Atoi(command[:end])
		if err != nil {
			panic(err)
		}
		number = n
		end++
	}

	return number, end
}
