#pragma once

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/physics_direct_body_state2d.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "surface_material.h"

namespace godot {

class DynamicBounceBody2D : public RigidBody2D {
    GDCLASS(DynamicBounceBody2D, RigidBody2D)

private:
    //declare private variables
    float size = 1.0f;
    float energy_loss_rate = 0.2f;
    float energy = 1.0f;
    float base_strength = 1.0f;
    Vector2 prev_velocity = Vector2();
    Ref<SurfaceMaterial> surface_material;

protected:
    //declare protected functions
    static void _bind_methods();

public:
    //declare public functions
    DynamicBounceBody2D();

    void set_surface_material(const Ref<SurfaceMaterial> &p_mat);
    Ref<SurfaceMaterial> get_surface_material() const { return surface_material; }

    //setters and getters
    void set_size(float p_size);
    float get_size() const;

    void set_energy_loss_rate(float p_rate);
    float get_energy_loss_rate() const;

    void set_base_strength(float p_strength);
    float get_base_strength() const;

    void set_energy(float p_energy);
    float get_energy() const;


    // virtual override of integrate forces
    virtual void _integrate_forces(PhysicsDirectBodyState2D *p_state) override;
};

}
