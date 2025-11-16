# The Legend of Autumn
**Assignment 4 - 2D Platformer**
**Converted to C# and Updated**

---

## How to Run the Game
1.  Clone or download the project folder.
2. Open the project in Godot
3. Build and run the project 
4. On the main menu, press the **Start** button to begin the game

---

## Controls:
* Use the arrow keys and space to move
* Left key to go left
* Right key to go right
* Down key to crouch
* Up key to jump
* Space key can also be used to jump

---

## Game Rules
### Win Conditions: 
* Collect the **key**
* Open the **chest** while holding the key to win
  
### Lose Conditions:
* Touching the **enemy** will kill you, causing a Game Over
* Falling off the map will kill you, causing Game Over


### Interactables
* **Pumpkin (Jump Boost):** Grants a temporary jump power-up
* **Key:** Required to open the chest
* **Chest:** Opens only when the key is collected, triggers Gane Won
* **Enemy:** Patrols or follows the player when in range and causes a Game Over on contact

---

## Assets Used
**Sound**
* Background Music: `autumn-waltz-174280.mp3`
* Death Sound: `piano-g-6200.mp3`
  
**Fonts**

* `EagleLake-Regular.ttf`

**Tile Set**

* `oak_woods_tileset`

**Particles**

* `white-spark-bright-clipart`
  
**Textures**
* Arrow for Labels: `arrow.png`
* Main Menu Background: `background_layer_1`
* Background for Level: `background_layer_1, background_layer_2, background_layer_3`
* Chest Image Closed: `closed_chest`
* Chest Image Open: `open_chest`
* Key: `key-white`
* Pumpkin: `pumpkin`
* Sunflower: `sunflower`

**Sprites**
* Player Crouch Idle: `Crouching_Idle_KG_1`
* Player Crouch Walk: `Crouching_Walk_KG_1`
* Player Fall: `Fall_KG_1`
* Player Idle: `Idle_KG_1`
* Player Jump: `Jump_KG_1`
* Player Walk: `Walking_KG_1`
* Enemy Idle: `Spr_Idle`
* Enemy Walk: `Spr_Walk`

# Project Requirements

## Tile-Based World
The platforms in this world are tile-based, with the tiles having physics and navigation layers, using the oak_woods_tileset. <br>
<img width="680" height="408" alt="image" src="https://github.com/user-attachments/assets/4c51c94f-11db-4b22-9ec2-85fb276d5aa6" />

## Player Character
The player character has a CharacterBody2d as its root node, with a Sprite2d and a CollisionShape2D with assets for both standing and crouching.<br>
<img width="740" height="239" alt="image" src="https://github.com/user-attachments/assets/16a34e8e-0dab-44e6-b462-55eb6d550bb8" />

The movement of the player character, defined in the _PhysicsProcess() function of Player.cs, using a velocity vector and by calling move_and_slide().<br>
<img width="710" height="282" alt="image" src="https://github.com/user-attachments/assets/53394824-9d2e-404c-8670-217a22705c96" />

Gravity is applied each frame and jumping is only enabled when is_on_floor() is true.<br>
<img width="697" height="573" alt="image" src="https://github.com/user-attachments/assets/817742ea-0899-461f-9e3c-63be56add10b" />
 
## Sprite Animation
The player has animations for crouch_idle,crouch_walk, fall, idle, jump, and walk movements, which are handled by a Sprite2D node combined with the AnimationPlayer node.<br>
<img width="671" height="431" alt="image" src="https://github.com/user-attachments/assets/7b37a113-e49e-49c2-a4da-7851c4552e0a" />
 
These animations are handled in the code in the UpdateAnimations() function, called from _PhysicsProcess(), so that during the appropriate movements the correct animations are played.<br>
<img width="592" height="569" alt="image" src="https://github.com/user-attachments/assets/2515bd30-5287-484e-b09e-4544f76f520c" />

The enemy also has animations for walk and idle, with a Sprite2D node and an AnimationPlayer node. Playing these animations is handled in the code in the _PhysicsProcess() function.<br>
<img width="975" height="721" alt="image" src="https://github.com/user-attachments/assets/7e7461e6-9af6-46d2-a0b4-7651483fbf63" />

## Enemies with Pathfinding
The enemy moves using 2D navigation and pathfinding. When the player is out of range, it patrols back and forth on the platform. When the player is in range, the enemy chases the player.
The tileset for the world has a navigation layer painted onto the blocks used for the platforms.<br>
<img width="876" height="162" alt="image" src="https://github.com/user-attachments/assets/2fc6fc1e-080a-452a-83aa-92b8b78766a0" />
<img width="451" height="458" alt="image" src="https://github.com/user-attachments/assets/a8af5b09-fd37-4917-8046-ef45943dcf18" />
<img width="269" height="225" alt="image" src="https://github.com/user-attachments/assets/618f70bd-866f-46e1-8f18-f49c22909a63" />


## Particle Effects
The enemy has a particle system that is triggered when the player touches the enemy and dies. It is made to look like an explosion. This is made with a GPUParticles2D system that has a ParticlesMaterial.<br>
<img width="156" height="551" alt="image" src="https://github.com/user-attachments/assets/6fc3b7d1-ba17-44c8-98e3-cb691b8f7eb5" /><img width="690" height="550" alt="image" src="https://github.com/user-attachments/assets/a280537b-e911-436f-b7d0-d11cb0582fec" />

The key also has a particle system for a celebratory explosion when the player gets they key. The particle system is handled in the Main scene and script.<br>
<img width="410" height="334" alt="image" src="https://github.com/user-attachments/assets/d672f692-f0a7-4d30-8c3a-a940c8c7412c" />
<img width="863" height="385" alt="image" src="https://github.com/user-attachments/assets/d8ff8571-9e42-4c51-8d56-b9a428a6488d" />

## Interactions and Simple Physics/Gravity and Jumping
The game is a platform, so the player can stand on platforms, has to duck under platforms that they can't walk through, and falls when they are not on a platform.<br>

## Collisions: 
The player has a CollisionShape2D that facilitates their interactions with the physics of the tileset so that they can stand on and run into platform elements.<br>

## Collectibles:
The game includes a key that the player must collect in order to open a chest at the end to win the game. Collecting the key changes the game state by setting the bool HasKey bool in main.cs to true, and enabling the chest to be opened.<br>
<img width="793" height="375" alt="image" src="https://github.com/user-attachments/assets/dc59292b-152c-473d-864a-b5bd18759aaf" />
<img width="683" height="550" alt="image" src="https://github.com/user-attachments/assets/309f7b37-41ad-4cb0-b183-7d60c38f6d33" />

## UI and feedback
There is a HUD that shows movement instructions when on the first platform, boost notifications, a message in the top right denoting whether or not you have the key, and a "You win!" message if you win or "You need the key" if you reach the chest without the key.<br>
<img width="975" height="548" alt="image" src="https://github.com/user-attachments/assets/41a194ca-a333-40c3-89b3-c705dd33121b" />

## Polish and Creativity
The game includes background music, a death sound effect, and a jump boost powerup.

