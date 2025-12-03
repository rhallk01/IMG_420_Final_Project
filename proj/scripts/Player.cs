//imports
using Godot;
using System;

public partial class Player : CharacterBody2D
{
	//variables to show up in editor
	[Export] public float Speed { get; set; } = 200.0f;
	[Export] public float JumpForce { get; set; } = -275.0f;
	[Export] public float Gravity { get; set; } = 20.0f;

	// --- NEW/UPDATED SIGNALS ---
	[Signal] public delegate void FellToDeathEventHandler(); // Renamed from GameOver
	[Signal] public delegate void HitByHazardEventHandler(); // NEW signal for C++ hazard

	//declare variables for necessary nodes
	private AnimationPlayer _ap;
	private Sprite2D _sprite;
	private CollisionShape2D _cShape;
	private RayCast2D _cRaycast1;
	private RayCast2D _cRaycast2;

	//declare and initialize variables for movement 
	private bool _hittingHeadState = false;
	public bool CanMove = true;

	//load collision shape
	private Shape2D _tallCShape = GD.Load<Shape2D>("res://resources/collision_shape_tall.tres");

	// --- NEW: Method to trigger player death from C++ ---
	public void Die()
	{
		// This method is called directly by the HazardObject C++ script
		EmitSignal(SignalName.HitByHazard); 
	}
	
	// --- NEW: REQUIRED FOR C++ COLLISION CHECK ---
	public bool IsPlayer()
	{
		return true;
	}

	//initial settings, set nodes and freeze the player (as they will be on main menu screen)
	public override void _Ready()
	{
		_ap = GetNode<AnimationPlayer>("AnimationPlayer");
		_sprite = GetNode<Sprite2D>("Sprite2D");
		_cShape = GetNode<CollisionShape2D>("CollisionShape2D");
		_cRaycast1 = GetNode<RayCast2D>("raycast_1");
		_cRaycast2 = GetNode<RayCast2D>("raycast_2");
		CanMove = false;
	}

	//player movement 
	public override void _PhysicsProcess(double delta)
	{
		//check if the player can move or not
		//if they can, set velocity 0 and move and slide
		if (!CanMove)
		{
			Velocity = Vector2.Zero;
			MoveAndSlide();
			return;
		}

		// if the player isn't on the ground, make them fall (gravity)
		if (!IsOnFloor())
		{
			//make the player fall
			Velocity = new Vector2(Velocity.X, Velocity.Y + Gravity);
			//if player goes too low, trigger game over signal
			if (Velocity.Y > 1000)
			{
				Velocity = new Vector2(Velocity.X, 1000);
				EmitSignal(SignalName.FellToDeath); // <-- UPDATED: Now emits FellToDeath
			}
		}

		// if jump button is pressed and the player is touching the floor, jump
		if (Input.IsActionJustPressed("jump") && IsOnFloor())
			Velocity = new Vector2(Velocity.X, JumpForce);

		// movement input
		float horizontalDirection = Input.GetAxis("move_left", "move_right");
		//switch direction if needed
		//adjust velocity
		if (horizontalDirection != 0)
		{
			SwitchDirection(horizontalDirection);
			Velocity = new Vector2(horizontalDirection * Speed, Velocity.Y);
		}
		else
		{
			Velocity = new Vector2(0, Velocity.Y);
		}
		
		MoveAndSlide();
		UpdateAnimations(horizontalDirection);
	}

	//update animations for idle, jump, fall, and run
	private void UpdateAnimations(float horizontalDirection)
	{
		//if on floor, play idle/run
		if (IsOnFloor())
		{
			//if not moving, idle 
			if (horizontalDirection == 0)
			{
				//play idle animation
				_ap.Play("idle");
			}
			//if moving, move animation
			else
			{
				//run movement animation
				_ap.Play("run");
			}
		}
		else
		//if not on floor
		{
			//play jump if going up, otherwise play fall
			_ap.Play(Velocity.Y > 0 ? "fall" : "jump");
		}
	}

	//handle switching direction
	private void SwitchDirection(float horizontalDirection)
	{
		//adjust the direction that the sprite is facing and their position accordingly
		_sprite.FlipH = (horizontalDirection == -1);
		_sprite.Position = new Vector2(horizontalDirection * -2, _sprite.Position.Y);
	}

}
