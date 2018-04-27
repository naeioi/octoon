#include <octoon/physics_material2d.h>
#include <octoon/physics2d.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>
#include <Box2D/Box2D.h>

#include <octoon/runtime/except.h>
#include <octoon/runtime/rtti_factory.h>


namespace octoon
{
    OctoonImplementSubClass(PhysicsMaterial2D, runtime::RttiInterface, "PhysicsMaterial2D")

	PhysicsMaterial2D::PhysicsMaterial2D() noexcept
	{

	}

	PhysicsMaterial2D::~PhysicsMaterial2D()
	{

	}

    void PhysicsMaterial2D::setBounciness(float b) noexcept
    {
        bounciness = b;
    }

    float PhysicsMaterial2D::getBounciness() const noexcept
    {
        return bounciness;
    }

    void PhysicsMaterial2D::setFriction(float f) noexcept
    {
        f = friction;
    }

    float PhysicsMaterial2D::getFriction() const noexcept
    {
        return friction;
    }
}