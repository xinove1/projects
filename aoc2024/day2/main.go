package main

import (
    "fmt"
    "strings"
    "os"
    "strconv"
)

func abs(v int) int{
	if v < 0 {
		return -v
	}
	return v
}

func SliceRemoveIndex(s []int, index int) []int {
	ret := make([]int, 0, len(s)-1)
	ret = append(ret, s[:index]...)
	return append(ret, s[index+1:]...)
}

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := StringToIntArr(string(input_raw))
    //fmt.Println(input)
    fmt.Println("part1: ", part1(input))
    fmt.Println("part2: ", part2(input))
}

func part1(lines [][]int) int {
    safe_count := 0
    for _, line := range lines {
        if (len(line) == 0) {
            continue
        }
        safe := TestSafety(line);
        if safe {
            safe_count += 1
        }
    }
    return safe_count
}

func part2(lines [][]int) int {
    safe_count := 0
    for _, line := range lines {
        if (len(line) == 0) {
            continue
        }
        safe := TestSafety(line);
        if safe == false {
            for i := range line {
                new_line := SliceRemoveIndex(line, i)
                safe = TestSafety(new_line);
                if safe {
                    break
                }
            }
        }
        if safe {
            safe_count += 1
        }
    }
    return safe_count
}

func TestSafety(line []int) bool {
    prev_number := line[0]
    change := 0
    for index := 1; index < len(line); index++ {
        number := line[index]
        if number == prev_number {
            return  false
        }
        diff := prev_number - number
        if change == 0 {
            change = diff
        }
        if (diff < 0 && change > 0 ) || (diff > 0 && change < 0) || abs(diff) > 3 {
            return  false
        }
        prev_number = number
    }
    return true
}

func StringToIntArr(s string) [][]int {
    s_lines := strings.Split(s, "\n")
    r := make([][]int, len(s_lines))
    for i, v := range s_lines {
        v_fields := strings.Fields(v)
        r[i] = make([]int, len(v_fields))
        for k, n := range v_fields {
            number, err := strconv.Atoi(n)
            if err != nil {
                panic(err)
            }
            r[i][k] = number
        }
    }
    return r
}
