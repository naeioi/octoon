#include <octoon/physics/Physx/physics_scene.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysxScene, PhysicsScene, "PhysxScene")
        PhysxScene::PhysxScene() except
            : physicsScene(nullptr),
            accumulator(0.0f), stepSize(1.0f / 60.0f)
        {

        }
        PhysxScene::~PhysxScene() noexcept
        {

        }

        void PhysxScene::setGravity(const math::Vector3& gravity) noexcept
        {

        }
        math::Vector3 PhysxScene::getGravity() const noexcept
        {

        }

        void PhysxScene::simulation(float delta) noexcept
        {
            
        }
    }
}