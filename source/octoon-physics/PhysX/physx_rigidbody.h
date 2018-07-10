#ifndef OCTOON_PHYSX_RIGIDBODY_H_
#define OCTOON_PHYSX_RIGIDBODY_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_rigidbody.h>

namespace physx
{
	class PxRigidDynamic;
	class PxRigidBody;
	class PxRigidActor;
}

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysxRigidbody : public PhysicsRigidbody
        {
            OctoonDeclareSubInterface(PhysxRigidbody, PhysicsRigidbody)
        public:
            PhysxRigidbody() noexcept;
            virtual ~PhysxRigidbody() noexcept;

            virtual void setAngularVelocity(const math::float3& v) except;
			virtual math::float3 getAngularVelocity() const except;

            virtual void setMass(float m) except;
            virtual float getMass() const except;

            virtual void setSleepMode(RigidbodySleepMode mode) except;
            virtual RigidbodySleepMode getSleepMode() const except;

			virtual void setIsKinematic(bool type) except;
			virtual bool getIsKinematic() const except;
        protected:
            physx::PxRigidActor* body;

            float angularVelocity;
            float gravityScale; // The degree to which this object is affected by gravity.
			bool isKinematic;
            float mass; // Mass of the rigidbody.
            RigidbodySleepMode sleepMode;
            math::Vector3 velocity;
        };
    }
}

#endif //OCTOON_PHYSX_RIGIDBODY_H_