# Pong by Saptarshi Nath
This is my rendition of the original pong equipped with local two player multiplayer and a computer AI opponent. Built using Lua with LÖVE.

## Contents
The game consists of two core files, one library, and four secondary files.



- **main.lua**

Consists of the toplevel management of the game function, including keypress management and mode selection.

- **conf.lua**

Consists of the configuration files required by Lua with LÖVE. Uses the default file provided by the löve2D website, with modifications made to resolution and title.

- **classic.lua***

Library used for the project from rxi/classic. Helps simplify classes in Lua. *Link is posted below in the 'Libraries' section.

- **game.lua**

Handles the overall functions of the game in an attempt to keep main.lua cleaner. Handles loading of all objects, mode variables and updates the game objects as the game progresses. Draws the user interface using the font 'Silkscreen'*.

- **puck.lua**

Puck class, used to handle puck properties. Extends from entity.lua. Sets the speed, and size. Handles collisions with paddles and the goals on either end of the arena.

- **pad.lua**

Handles the paddle object. Sets the control scheme, movement speed, and AI properties. Extends from entity.lua.

- **entity.lua**

Makes a core object with height, width, x/y position, and x/y speed properties. Handles how speed is managed using delta time (dt), and ensures the bounds of the object within the arena. Draws rectangle shape with given values.

## Fonts used
https://www.fontsquirrel.com/fonts/silkscreen

## Tools used
https://love2d.org/
https://github.com/rxi/classic.git
