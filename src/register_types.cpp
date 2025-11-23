#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "surface_material.h"
#include "dynamic_bounce_body_2d.h"

using namespace godot;

// initialize functions for the extension
void initialize_bounce_extension(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<SurfaceMaterial>();
    ClassDB::register_class<DynamicBounceBody2D>();
}

// uninitialize functions for the extension
void uninitialize_bounce_extension(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {

// initialization
GDExtensionBool GDE_EXPORT bounce_extension_library_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization* r_initialization)
{
    GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_bounce_extension);
    init_obj.register_terminator(uninitialize_bounce_extension);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}

} 