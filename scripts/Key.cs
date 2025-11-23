//imports
using Godot;
using System;

public partial class Key : Area2D
{
	//set up signal for got key
	[Signal] public delegate void GotKeyEventHandler();
		
	//initial settings
	public override void _Ready()
	{
		// Show the key when the scene starts
		SetDeferred("monitoring", true);
		Show();
	}

	//override process
	public override void _Process(double delta)
	{
		// pass
	}

	//handle when player gets key
	private void _OnBodyEntered(Node2D body)
	{	
		// hide the key and emit got_key signal
		Hide();
		EmitSignal(SignalName.GotKey);
	}
}
