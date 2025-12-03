#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "surface_material.h"
#include "impact_event.h" // Added ImpactEvent header
#include "dynamic_bounce_body_2d.h"
#include "hazard_object.h" // <-- NEW: Include the new class header

using namespace godot;

// initialize functions for the extension
void initialize_bounce_extension(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Register all custom classes
    ClassDB::register_class<godot::SurfaceMaterial>();
    ClassDB::register_class<godot::ImpactEvent>(); // Registered ImpactEvent
    ClassDB::register_class<godot::DynamicBounceBody2D>();
    ClassDB::register_class<godot::HazardObject>(); // <-- NEW: Register the HazardObject
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