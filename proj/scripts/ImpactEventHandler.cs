using Godot;

public partial class ImpactEventHandler : Node2D
{
	private AudioStreamPlayer2D _audio;

	public override void _Ready()
	{
		// Create audio player dynamically
		_audio = new AudioStreamPlayer2D();
		AddChild(_audio);

		// Connect to parent's signal matching impact event
		var body = GetParent() as Node;
		if (body != null)
		{
			body.Connect("impact_event_signal", new Callable(this, nameof(OnImpactEvent)));
		}
	}

	private void OnImpactEvent(float impactSpeed, Vector2 position, float surfaceFactor)
	{
		var body = GetParent() as GodotObject;
		if (body == null)
			return;

		// Exposes impact_event as a property
		var impactEvent = (Resource)body.Get("impact_event");

		if (impactEvent == null)
		{
			GD.Print("ImpactEventHandler: No ImpactEvent resource found.");
			return;
		}

		var soundEventObj = impactEvent.Get("sound_event");
		string soundEventPath = "";

		if (soundEventObj.VariantType == Variant.Type.StringName)
		{
			soundEventPath = soundEventObj.AsStringName();
		}

		var sound = ResourceLoader.Load<AudioStream>(soundEventPath);

		var particleObj = impactEvent.Get("particle_scene");
		string particlePath = "";

		if (particleObj.VariantType == Variant.Type.StringName)
		{
			particlePath = particleObj.AsStringName();
		}

		if (!string.IsNullOrEmpty(particlePath))
		{
			var scene = ResourceLoader.Load<PackedScene>(particlePath);
			if (scene != null)
			{
				Node2D p = scene.Instantiate<Node2D>();
				p.GlobalPosition = position;
				GetTree().CurrentScene.AddChild(p);
				GetTree().CreateTimer(1.0).Timeout += () =>
				{
					if (IsInstanceValid(p))
						p.QueueFree();
				};
			}
			else
			{
				GD.Print($"ImpactEventHandler: Could not load particle scene at '{particlePath}'.");
			}
		}

		if (sound == null)
		{
			GD.Print($"ImpactEventHandler: Could not load sound at '{soundEventPath}'.");
			return;
		}

		_audio.Stream = sound;
		_audio.GlobalPosition = position;
		_audio.Play();
	}
}
