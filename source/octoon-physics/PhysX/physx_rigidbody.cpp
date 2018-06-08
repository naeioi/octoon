#include <octoon/physics/physx_rigidbody.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysxRigidbody, PhysicsRigidbody, "PhysxRigidbody")
        PhysxRigidbody::PhysxRigidbody() noexcept
        {
            if (body)return;
            auto physicsFeature = GameApp::instance()->getFeature<PhysicsFeature>();

            auto transform = this->getComponent<TransformComponent>();

            if (!transform) return;
            auto& translate = transform->getTranslate();
            auto& rotation = transform->getQuaternion();

            physx::PxTransform pose;
            pose.p = physx::PxVec3(translate.x, translate.y, translate.z);
            pose.q = physx::PxQuat(rotation.x, rotation.y, rotation.z, rotation.w);

            if (isKinematic)
            {
                body = physicsFeature->getSDK()->createRigidStatic(pose);
                if (!body)
                    throw  runtime::runtime_error::create("create body failed!");
            }
            else
            {
                body = physicsFeature->getSDK()->createRigidDynamic(pose);
                if (!body)
                    throw  runtime::runtime_error::create("create body failed!");

                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                physx::PxRigidBodyExt::updateMassAndInertia(*rigid_body, mass);
            }

            physicsFeature->getScene()->addActor(*body);
        }
        PhysxRigidbody::~PhysxRigidbody() noexcept
        {

        }
    }
}