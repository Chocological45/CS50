Game = Object:extend()

-- Core game management
function Game:new(mode)
		-- Load the paddles, Puck, and scoreboard data. Get the ai mode
		self.padLeft = Pad()
		self.padLeft.keyUp = "w"
		self.padLeft.keyDown = "s"

		self.padRight = Pad()
		self.padRight.x = 1220

		self.Puck = Puck()

		self.scoreLeft = 0
		self.scoreRight = 0

		ai = mode
end


function Game:update(dt)
		-- Get player 1 paddle running
		self.padLeft:update(dt, 0, self.Puck.y)

		-- Get player 2 paddle running based on ai mode setting
	  if ai == 0 then
				self.padRight:update(dt, 0, self.Puck.y)
		elseif ai == 1 then
				self.padRight:update(dt, 1, self.Puck.y)
		end

		-- Get Puck running and map paddles to the bounce function
		self.Puck:update(dt)
		
		self.Puck:bounce(self.padRight)
		self.Puck:bounce(self.padLeft)

		-- Get the status of the Puck
		local Puck_status = self.Puck:goalStatus()

		-- Update player scores when goal is made
		if Puck_status == "left" then
				self.scoreRight = self.scoreRight + 1
				self.Puck = Puck()
		elseif Puck_status == "right" then
				self.scoreLeft = self.scoreLeft + 1
				self.Puck = Puck()
		end
end


-- Draw the interface
function Game:draw()
		-- Draw the line down the middle
		-- Set color to dark gray
		love.graphics.setColor(105/255, 105/255, 105/255)
		for i = 0, 35 do
				love.graphics.rectangle("fill", love.graphics.getWidth()/2, 25 * i, 10, 10)
		end

		-- Set color back to white
		love.graphics.setColor(1, 1, 1)

		-- Draw the paddles and Puck
		self.padLeft:draw()
		self.padRight:draw()
		self.Puck:draw()


		-- Import a font for the scoreboard and filter for clarity
		local font = love.graphics.newFont("slkscr.ttf", 50)
		font:setFilter( "nearest", "nearest" )

		-- Handle the score display
		if self.scoreLeft == 1 then
				love.graphics.print(self.scoreLeft .."-".. self.scoreRight, font, love.graphics.getWidth()/3 + 35, 20, 0, 4, 4)
		else
				love.graphics.print(self.scoreLeft .."-".. self.scoreRight, font, love.graphics.getWidth()/3 + 11, 20, 0, 4, 4)
		end

		-- Draw the instructional menu
		love.graphics.print("Press 'm' to set mode to Multiplayer", 530, 680)
		love.graphics.print("Press 'c' to set mode to Computer AI", 530, 700)
		love.graphics.print("Press 'p' to pause the game", 530, 720)
end
