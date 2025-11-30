#include "impact_event.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void ImpactEvent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_min_speed", "speed"), &ImpactEvent::set_min_speed);
    ClassDB::bind_method(D_METHOD("get_min_speed"), &ImpactEvent::get_min_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_speed"), "set_min_speed", "get_min_speed");

    ClassDB::bind_method(D_METHOD("set_particle_scene", "scene"), &ImpactEvent::set_particle_scene);
    ClassDB::bind_method(D_METHOD("get_particle_scene"), &ImpactEvent::get_particle_scene);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "particle_scene"),
        "set_particle_scene", "get_particle_scene");

    ClassDB::bind_method(D_METHOD("set_sound_event", "sound"), &ImpactEvent::set_sound_event);
    ClassDB::bind_method(D_METHOD("get_sound_event"), &ImpactEvent::get_sound_event);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "sound_event"),
        "set_sound_event", "get_sound_event");

    // Might use later - was considering, but then got tired - HB
    ClassDB::bind_method(D_METHOD("set_camera_shake", "strength"), &ImpactEvent::set_camera_shake);
    ClassDB::bind_method(D_METHOD("get_camera_shake"), &ImpactEvent::get_camera_shake);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_shake"),
        "set_camera_shake", "get_camera_shake");
}

void ImpactEvent::set_min_speed(float p) { min_speed = p; }
float ImpactEvent::get_min_speed() const { return min_speed; }

void ImpactEvent::set_particle_scene(const StringName& p) { particle_scene = p; }
StringName ImpactEvent::get_particle_scene() const { return particle_scene; }

void ImpactEvent::set_sound_event(const StringName& p) { sound_event = p; }
StringName ImpactEvent::get_sound_event() const { return sound_event; }

void ImpactEvent::set_camera_shake(float p) { camera_shake = p; }
float ImpactEvent::get_camera_shake() const { return camera_shake; }
