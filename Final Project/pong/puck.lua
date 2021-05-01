Puck = Entity:extend()

-- Puck constructor takes x, y positions and dimensions
function Puck:new(x, y, width, height)
    Puck.super.new(self, love.graphics.getWidth()/2 - 2, love.graphics.getHeight()/2, 15, 15)

    -- Set x and y speeds and starting directions
    self.ySpeed = -500
    if math.random(1, 2) == 1 then
        self.xSpeed = 400
    else
        self.xSpeed = -400
    end

    -- Set a timer before the Puck is launched
    self.timer = 1
end

function Puck:update(dt)
    -- If timer is over start moving the Puck
    if self.timer > 0 then
        self.timer = self.timer - dt
    else
        Puck.super.update(self, dt)
    end
end


-- Handle the Puck bouncing
function Puck:bounce(e)

    -- Get hitbox of left paddle
    local lp1 = self.x
    local rp1 = self.x + self.width
    local tp1 = self.y
    local bp1 = self.y + self.height

    -- Get hitbox of right paddle
    local lp2 = e.x
    local rp2 = e.x + e.width
    local tp2 = e.y
    local bp2 = e.y + e.height

    -- Check hitbox collision
    if bp1 > tp2 and lp1 < rp2 and tp1 < bp2 and rp1 > lp2 then
        -- Reverse Puck magnitude
        self.xSpeed = -self.xSpeed
    end
end

-- Check Puck collisions with goals
function Puck:goalStatus()
    -- Check if Puck is out of the bounds set for goals to register
    if self.x + self.width < 0 then
        return "left"
    elseif self.x > 1280 then
        return "right"
    else
        return false
    end
end
