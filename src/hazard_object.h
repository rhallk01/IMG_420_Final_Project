#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "dynamic_bounce_body_2d.h" // Assuming this is where DynamicBounceBody2D is defined

namespace godot {

class HazardObject : public DynamicBounceBody2D {
    GDCLASS(HazardObject, DynamicBounceBody2D)

protected:
    // Binds the class methods and signals to Godot's ClassDB
    static void _bind_methods();

public:
    // Constructor
    HazardObject();
    
    // Destructor
    ~HazardObject();

    // FIX: Moved _ready to public, as virtual methods registered with Godot's ClassDB
    // need to be publicly accessible for the binding system to find them.
    void _ready() override;

    // Custom collision handler method, connected to the built-in RigidBody2D::body_entered signal
    void _on_body_entered(Node2D* body);
};

} // namespace godot