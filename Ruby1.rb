s = gets.chomp

count = 0
gl = "AaEeIiOoUuYy"

s.each_char do |char|
  if char != " "
    if gl.include?(char)
      count += 1
    else
      count -= 1
    end
  end
end

if count == 0
  puts "Одинаково"
elsif count < 0
  puts "Нет"
else
  puts "Да"
end

