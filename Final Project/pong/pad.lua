Pad = Entity:extend()

-- Pad from Entity object
function Pad:new(x, y, width, height)
    Pad.super.new(self, 50, 350, 10, 70)

    -- Default key layout for paddle 1
    self.keyUp = "up"
    self.keyDown = "down"
end


-- Paddle logic. Use delta time, ai mode and the Puck object y position
function Pad:update(dt, ai, Puck_Y)

    -- If mode is 2 player
    if ai == 0 then
        -- Set controls and manage speed
        if love.keyboard.isDown(self.keyUp) then
            self.ySpeed = -400
        elseif love.keyboard.isDown(self.keyDown) then
            self.ySpeed = 400
        else
            self.ySpeed = 0
        end

    -- If mode is ai
    elseif ai == 1 then
        -- Manage the direction of movement relative to Puck y position
        local pady = self.y
        if Puck_Y < self.y + 50 then
            self.y = self.y - Puck_Y * dt
            if self.y < 0 then
                self.y = pady
            end
        end

        if Puck_Y > self.y + 50  then
            self.y = self.y + Puck_Y * dt
            if self.y > 1280 then
                self.y = pady
            end
        end
    end

    -- Update the paddle position
    Pad.super.update(self, dt)
end
