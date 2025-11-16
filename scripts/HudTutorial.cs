//imports
using Godot;
using System;

public partial class HudTutorial : CanvasLayer
{
	// set up initial hud
	public override void _Ready()
	{
		// hide the "YouWin" label at start
		GetNode<Control>("YouWin").Hide();

		// set initial key status message
		var keyStatus = GetNode<Label>("keyStatus");
		keyStatus.Text = "you need\nthe key";
	}

	// override process func
	public override void _Process(double delta)
	{
		// pass
	}
}
