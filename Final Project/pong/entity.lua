Entity = Object:extend()

-- Basic Entity object with positional and movement properties
function Entity:new(x, y, width, height)
		self.x = x
		self.y = y
		self.width = width
		self.height = height
		self.xSpeed = 0
		self.ySpeed = 0
end

function Entity:update(dt)
		-- Update the entities position with speed, bound by delta time
		-- dt ensures that speed is not relative to the system fps
		self.x = self.x + self.xSpeed * dt
		self.y = self.y + self.ySpeed * dt

		-- Set the bounds of the entity to within the arena
		if self.y <= 0 then
				self.y = 0
				self.ySpeed = -self.ySpeed
		elseif self.y + self.height >= 800 then
				self.y = 800 - self.height
				self.ySpeed = -self.ySpeed
		end
end

function Entity:draw()
		-- Draw the 'paddles' and 'ball'
		love.graphics.rectangle("fill", self.x, self.y, self.width, self.height)
end
