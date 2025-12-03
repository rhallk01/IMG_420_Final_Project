# The Lunar Kingdom
**Final Project - 2D Platformer** <br>
**By: Haley Kloss, Hunter Beach, and Mark Johnson**<br>

---

## Module Functionality

**DynamicBounceBody2D**: a custom node that extends RigidBody2D, creating an object that bounces
dynamically when it collides with the ‘ground.’ This node has custom properties that are visible in the editor, including size, energy, energy loss, base strength, and fade on stop.
<br><br>
**Surface Material**: A new resource that stores and applies surface material properties for hardness to allow for custom bounce behavior on it. This resource is built in as a property of 
<br><br>
**Impact Events**: A class that emits custom signals when a collision occurs or when the object
dissipates after losing all of its bounce energy. It will trigger particles and sounds. If bool
fade_on_stop is true, the object in question will be removed from the game once the dissipation
particles and sound are completed.
<br><br>
**HazardObject**: A custom node that extends a RigidBody2D, this object has gravity applied, is
integrated with bounce and impact events, and sends out a kill signal when the player touches
it.


---

## Features List
1. Controllable player character
2. Enemy that patrols and chases
3. Jump boost that can be collected for higher jumps for 30 seconds
4. Key that can be collected to open the door and win the game
5. Background music and death sound
6. HUD with gameplay instruction overlay and key collection status
7. Main menu screen with instructions and start button
8. Falling stars that land and bounce, which the player must avoid
9. System of collision effects

---

## Installation and Build Instructions
1. Clone the repository
2. Open Godot
3. Import project with the cloned folder

---

## How to Run the Game

1.  Clone or download the project folder.
2. Open the project in Godot
3. Build and run the project 
4. On the main menu, press the **Start** button to begin the game
   
---

## Controls and Gameplay Instructions

#### Player
* Run Right - Right arrow key or 'D'
* Run Left - Left arrow key or 'A'
* Jump - Space, 'W', or the up arrow key
* Pick up item - touch item to pick it up

#### Win Conditions: 
* Collect the **key**
* Open the **door** while holding the key to win
  
### Lose Conditions:
* Touching the **enemy** will kill you, causing a Game Over
* Falling off the map will kill you, causing Game Over

### Interactables
* **Moon (Jump Boost):** Grants a temporary jump power-up
* **Key:** Required to open the chest
* **Door:** Opens only when the key is collected, triggers Gane Won
* **Enemy:** Patrols or follows the player when in range and causes a Game Over on contact

---

## Known Issues and Future Improvements
1. Currently, the surface texture resource has only been added to the DynamicBounceObject2D, and having it implemented in a rigid body to assign ground texture would be optimal.

---
## Credits and Acknowledgements
**Player Character**: https://lucky-loops.itch.io/character-satyr<br>
**Background/Platform Texture**: https://trixelized.itch.io/starstring-fields<br>
**Sky**: https://free-game-assets.itch.io/free-sky-with-clouds-background-pixel-art-set<br>
**Enemy**: https://zneeke.itch.io/goblin-scout-silhouette<br>
**Moon (Jump Boost)**: https://squaremeapixel.itch.io/moon<br>
**Key**: https://dantepixels.itch.io/key-items-16x16<br>

---

## Link to Demo Video
