#include "dynamic_bounce_body_2d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/math.hpp>


using namespace godot;

// set up dynamic bounce body constructor
DynamicBounceBody2D::DynamicBounceBody2D() {
    prev_velocity = Vector2(0, 1); 
    set_sleeping(false);
    set_can_sleep(false);
}

void DynamicBounceBody2D::_bind_methods() {
    // bind method for size
    ClassDB::bind_method(D_METHOD("set_size", "size"), &DynamicBounceBody2D::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &DynamicBounceBody2D::get_size);
    //add property for size
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "size", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"),
                 "set_size", "get_size");

    // bind method for energy
    ClassDB::bind_method(D_METHOD("set_energy", "energy"), &DynamicBounceBody2D::set_energy);
    ClassDB::bind_method(D_METHOD("get_energy"), &DynamicBounceBody2D::get_energy);
    //add property for energy
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "energy", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"), 
             "set_energy", "get_energy");

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

    // binds for ImpactEvents
    ClassDB::bind_method(D_METHOD("set_fade_on_stop", "fade"), &DynamicBounceBody2D::set_fade_on_stop);
    ClassDB::bind_method(D_METHOD("get_fade_on_stop"), &DynamicBounceBody2D::get_fade_on_stop);
    ADD_PROPERTY(
        PropertyInfo(Variant::BOOL, "fade_on_stop"),
        "set_fade_on_stop", "get_fade_on_stop");

    ClassDB::bind_method(D_METHOD("set_impact_event", "event"), &DynamicBounceBody2D::set_impact_event);
    ClassDB::bind_method(D_METHOD("get_impact_event"), &DynamicBounceBody2D::get_impact_event);
    ADD_PROPERTY(
        PropertyInfo(
            Variant::OBJECT,"impact_event", PROPERTY_HINT_RESOURCE_TYPE, "ImpactEvent" ),
        "set_impact_event", "get_impact_event");

    ADD_SIGNAL(MethodInfo(
        "impact_event_signal",
        PropertyInfo(Variant::FLOAT, "impact_speed"),
        PropertyInfo(Variant::VECTOR2, "position"),
        PropertyInfo(Variant::FLOAT, "surface_factor")
    ));

    ADD_SIGNAL(MethodInfo("bounce_finished"));
    ADD_SIGNAL(MethodInfo("dissipated"));
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
void DynamicBounceBody2D::set_surface_material(const Ref<SurfaceMaterial>& p_mat) {
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

//set energy level
void DynamicBounceBody2D::set_energy(float p_energy) { 
    energy = p_energy; 
}
//get energy level
float DynamicBounceBody2D::get_energy() const { 
    return energy; 
}

// Start Impact events

void DynamicBounceBody2D::set_fade_on_stop(bool p_value) {
    fade_on_stop = p_value;
}
bool DynamicBounceBody2D::get_fade_on_stop() const {
    return fade_on_stop;
}
void DynamicBounceBody2D::set_impact_event(const Ref<ImpactEvent>& p_event) {
    impact_event = p_event;
}
Ref<ImpactEvent> DynamicBounceBody2D::get_impact_event() const {
    return impact_event;
}

// End Impact events


// virtual override of _integrate_forces to implement bouncing behavior
void DynamicBounceBody2D::_integrate_forces(PhysicsDirectBodyState2D *p_state) {
    // UtilityFunctions::print("Integrating forces...");

    // check that p_state is valid
    if (!p_state) {
        UtilityFunctions::print("Invalid PhysicsDirectBodyState2D pointer");
        return;
    }

    // get current and previous velocity
    Vector2 current_vel = p_state->get_linear_velocity();
    Vector2 old_vel = prev_velocity;  
    prev_velocity = current_vel;

    // Debug: print velocity each frame
    // UtilityFunctions::print("Velocity:", p_state->get_linear_velocity());

    // Check contacts but DO NOT return yet
    int contact_count = p_state->get_contact_count();
    // UtilityFunctions::print("Contact count:", contact_count);


    // check if energy is depleted
    if (energy <= 0.0f) {
        UtilityFunctions::print("Energy depleted, stopping integration.");
        p_state->set_linear_velocity(Vector2(0, 0));
        set_sleeping(true);
        emit_signal("bounce_finished");

        if (fade_on_stop) {
            emit_signal("dissipated");
            call_deferred("queue_free");
        }
        return;
    }

    if (contact_count == 0) {
        // UtilityFunctions::print("No contacts detected.");
        return;
    }

    // iterate through contacts to find ground contact
    for (int i = 0; i < contact_count; i++) {
        Vector2 normal = p_state->get_contact_local_normal(i);

        // check if facing up and moving downwards
        if (normal.y < -0.5f && old_vel.y > 0.0f) {

            //get vars for bounce calculation
            float impact_speed = old_vel.length();
            float surface_factor = 1.0f;
            // Do it this way to avoid posible dangling pointers
            if (surface_material.is_valid()) {
                surface_factor = surface_material->get_hardness();
            }
            // UtilityFunctions::print("Surface surface_factor = ", surface_factor);

            // Trigger ImpactEvent resource
            if (impact_event.is_valid() && impact_speed >= impact_event->get_min_speed()) {
                emit_signal("impact_event_signal", impact_speed, get_global_position(), surface_factor );
            }

            float size_factor = size;
            // calculate bounce speed
            float bounce_speed = base_strength * impact_speed * size_factor * surface_factor * energy;
            Vector2 new_vel = Vector2(current_vel.x, -bounce_speed);
            p_state->set_linear_velocity(new_vel);

            energy -= energy_loss_rate;
            if (energy < 0.0f) energy = 0.0f;

            break;
        }
    }
}

