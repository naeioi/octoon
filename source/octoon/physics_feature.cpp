#include <stdexcept>

#include <octoon/game_object.h>
#include <octoon/transform_component.h>
#include <octoon/physics_feature.h>
#include <octoon/physics.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>

#include <octoon/runtime/except.h>
#include <octoon/runtime/rtti_factory.h>

#include <PxPhysicsAPI.h>

namespace octoon
{
    OctoonImplementSubClass(PhysicsFeature, GameFeature, "PhysicsFeature")

	PhysicsFeature::PhysicsFeature() except
		:
	{
	}

	PhysicsFeature::~PhysicsFeature() noexcept
	{
	}

    void PhysicsFeature::onActivate() except
    {
    }

    void PhysicsFeature::onDeactivate() noexcept
    {
    }

    void PhysicsFeature::onInputEvent(const input::InputEvent& event) noexcept
    {
    }

    void PhysicsFeature::onReset() noexcept
    {
    }

    void PhysicsFeature::onFrameBegin() noexcept
    {
    }

    void PhysicsFeature::onFrame() except
    {
    }

    void PhysicsFeature::onFrameEnd() noexcept
    {
    }

    void PhysicsFeature::onOpenScene(const GameScenePtr& scene) except
    {
    }

	void PhysicsFeature::onCloseScene(const GameScenePtr& scene) noexcept
    {
    }
}