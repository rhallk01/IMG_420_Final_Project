#include "surface_material.h"
using namespace godot;

void SurfaceMaterial::_bind_methods() {
    // bindings for setting and getting hardness
    ClassDB::bind_method(D_METHOD("set_hardness", "hardness"), &SurfaceMaterial::set_hardness);
    ClassDB::bind_method(D_METHOD("get_hardness"), &SurfaceMaterial::get_hardness);

    // add hardness property so it's available in the editor
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "hardness", PROPERTY_HINT_RANGE, "0.0,5.0,0.1"),
                 "set_hardness", "get_hardness");
}

// explicit default constructor
SurfaceMaterial::SurfaceMaterial() {
    hardness = 1.0f;
    UtilityFunctions::print("SurfaceMaterial constructor RAN, hardness = ", hardness);
}


// set the hardness value
void SurfaceMaterial::set_hardness(float p_hardness) {
    hardness = p_hardness;
}

// get the hardness value
float SurfaceMaterial::get_hardness() const {
    return hardness;
}
