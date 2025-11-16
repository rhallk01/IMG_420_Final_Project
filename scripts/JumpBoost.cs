//imports
using Godot;
using System;

public partial class JumpBoost : Area2D
{
	//set up boost signal to emit
	[Signal] public delegate void BoostEventHandler();
	
	//set up jump boost for initial run through
	public override void _Ready()
	{
		// enable monitoring for the node
		SetDeferred("monitoring", true);
	}

	//override process func
	public override void _Process(double delta)
	{
		// pass
	}

	//handle when player gets jump boost
	private void _OnBodyEntered(Node2D body)
	{
		// emit boost signal
		EmitSignal(SignalName.Boost);
	}
}
