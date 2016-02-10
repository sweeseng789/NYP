function add(...)
local sum = 0

	for idx = 1, arg.n do
	sum = sum + arg[idx]
	end
	
return sum
end