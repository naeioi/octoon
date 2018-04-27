#include <octoon/physics2d_feature.h>
#include <octoon/physics2d.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>
#include <Box2D/Box2D.h>

#include <octoon/runtime/except.h>
#include <octoon/runtime/rtti_factory.h>


namespace octoon
{
    OctoonImplementSubClass(Physics2DFeature, GameFeature, "Physics2DFeature")

	std::shared_ptr<b2World> Physics2DFeature::world;
    
	Physics2DFeature::Physics2DFeature() noexcept
	{

	}

	Physics2DFeature::~Physics2DFeature() noexcept
	{

	}

	std::shared_ptr<b2World> Physics2DFeature::getWorld() noexcept
	{
		return world;
	}

    void Physics2DFeature::onActivate() except
    {
		// get gravity
		math::Vector2 g = Physics2D::getGravity();
		b2Vec2 gravity;
		gravity.Set(g.x, g.y);


		world = std::make_unique<b2World>(gravity);

		world->SetAllowSleeping(true);
		world->SetWarmStarting(true);
    }

    void Physics2DFeature::onDeactivate() noexcept
    {

    }

    void Physics2DFeature::onInputEvent(const input::InputEvent& event) noexcept
    {

    }

    void Physics2DFeature::onReset() noexcept
    {

    }

    void Physics2DFeature::onFrameBegin() noexcept
    {

    }

    void Physics2DFeature::onFrame() except
    {

    }

    void Physics2DFeature::onFrameEnd() noexcept
    {

    }

    void Physics2DFeature::onOpenScene(const GameScenePtr& scene) except
    {

    }

	void Physics2DFeature::onCloseScene(const GameScenePtr& scene) noexcept
    {

    }

}