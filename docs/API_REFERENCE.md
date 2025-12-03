# API Documentation

#### Falling Hazard Process Overview:

1. Detect a collision between the ground and a DynamicBounceBody2D
2. Override the \_integrate\_forces, calculate dynamic bounce, and apply bounce to the object
3. The signal class triggers impact events such as particles on impact
4. Repeat the process until the energy has dissipated





**DynamicBounceBody2D**: a custom node that extends RigidBody2D, creating an object that bounces
dynamically when it collides with the ‘ground.’ This node has custom properties that are visible in the editor, including size, energy, energy loss, base strength, and fade on stop.


**Surface Material**: A new resource that stores and applies surface material properties for hardness to allow for custom bounce behavior on it. This resource is built in as a property of 


**Impact Events**: A class that emits custom signals when a collision occurs or when the object
dissipates after losing all of its bounce energy. It will trigger particles and sounds. If bool
fade\_on\_stop is true, the object in question will be removed from the game once the dissipation
particles and sound are completed.


**HazardObject**: A custom node that extends a RigidBody2D, this object has gravity applied, is
integrated with bounce and impact events, and sends out a kill signal when the player touches
it.


Properties Accessible in Editor:
---



Float size

Float energy

Float energy\_loss

Float base\_strength
Bool fade\_on\_stop

Property surface\_material: Float hardness

Property impact\_event



