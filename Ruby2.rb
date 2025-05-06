matches = 0

commands = gets.chomp.to_i

while commands != 1
  if commands % 2 == 0
    matches += commands / 2
    commands = commands / 2
  else
    matches += (commands - 1) / 2 + 1
    commands = (commands - 1) / 2
  end
end

puts "Количество сыгранных матчей: #{matches}"

