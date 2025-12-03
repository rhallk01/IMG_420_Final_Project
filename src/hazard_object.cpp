#include "hazard_object.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

// --- Constructor / Destructor ---

HazardObject::HazardObject() {
    // You can set initial values here if needed
}

HazardObject::~HazardObject() {
    // Cleanup
}

// --- Bind Methods: Register signals and methods to Godot ---

void HazardObject::_bind_methods() {
    // We are no longer using 'player_hit_signal' for the primary kill logic.
    // The C++ call will now trigger the C# Die() method.
    // ClassDB::add_signal("HazardObject", MethodInfo("player_hit_signal"));
    
    // Register the C++ handler method so Godot can call it when the 'body_entered' signal fires
    ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &HazardObject::_on_body_entered);
}

// --- Ready: Set up contact monitoring and connect the signal ---

void HazardObject::_ready() {
    // Check if running in the editor. If so, don't execute runtime logic.
    if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    // A RigidBody2D needs contact monitoring turned on to emit the body_entered signal.
    set_contact_monitor(true);
    // Set max contacts to be safe (can be 1 for a simple kill)
    set_max_contacts_reported(1);
    
    // Connect the built-in RigidBody2D signal ('body_entered') to our C++ handler method
    Callable callable(this, "_on_body_entered");
    // Connects RigidBody2D's signal 'body_entered' to this object's method '_on_body_entered'
    connect("body_entered", callable);

    godot::UtilityFunctions::print("HazardObject initialized and body_entered signal connected.");
}

// --- Collision Handler: Implement the kill logic ---

void HazardObject::_on_body_entered(Node2D* body) {
    if (body) {
        // Debug output to show what was hit
        godot::UtilityFunctions::print("HazardObject detected collision with: ", body->get_class(), " (Name: ", body->get_name(), ")");
    }
    
    // Check if the colliding body exists and has the 'IsPlayer' method.
    if (body && body->has_method("IsPlayer")) {
        godot::UtilityFunctions::print("Player was hit by a falling hazard. DEATH TRIGGERED. Calling Player.Die().");
        
        // CRITICAL FIX: Direct call to the Player's C# Die method
        body->call("Die"); 
    }
}