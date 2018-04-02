local vec3_mt = {}
vec3_mt.__index = vec3_mt

local function new(x, y, z)
	return setmetatable({x = x or 0, y = y or 0, z = z or 0}, vec3_mt)
end

function vec3_mt:__add(v)
	return new(
		self.x + v.x,
		self.y + v.y,
		self.z + v.z
	)
end

function vec3_mt:__sub(v)
	return new(
		self.x - v.x,
		self.y - v.y,
		self.z - v.z
	)
end

function vec3_mt:__mul(v)
	if type(v) == "number" then
		return new(
			self.x * v,
			self.y * v,
			self.z * v
		)
	else
		return new(
			self.x * v.x,
			self.y * v.y,
			self.z * v.z
		)
	end
end

function vec3_mt:__div(v)
	if type(v) == "number" then
		return new(
			self.x / v,
			self.y / v,
			self.z / v
		)
	else
		return new(
			self.x / v.x,
			self.y / v.y,
			self.z / v.z
		)
	end
end

function vec3_mt:__eq(v)
	return self.x == v.x and self.y == v.y and self.z == v.z
end

function vec3_mt:__unm()
	return new(-self.x, -self.y, -self.z)
end

function vec3_mt:__tostring()
	return "[" .. self.x .. "," .. self.y .. "," .. self.z .. "]"
end

function vec3_mt:add(v)
	self = self + v
end

function vec3_mt:sub(v)
	self = self - v
end

function vec3_mt:mul(n)
	self.x = self.x * n
	self.y = self.y * n
	self.z = self.z * n
end

function vec3_mt:zero()
	self.x = 0
	self.y = 0
	self.z = 0
	return self
end

function vec3_mt:length()
	return ((self.x * self.x) + (self.y * self.y) + (self.z * self.z)) ^ 0.5
end

function vec3_mt:normal()
	local length = self:length()
	return new(self.x / length, self.y / length, self.z / length)
end

function vec3_mt:dot(v)
	return (self.x * v.x) + (self.y * v.y) + (self.z * v.z)
end

function vec3_mt:cross(v)
	local vec = new(0,0,0)
	vec.x = (self.y * v.z) - (v.y * self.z)
	vec.y = (self.z * v.x) - (v.z * self.x)
	vec.z = (self.x * v.y) - (v.x * self.y)
	return vec
end

function vec3_mt:distance(v)
	local vec = self - v
	return vec:length()
end

function vec3_mt:lerp(to, ratio)
	local vec = (self * (1 - ratio)) + (to * ratio)
	return vec
end

return new
