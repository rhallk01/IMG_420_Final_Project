#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>

namespace godot {

class SurfaceMaterial : public Resource {
    GDCLASS(SurfaceMaterial, Resource)

private:
    //declare private variables
    float hardness = 1.0f;

protected:
    // devclare protected functions (bind methods)
    static void _bind_methods();

public:
    //declare public functions
    SurfaceMaterial();
    void set_hardness(float p_hardness);
    float get_hardness() const;
};

}
