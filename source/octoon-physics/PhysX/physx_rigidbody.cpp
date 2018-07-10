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

        void PhysxRigidbody::setAngularVelocity(const math::float3& v) except
        {
            if ( !isKinematic && body)
            {
                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                rigid_body->setAngularVelocity(physx::PxVec3(v.x, v.y, v.z));
            }
        }
        math::float3 PhysxRigidbody::getAngularVelocity() const except
        {
            math::float3 retval;
            if (!isKinematic && body)
            {
                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                physx::PxVec3 v = rigid_body->getAngularVelocity();
                retval.x = v.x;
                retval.y = v.y;
                retval.z = v.z;
            }

            return retval;
        }

        void PhysxRigidbody::setMass(float m) except
        {
            if (!isKinematic && body)
            {
                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                rigid_body->setMass(m);
            }
        }
        float PhysxRigidbody::getMass() const except
        {
            float retval;
            if (!isKinematic && body)
            {
                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                retval = rigid_body->getMass();
            }

            return retval;
        }

        void PhysxRigidbody::setSleepMode(RigidbodySleepMode mode) except
        {
            sleepMode = mode;
            if(sleepMode == RigidbodySleepMode::NeverSleep)
            {
            }
            else if(sleepMode == RigidbodySleepMode::StartAsleep)
            {
            }
            else if(sleepMode == RigidbodySleepMode::StartAwake)
            {
            }
        }
        RigidbodySleepMode PhysxRigidbody::getSleepMode() const except
        {
            return sleepMode;
        }

        void PhysxRigidbody::setIsKinematic(bool type) except
        {
            if (isKinematic != type)
            {
                isKinematic = type;
                releaseRigidBody();
                buildRigidBody();
            }
        }
        bool PhysxRigidbody::getIsKinematic() const except
        {
            return isKinematic;
        }
    }
}