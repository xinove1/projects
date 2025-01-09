package main

import (
	"fmt"
	"os"
	"slices"
	"strings"
)

type v2 struct {
	x int
	y int
}

func (v v2) add(b v2) v2 {
	return v2{v.x + b.x, v.y + b.y}
}

var Count = 1

var WentPositions = make([]v2, 0, 1000)

func main() {
	input_raw, err := os.ReadFile("./input")
	if err != nil {
		panic(err)
	}
	input := strings.Split(string(input_raw), "\n")
	game_map := make([][]byte, len(input)-1)
	for i, v := range input {
		if len(v) != 0 {
			game_map[i] = []byte(v)
		}
	}
	guard_pos := findGuard(game_map)
	guard_dir := v2{0, -1}
	fmt.Println(guard_pos)

	expected_iterations := part1(game_map, guard_pos, guard_dir)

	fmt.Println("part1 :", Count)
	fmt.Println("part2 :", part2(game_map, guard_pos, guard_dir, expected_iterations))
	fmt.Println(expected_iterations)
	//fmt.Println(WentPositions)
}

func part2(game_map [][]byte, pos v2, dir v2, expected_iter int) int {
	count := 0
	//g_map := copyGameMap(game_map)
	for _, v := range WentPositions {
		//fmt.Println(v)
		g_map := copyGameMap(game_map)
		g_map[v.y][v.x] = '#'
		gpos := v2{pos.x, pos.y}
		gdir := v2{dir.x, dir.y}
		for iter := 0; updateGame(g_map, &gpos, &gdir, false, false); iter++ {
			if iter > expected_iter * 2 {
				count++
				g_map[v.y][v.x] = 'O'
				//print_map(g_map)
				break
			}
		}
		g_map[v.y][v.x] = '.'
	}
	return count
}

func part1(game_map [][]byte, pos v2, dir v2) int {
	iterations := 0
	//gmap := slices.Clone(game_map)
	gmap := copyGameMap(game_map)
	gpos := v2{pos.x, pos.y}
	gdir := v2{dir.x, dir.y}
	for updateGame(gmap, &gpos, &gdir, true, true) {
		iterations++
	}
	return iterations
}

func print_map(game_map [][]byte) {
	fmt.Println("------------------------------------")
	for _, v := range game_map {
		fmt.Println(string(v))
	}
	//bufio.NewReader(os.Stdin).ReadBytes('\n')
}

func copyGameMap(game_map [][]byte) [][]byte {
	g_map := make([][]byte, len(game_map))
	for i, v := range game_map {
		g_map[i] = make([]byte, len(v))
		for k, va := range v {
			g_map[i][k] = va
		}
	}
	return g_map
}

func updateGame(gmap [][]byte, pos *v2, dir *v2, update_location bool, update_went bool) bool {
	new_pos := pos.add(*dir)
	if new_pos.x < 0 || new_pos.x >= len(gmap[0]) || new_pos.y < 0 || new_pos.y >= len(gmap) {
		if update_location {
			gmap[pos.y][pos.x] = 'X'
		}
		return false
	}
	v := &gmap[new_pos.y][new_pos.x]
	if *v == '#' {
		if dir.y == -1 {
			*dir = v2{1, 0}
		} else if dir.x == 1 {
			*dir = v2{0, 1}
		} else if dir.y == 1 {
			*dir = v2{-1, 0}
		} else if dir.x == -1 {
			*dir = v2{0, -1}
		}
		return true
	}

	if *v == '.' {
		Count += 1
	}

	if update_location {
		if dir.y == -1 {
			*v = '^'
		} else if dir.x == 1 {
			*v = '>'
		} else if dir.y == 1 {
			*v = 'V'
		} else if dir.x == -1 {
			*v = '<'
		}
		gmap[pos.y][pos.x] = 'X'
	}
	if update_went && !slices.Contains(WentPositions, new_pos){
		WentPositions = append(WentPositions, new_pos)
	}
	*pos = new_pos

	return true
}

func findGuard(input [][]byte) v2 {
	for y := range input {
		for x, v := range input[y] {
			if v == '^' {
				return v2{x, y}
			}
		}
	}
	panic("findGuard: couldn't")
}
