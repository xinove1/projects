#!/usr/bin/env python3
def task_1(file):
    # Iterate over commands, add 1 to cycle count no matter what is the input; If the command is "addx", then add
    # 1 more to the count and update signal strength if it's one of the above-mentioned cycles; At the end of this if,
    # add the number from the command to x register
    signal_strength = 0
    x_register = 1
    cycle_count = 0
    cycle_check = 20
    for command in file.readlines():
        cycle_count += 1
        if command.startswith("addx"):
            cycle_count += 1
            if cycle_count >= cycle_check:
                signal_strength += x_register * cycle_check
                cycle_check += 40
                print("Cycle: " + str(cycle_count) + " x: " + str(x_register) + " signal strength: " + str(x_register * cycle_count))
            x_register += int(command.split()[1])
    print("Task 1 result: " + str(signal_strength))

print("Advent of Code - Day 10")
file_task_1 = open('input_demo', 'r')
task_1(file_task_1)
print("aaa");
