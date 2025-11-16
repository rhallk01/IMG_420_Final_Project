//import
using Godot;

public partial class Chest : Area2D
{
	// set up outgoing signals
	[Signal] public delegate void GameWonEventHandler();
	[Signal] public delegate void ShowWonEventHandler();
	[Signal] public delegate void NeedKeyEventHandler();

	// variables
	public bool HasKey = false;
	public AnimationPlayer _ap;

	// set up chest for initial playthrough
	public override void _Ready()
	{
		//make sure chest is in closed state 
		_ap = GetNode<AnimationPlayer>("AnimationPlayerChest");
		_ap.Play("closed");
	}

	// override process
	public override void _Process(double delta)
	{
		// pass
	}

	//handle when player touches the chest
	private async void _OnBodyEntered(Node2D body)
	{
		//if the player has the key
		if (HasKey == true)
		{
			//make the chest glow
			var particles = GetNodeOrNull<CpuParticles2D>("ChestGlow");
			if (particles != null)
			{
				particles.Restart();
				particles.Emitting = true;
			}
			//open the chest
			_ap.Play("open");
			//signal that the game has been won
			EmitSignal(SignalName.ShowWon);
			//hide the chest labels
			GetNode<CanvasItem>("ChestLabel").Hide();
			GetNode<CanvasItem>("ChestLabel/arrow").Hide();
			
			//wait 1.5 seconds
			await ToSignal(GetTree().CreateTimer(1.15), SceneTreeTimer.SignalName.Timeout);
			//emit game won signal
			EmitSignal(SignalName.GameWon);
		}
		else
		{
			//if the player doesnt have the key
			//show need key message by emitting need key
			EmitSignal(SignalName.NeedKey);
		}
	}
}
