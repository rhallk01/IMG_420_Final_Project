#include "dynamic_bounce_body_2d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;


void DynamicBounceBody2D::_bind_methods() {
    // bind method for size
    ClassDB::bind_method(D_METHOD("set_size", "size"), &DynamicBounceBody2D::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &DynamicBounceBody2D::get_size);
    //add property for size
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "size", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"),
                 "set_size", "get_size");

    // bind method for energy_loss_rate
    ClassDB::bind_method(D_METHOD("set_energy_loss_rate", "rate"), &DynamicBounceBody2D::set_energy_loss_rate);
    ClassDB::bind_method(D_METHOD("get_energy_loss_rate"), &DynamicBounceBody2D::get_energy_loss_rate);
    //add property for energy_loss_rate
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "energy_loss_rate", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
                 "set_energy_loss_rate", "get_energy_loss_rate");

    // bind method for setting and getting surface_material
    ClassDB::bind_method(D_METHOD("set_surface_material", "material"), &DynamicBounceBody2D::set_surface_material);
    ClassDB::bind_method(D_METHOD("get_surface_material"), &DynamicBounceBody2D::get_surface_material);
    //add property for surface_material
    ADD_PROPERTY(
        PropertyInfo(Variant::OBJECT, "surface_material", PROPERTY_HINT_RESOURCE_TYPE, "SurfaceMaterial"),
        "set_surface_material", "get_surface_material"
    );

    // bind method for base_strength
    ClassDB::bind_method(D_METHOD("set_base_strength", "strength"), &DynamicBounceBody2D::set_base_strength);
    ClassDB::bind_method(D_METHOD("get_base_strength"), &DynamicBounceBody2D::get_base_strength);
    //add property for base_strength
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base_strength", PROPERTY_HINT_RANGE, "0.1,5.0,0.1"),
                 "set_base_strength", "get_base_strength");
}
//set size of the dynamic bounce body
void DynamicBounceBody2D::set_size(float p_size) {
    // make sure size is positive
    if (p_size <= 0.0f) {
        UtilityFunctions::push_warning("DynamicBounceBody2D: size must be > 0. Using default 1.0.");
        size = 1.0f;
    } else {
        size = p_size;
    }
}

//get size of the dynamic bounce body
float DynamicBounceBody2D::get_size() const {
    return size;
}

//set energy loss rate (between 0 and 1)
void DynamicBounceBody2D::set_energy_loss_rate(float p_rate) {
    energy_loss_rate = Math::clamp(p_rate, 0.0f, 1.0f);
}

//get energy loss rate
float DynamicBounceBody2D::get_energy_loss_rate() const {
    return energy_loss_rate;
}

//set surface material
void DynamicBounceBody2D::set_surface_material(SurfaceMaterial *p_mat) {
    surface_material = p_mat;
}

// set base strength for bounce calculation
void DynamicBounceBody2D::set_base_strength(float p_strength) {
    base_strength = MAX(p_strength, 0.0f);
}

//get base strength
float DynamicBounceBody2D::get_base_strength() const {
    return base_strength;
}

// virtual override of _integrate_forces to implement bouncing behavior
void DynamicBounceBody2D::_integrate_forces(PhysicsDirectBodyState2D *p_state) {
    // check that p_state is valid
    if (!p_state) {
        return;
    }
    // check if energy is depleted
    if (energy <= 0.0f) {
        return;
    }
    // get contact count
    const int contact_count = p_state->get_contact_count();
    if (contact_count == 0) {
        return;
    }
    // get current linear velocity
    Vector2 linear_vel = p_state->get_linear_velocity();

    // iterate through contacts to find ground contact
    for (int i = 0; i < contact_count; i++) {
        Vector2 normal = p_state->get_contact_local_normal(i);

        // check if facing up and moving downwards
        if (normal.y < -0.5f && linear_vel.y > 0.0f) {
            float impact_speed = linear_vel.length();

            float surface_factor = 1.0f;
            if (surface_material) {
                surface_factor = surface_material->get_hardness();
            } else {
                UtilityFunctions::push_warning("DynamicBounceBody2D: surface_material not set, using default factor 1.0.");
            }

            // calculate bounce speed using size, base strength, surface material, and energy
            float size_factor = size;
            float bounce_speed = base_strength * impact_speed * size_factor * surface_factor * energy;

            linear_vel.y = -bounce_speed;
            p_state->set_linear_velocity(linear_vel);

            // reduce energy based on loss rate
            energy -= energy_loss_rate;
            if (energy < 0.0f) {
                energy = 0.0f;
                p_state->set_linear_velocity(Vector2(linear_vel.x, 0.0f));
            }

            // stop bouncing when energy is too low
            if (linear_vel.length() < 2.0f) {
                p_state->set_linear_velocity(Vector2(0, 0));
                set_sleeping(true);
            }

            break;
        }
    }
}
