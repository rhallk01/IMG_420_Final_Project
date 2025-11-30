#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string_name.hpp>

namespace godot {

    class ImpactEvent : public Resource {
        GDCLASS(ImpactEvent, Resource)

    private:
        float min_speed = 0.0f;
        StringName particle_scene;
        StringName sound_event;
        float camera_shake = 0.0f;

    protected:
        static void _bind_methods();

    public:
        ImpactEvent() = default;

        void set_min_speed(float p);
        float get_min_speed() const;

        void set_particle_scene(const StringName& p);
        StringName get_particle_scene() const;

        void set_sound_event(const StringName& p);
        StringName get_sound_event() const;

        void set_camera_shake(float p);
        float get_camera_shake() const;
    };

} // namespace godot
