package main

import (
	"fmt"
	"os"
	"slices"
	"strings"
)

type V2 struct {
	x int
	y int
}

func (v V2) add(b V2) V2 {
	return V2{v.x + b.x, v.y + b.y}
}

func (v V2) subtract(b V2) V2 {
	return V2{v.x - b.x, v.y - b.y}
}

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := strings.Split(string(input_raw), "\n")
	game_map := make([][]byte, len(input)-1)
	for i, v := range input {
		if len(v) != 0 {
			//v = v[:len(v)]
			game_map[i] = []byte(v)
		}
	}
	antennas := get_all_spots(game_map)
	antinodes := produce_anti_nodes(game_map, antennas)
	apply_antinodes(game_map, antinodes)
	fmt.Println(antinodes)
	fmt.Println(antennas)
	print_map(game_map)
	fmt.Println("part1: ", len(antinodes))
}

func apply_antinodes(gmap [][]byte, nodes []V2) {
	for _, pos := range nodes {
		gmap[pos.y][pos.x] = '#'
	}
}

func produce_anti_nodes(gmap [][]byte, m map[rune][]V2) []V2 {
	r := []V2{}

	for _, v := range m {
		fmt.Println("v : ", v)
		for i := 0; i < len(v)-1; i++ {
			for k := i + 1; k < len(v); k++ {
				diff := v[i].subtract(v[k]).add(v[i])
				diff2 := v[k].subtract(v[i]).add(v[k])
				// fmt.Println(diff)
				// fmt.Println(diff2)
				if in_map(gmap, diff) && !slices.Contains(r, diff) {
					r = append(r, diff)
				}
				if in_map(gmap, diff2) && !slices.Contains(r, diff2) {
					r = append(r, diff2)
				}
			}
		}
	}
	return r
}

func in_map(m [][]byte, pos V2) bool {
	if pos.x >= 0 && pos.x < len(m[0]) && pos.y >= 0 && pos.y < len(m) {
		return true
	}
	return false
}

func get_all_spots(game_map [][]byte) map[rune][]V2 {
	r := make(map[rune][]V2, 0)

	for y := range game_map {
		for x := range game_map[y] {
			char := rune(game_map[y][x])
			if char != '.' {
				v, ok := r[char]
				if ok {
					r[char] = append(v, V2{x, y})
				} else {
					r[char] = []V2{{x, y}}
				}
			}
		}
	}

	return r
}

func print_map(game_map [][]byte) {
	fmt.Println("------------------------------------")
	for _, v := range game_map {
		fmt.Println(string(v))
	}
	//bufio.NewReader(os.Stdin).ReadBytes('\n')
}
