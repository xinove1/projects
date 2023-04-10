#!/usr/bin/env ruby
puts 'Hello, world'

string = 'Hello, Ruby'
puts "Index of 'Ruby' in #{string} is #{string.index('Ruby')}"

i = 0
while i < 10
  puts "xinove #{i}"
  i += 1
end

number = rand(1001)
puts "Try guessing the number from 0 to 1000"

guess = gets().to_i
while guess != number
  if (guess > number)
    puts "Too high"
  else
    puts "Too low"
  end
  guess = gets().to_i
end
