#ifndef OCTOON_PHYSICS_TYPES_H_
#define OCTOON_PHYSICS_TYPES_H_

#include <memory>

#include <octoon/runtime/platform.h>

#include <octoon/physics/physics_scene.h>
#include <octoon/physics/physics_system.h>
#include <octoon/physics/physics_rigidbody.h>

namespace octoon
{
    namespace physics
    {
        using PhysicsScenePtr = std::shared_ptr<PhysicsScene>;
        using PhysicsRigidbodyPtr = std::shared_ptr<PhysicsRigidbody>;
        using PhysicsSystemPtr = PhysicsSystem*;
        
    }
}

#endif //OCTOON_PHYSICS_TYPES_H_