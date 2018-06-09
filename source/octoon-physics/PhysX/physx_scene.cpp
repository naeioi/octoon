#include <octoon/physics/Physx/physics_scene.h>

#include <PxPhysicsAPI.h>

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
            if(physicsScene) physicsScene->release();
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

        void addPhysicsRigidbody(PhysicsRigidbodyPtr rigidbody) noexcept
        {

        }

        void setPhysicsScene(physx::PxScene* scene) noexcept
        {
            physicsScene = scene;
        }

        void setAccumulator(float a) noexcept
        {
            accumulator = a;
        }

        void setStepSize(float s) noexcept
        {
            stepSize = s;
        }
    }
}