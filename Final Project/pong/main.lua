-- One main.lua to rule them all, one main.lua to find them
-- One main.lua to bring them all, and in binary, bind them.

-- Get the mode from the keypress function
function love.load(mode)
		-- Use the external library 'classic' by rxi for Lua with Löve
		Object = require "classic"

		-- Gather the various files
		require "game"
		require "entity"
		require "pad"
		require "puck"

		-- Launch a game object
		game = Game(mode)

		-- Pause the game until it is time to run
		pause = true
end

-- Update the game
function love.update(dt)
		-- Once one of the modes are selected, start the game
		if pause == false then
				game:update(dt)
	  end
end

-- Draw the game
function love.draw()
		game:draw()
end


-- Check game mode from keypress
function love.keypressed(k)
		if k == "m" then
				love.load(0)
				pause = false
		end
		if k == "c" then
				love.load(1)
				pause = false
		end

		-- Pause the Game
		if k == "p" then
				pause = not pause
		end
end
