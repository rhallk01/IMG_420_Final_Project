using Godot;
using System;
using System.Threading.Tasks;

public partial class MainMenu : CanvasLayer
{
	//set up signal for start game
	[Signal] public delegate void StartGameEventHandler();

	//initial settings for text
	public override void _Ready()
	{
		// Hide Win/Lose text at start
		GetNode<Label>("WinOrLose").Hide();
	}

	//show the messages for the title and instructions
	public void ShowMessage(string text)
	{
		//get message nodes
		var message = GetNode<Label>("Message");
		var message2 = GetNode<Label>("Message2");
		//show the messages
		message.Text = text;
		message.Show();
		message2.Text = text;
		message2.Show();
	}

	//show game over screen
	public async void show_game_over()
	{
		//get nodes for all of the necessary messages
		var winOrLose = GetNode<Label>("WinOrLose");
		var bg = GetNode<Control>("WinOrLosebg");
		var mainMenuBg = GetNode<Control>("MainMenubg");
		var message = GetNode<Label>("Message");
		var message2 = GetNode<Label>("Message2");
		var startButton = GetNode<Button>("StartButton");
	
		//Set text for game over screen
		winOrLose.Text = "GAME OVER";
		Show();
		bg.Show();
		winOrLose.Show();

		// Wait 0.6 seconds to go to main menu screen
		await ToSignal(GetTree().CreateTimer(0.6f), SceneTreeTimer.SignalName.Timeout);

		//hide game over screen
		winOrLose.Hide();
		bg.Hide();
		mainMenuBg.Show();

		//show main menu
		message.Text = "The Lunar Kingdom";
		message.Show();
		message2.Text = "get the key and\nopen the door alive to win!";
		message2.Show();
		startButton.Show();
	}
	
	//show game won screen
	public async void show_game_won()
	{
		//get nodes for all of the necessary messages
		var winOrLose = GetNode<Label>("WinOrLose");
		var bg = GetNode<Control>("WinOrLosebg");
		var mainMenuBg = GetNode<Control>("MainMenubg");
		var message = GetNode<Label>("Message");
		var message2 = GetNode<Label>("Message2");
		var startButton = GetNode<Button>("StartButton");

		//Set text for game won screen
		winOrLose.Text = "YOU WON!!";

		// hide cause of death message if it exists
		if (HasNode("WinOrLose/howDie"))
		{
			var howDie = GetNode<CanvasItem>("WinOrLose/howDie");
			howDie.Hide();
		}

		//show game won screen
		Show();
		bg.Show();
		winOrLose.Show();

		// wait 1 second
		await ToSignal(GetTree().CreateTimer(1.0f), SceneTreeTimer.SignalName.Timeout);

		//hide game won screen
		winOrLose.Hide();
		bg.Hide();
		mainMenuBg.Show();

		//show main menu elements
		message.Text = "The Lunar Kingdom";
		message2.Text = "get the key and\nopen the door alive to win!";
		message.Show();
		message2.Show();
		startButton.Show();
	}

	//handles start button being pressed
	private void _OnStartButtonPressed()
	{
		//get necessary nodes
		var mainMenuBg = GetNode<Control>("MainMenubg");
		var startButton = GetNode<Button>("StartButton");
		var message = GetNode<Label>("Message");
		var message2 = GetNode<Label>("Message2");

		//hide main menu screen elements
		mainMenuBg.Hide();
		startButton.Hide();
		message.Hide();
		message2.Hide();
		
		//send out signal to start the game
		EmitSignal(SignalName.StartGame);
	}
}
