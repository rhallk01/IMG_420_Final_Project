#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class SurfaceMaterial : public RefCounted {
    GDCLASS(SurfaceMaterial, RefCounted)

private:
    //declare private variables
    float hardness = 1.0f;

protected:
    // devclare protected functions (bind methods)
    static void _bind_methods();

public:
    //declare public functions
    void set_hardness(float p_hardness);
    float get_hardness() const { return hardness; }
};

}
