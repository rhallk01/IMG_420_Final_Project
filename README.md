# The Lunar Kingdom
**Final Project - 2D Platformer** <br>
**By: Haley Kloss, Hunter Beach, and Mark Johnson**<br>

---

## Module Functionality

**DynamicBounceBody2D**: a custom node that extends RigidBody2D, creating an object that bounces
dynamically when it collides with the ‘ground.’ This node has custom properties that are visible in the editor, including size, energy, energy loss, base strength, and fade on stop.<br>
![star_dissipating_gif](https://github.com/user-attachments/assets/f03e81f2-ac64-4e10-b7df-1c31df13f7dc)
<br><br>

**Surface Material**: A new resource that stores and applies surface material properties for hardness to allow for custom bounce behavior on it. This resource is built in as a property of DynamicBounceBody2D.<br>
<img width="407" height="336" alt="image" src="https://github.com/user-attachments/assets/045fccbc-2fdc-4815-95bd-9f919636366c" />
<br><br>

**Impact Events**: A class that emits custom signals when a collision occurs or when the object
dissipates after losing all of its bounce energy. It will trigger particles and sounds. If bool
fade_on_stop is true, the object in question will be removed from the game once the dissipation
particles and sound are completed.<br>
![star_slow_down_gif](https://github.com/user-attachments/assets/91a183fe-ad38-4294-b509-1d4772395617)
<br><br>
**HazardObject**: A custom node that extends a RigidBody2D, this object has gravity applied, is
integrated with bounce and impact events, and sends out a kill signal when the player touches
it.


---

## Features List
1. Controllable player character
<img width="277" height="277" alt="image" src="https://github.com/user-attachments/assets/e65cf0fa-e483-4bdc-b62c-24cbe28705e6" />

2. Enemy that patrols and chases
<img width="428" height="476" alt="image" src="https://github.com/user-attachments/assets/726f897e-1141-4395-8f99-59382698ab97" />

3. Jump boost that can be collected for higher jumps for 5 seconds
<img width="353" height="303" alt="image" src="https://github.com/user-attachments/assets/fc2afd52-f664-42ae-88aa-ad3e709b52f7" />


4. Key that can be collected to open the door and win the game
<img width="362" height="392" alt="image" src="https://github.com/user-attachments/assets/78466f26-06a6-4954-b14e-58aab8a73484" />

5. Background music and death sound
6. HUD with gameplay instruction overlay and key collection status
<img width="425" height="315" alt="image" src="https://github.com/user-attachments/assets/b0c28f06-d0eb-48de-ac5f-07a1561ce02f" />

7. Main menu screen with instructions and start button
<img width="462" height="278" alt="image" src="https://github.com/user-attachments/assets/67de2c52-ee4b-4875-a820-c8460c28d712" />

8. Falling stars that land and bounce, which the player must avoid
<img width="397" height="188" alt="image" src="https://github.com/user-attachments/assets/8fe00e30-d69f-485d-8b1d-66cd24f7d95a" />

9. System of collision effects
<img width="397" height="188" alt="image" src="https://github.com/user-attachments/assets/c0baee48-0fed-4cc6-ab39-4f253b08fae9" />


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
https://drive.google.com/file/d/17LQnlJf-OtlVVu55WnRTzzgBsy06qOJE/view?usp=sharing
