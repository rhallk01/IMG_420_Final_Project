//imports
using Godot;
using System;
using System.Threading.Tasks;

public partial class Main : Node2D
{
	// declare private variables
	private Player _player;
	private MainMenu _mainMenu;
	private Label _keyStatus;
	private Label _youWin;
	private Label _getTheKey;
	private Label _boostMessage;
	private AudioStreamPlayer2D _deathSound;
	private Door _door;
	private Area2D _jumpBoost;
	private Key _key;
	private HudTutorial _hudTutorial;

	//override Ready for the main scene
	public override void _Ready()
	{
		//initialize variables refering to other nodes
		GD.Print("Test");
		_player = GetNode<Player>("Player");
		_mainMenu = GetNode<MainMenu>("MainMenu");
		_keyStatus = GetNode<Label>("HUD_tutorial/keyStatus");
		_youWin = GetNode<Label>("HUD_tutorial/YouWin");
		_getTheKey = GetNode<Label>("HUD_tutorial/GetTheKey");
		_boostMessage = GetNode<Label>("HUD_tutorial/BoostMessage");
		_deathSound = GetNode<AudioStreamPlayer2D>("DeathSound");
		_door = GetNode<Door>("Door");
		_jumpBoost = GetNode<Area2D>("JumpBoost");
		_key = GetNode<Key>("Key");
		_hudTutorial = GetNode<HudTutorial>("HUD_tutorial");

		//connect signals 
		_mainMenu.Connect(MainMenu.SignalName.StartGame, new Callable(this, nameof(_on_main_menu_start_game)));
		_player.Connect(Player.SignalName.GameOver, new Callable(this, nameof(_on_player_game_over)));
		_jumpBoost.Connect("Boost", new Callable(this, nameof(_on_jump_boost_boost)));
		_key.Connect("GotKey", new Callable(this, nameof(_on_key_got_key)));
		_door.Connect("GameWon", new Callable(this, nameof(_on_door_game_won)));
		_door.Connect("NeedKey", new Callable(this, nameof(_on_door_need_key)));
		_door.Connect("ShowWon", new Callable(this, nameof(_on_door_show_won)));

		// hide/show initial UI (with start button)
		_hudTutorial.GetNode<Label>("YouWin").Hide();
		_boostMessage.Hide();
		_mainMenu.Show();
	}
	
	//override process function, which runs every frame
	public override void _Process(double delta)
	{ 
		//get player position and init movement instruction label
		var playerX = _player.Position.X;
		var moveLabel = GetNode<Label>("HUD_tutorial/MoveKeyLabel");

		//have the hud label for initial movement instructions
		//show on screen only on the first platform
		if (playerX > -20 && playerX < 90)
			moveLabel.Show();
		else
			moveLabel.Hide();
	}

	// set up for new game
	public void new_game()
	{
		 //make sure text is right, has key is false
		//hide or show menus and messages
		_keyStatus.Text = "you need\nthe key";
		_door.HasKey = false;
		_youWin.Hide();
		_mainMenu.Hide();
		_boostMessage.Hide();
		_jumpBoost.Show();
		_key.Show();

		//set player speed, jump, and can move
		_player.Speed = 200.0f;
		_player.JumpForce = -275.0f;
		_player.CanMove = true;
	}

	//handle game over
	public void game_over()
	{
		//freeze player, put them in the right spot
		//play death spot, show game over menu
		_player.SetPhysicsProcess(false);
		_player.GlobalPosition = new Vector2(80, 150);
		_player.Velocity = Vector2.Zero;
		_player.SetPhysicsProcess(true);
		_player.CanMove = false;
		_deathSound.Play();
		_mainMenu.show_game_over();
	}

	//handle player falling to their deat
	public void _on_player_game_over()
	{
		//load appropriate death message, go to game over handling
		var howDie = GetNode<Label>("MainMenu/WinOrLose/howDie");
		howDie.Text = "you fell to your death";
		game_over();
	}

	//handle player getting the jump boost
	public async void _on_jump_boost_boost()
	{
		//hide the boost pumpkin
		//set the new jump force, show boost message
		_jumpBoost.Hide();
		_player.JumpForce = -350.0f;
		_boostMessage.Text = "5 sec jump boost!";
		_boostMessage.Show();

		//wait for 5 sec to give player 5 secs of boost
		await ToSignal(GetTree().CreateTimer(5.0f), SceneTreeTimer.SignalName.Timeout);

		//return jump force to normal, show boost over message for 1 sec
		//after 1 sec, hide boost over message
		_player.JumpForce = -275.0f;
		_boostMessage.Text = "jump boost over";
		await ToSignal(GetTree().CreateTimer(1.0f), SceneTreeTimer.SignalName.Timeout);
		_boostMessage.Hide();
	}

	//handle death by enemy
	public void _on_enemy_died_by_enemy()
	{
		//load appropriate death message, go to game over handling
		var howDie = GetNode<Label>("MainMenu/WinOrLose/howDie");
		howDie.Text = "you were killed by the enemy";
		game_over();
	}

	//handle player getting the key
	public void _on_key_got_key()
	{
		 //if they dont have the key yet, show celebratory particles
		if(_keyStatus.Text != "you have\nthe key"){
			var particles = GetNodeOrNull<GpuParticles2D>("KeySparkles");
			if (particles != null)
			{
				particles.GlobalPosition = _key.GlobalPosition;
				particles.Restart();
				particles.Emitting = true;
			}
		}
		//set the HUD message and variable to reflect that player has key
		_keyStatus.Text = "you have\nthe key";
		_door.HasKey = true;
	}
	
	//handle player reaching the door without the hey
	public async void _on_door_need_key()
	{
		//show message that the player needs to get the key for 
		//.4 seconds, then hide message 
		_getTheKey.Show();
		await ToSignal(GetTree().CreateTimer(0.4f), SceneTreeTimer.SignalName.Timeout);
		_getTheKey.Hide();
	}

	//handle menu when start game is pressed
	public void _on_main_menu_start_game()
	{
		//hide main menu and set messages to appropriate states	
		_mainMenu.Hide();
		_boostMessage.Hide();
		_jumpBoost.Show();

		//set player physics
		_player.Speed = 200.0f;
		_player.JumpForce = -275.0f;
		_player.CanMove = true;
		
		// reset key and door state
		_key.Show();
		_door.HasKey = false;

		// update HUD text
		var keyStatus = _hudTutorial.GetNode<Label>("keyStatus");
		keyStatus.Text = "you need\nthe key";
	
		
	}

	//handle messages for player reaching door with key
	public void _on_door_show_won()
	{
		//show you win message, hide extraneous messages
		_youWin.Show();
		_boostMessage.Hide();
	}

	//handle player reaching door with key - winning!
	public void _on_door_game_won()
	{
		GD.Print("won!");
		//freeze the player, set their position to start
		_player.SetPhysicsProcess(false);
		_player.GlobalPosition = new Vector2(80, 150);
		_player.Velocity = Vector2.Zero;
		_player.SetPhysicsProcess(true);
		_player.CanMove = false;

		//reset door animations 
		_door._ap.Play("closed");
		_youWin.Hide();
		_door.GetNode<Label>("DoorLabel").Hide();
		_door.GetNode<Sprite2D>("DoorLabel/arrow").Show();

		//go to show game won function
		_mainMenu.show_game_won();
	}
}
