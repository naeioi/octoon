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
            physx::PxSceneDesc sceneDesc(physics->getTolerancesScale());
            Physics::setGravity(math::Vector3(0.f, -9.8f, 0.f));
            math::Vector3 g = Physics::getGravity();
            sceneDesc.gravity = physx::PxVec3(g.x, g.y, g.z);
            dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
            sceneDesc.cpuDispatcher = dispatcher;
            sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
            physicsScene = physics->createScene(sceneDesc);
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