using Godot;
using System;

public partial class Enemy : CharacterBody2D
{
	//set up died by enemy signal 
	[Signal] public delegate void DiedByEnemyEventHandler();
	
	//declare private variables
	private NavigationAgent2D _agent;
	private Sprite2D _sprite;
	private AnimationPlayer _anim;
	private Node2D _player;
	private bool _goingRight = true;
	
	//declare and initialize export variables
	[Export] public float Speed = 15f;
	[Export] public float Gravity = 800f;
	[Export] public float ChaseRange = 200f;
	[Export] public Vector2 Target1 = new Vector2(785, 81);
	[Export] public Vector2 Target2 = new Vector2(720, 81);

	//on initial run through setup
	public override void _Ready()
	{
		//set up variables pointing to nodes
		_agent = GetNode<NavigationAgent2D>("NavigationAgent2D");
		_sprite = GetNodeOrNull<Sprite2D>("Sprite2D");
		_anim = GetNodeOrNull<AnimationPlayer>("AnimationPlayerEnemy");
		_player = GetTree().Root.GetNode<Node2D>("Main/Player");

		//path finding settings
		_agent.PathDesiredDistance = 4f;
		_agent.TargetDesiredDistance = 4f;
		_agent.VelocityComputed += OnVelocityComputed;
		Callable.From(DeferredSetup).CallDeferred();
	}

	//setup for navigation
	private async void DeferredSetup()
	{
		//wait until everything has loaded to start navigation
		//init navigation map
		await ToSignal(GetTree(), SceneTree.SignalName.PhysicsFrame);
		_agent.SetNavigationMap(GetWorld2D().NavigationMap);
		_agent.TargetPosition = Target1;
	}

	
	public override void _PhysicsProcess(double delta)
	{
		// apply gravity
		if (!IsOnFloor())
			Velocity = new Vector2(Velocity.X, Velocity.Y + Gravity * (float)delta);

		// chase player if within range
		if (_player != null && GlobalPosition.DistanceTo(_player.GlobalPosition) < ChaseRange)
		{
			// only update target every few frames or if far enough
			if (_agent.TargetPosition.DistanceTo(_player.GlobalPosition) > 8f)
				_agent.TargetPosition = _player.GlobalPosition;
		}
		else if (_agent.IsNavigationFinished())
		{
			_goingRight = !_goingRight;
			_agent.TargetPosition = _goingRight ? Target1 : Target2;
		}

		// move along path
		Vector2 nextPos = _agent.GetNextPathPosition();
		Vector2 dir = (nextPos - GlobalPosition).Normalized();

		Velocity = new Vector2(dir.X * Speed, Velocity.Y);
		MoveAndSlide();

		// flip sprite so it faces the direction its walking
		if (_sprite != null && MathF.Abs(Velocity.X) > 5f)
		{
			bool newFlip = Velocity.X < 0;
			if (_sprite.FlipH != newFlip)
				_sprite.FlipH = newFlip;
		}

		// set animation
		if (_anim != null)
		{
			if (MathF.Abs(Velocity.X) > 5f)
				_anim.Play("walk");
			else
				_anim.Play("idle");
		}
	}

	//set velocity to safe velocity
	private void OnVelocityComputed(Vector2 safeVelocity)
	{
		Velocity = safeVelocity;
	}

	//handling for when player touches enemy
	public async void _OnBodyEntered(Node2D body)
	{
		// play particle effect
		var particles = GetNodeOrNull<GpuParticles2D>("DeathParticles");
		if (particles != null)
		{
			//reset particles
			particles.Restart();
			// let the particles emit for .02 seconds
			particles.Emitting = true;
			await ToSignal(GetTree().CreateTimer(0.02f), SceneTreeTimer.SignalName.Timeout);
			particles.Emitting = false;
			// wait for the particles to finish
			await ToSignal(GetTree().CreateTimer(0.2f), SceneTreeTimer.SignalName.Timeout);
		}
		//emit died by enemy signal
		GD.Print("Enemy collided with player!");
		EmitSignal(SignalName.DiedByEnemy);
	}
}
