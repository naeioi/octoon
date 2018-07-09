#ifndef OCTOON_PHYSICS_RIGIDBODY_H_
#define OCTOON_PHYSICS_RIGIDBODY_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

namespace octoon
{
    namespace physics
    {
        enum class RigidbodySleepMode:int
        {
            NeverSleep, //Rigidbody never automatically sleeps.
            StartAwake, //Rigidbody is initially awake.
            StartAsleep, //Rigidbody is initially asleep.
        };

        class OCTOON_EXPORT PhysicsRigidbody : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsRigidbody, runtime::RttiInterface)
        public:
            PhysicsRigidbody() noexcept;
            virtual ~PhysicsRigidbody() noexcept;

            virtual void setAngularVelocity(const math::float3& v) except = 0;
			virtual math::float3 getAngularVelocity() const except = 0;

            virtual void setMass(float m) except = 0;
            virtual float getMass() const except = 0;

            virtual void setSleepMode(RigidbodySleepMode mode) except = 0;
            virtual RigidbodySleepMode getSleepMode() const except = 0;

			virtual void setIsKinematic(bool type) except = 0;
			virtual bool getIsKinematic() const except = 0;
        };
    }
}

#endif //OCTOON_PHYSICS_RIGIDBODY_H_