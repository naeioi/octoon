#include <octoon/physics2dFeature.h>
#include <octoon/physics2d.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>
#include <Box2D/Box2D.h>

#include <octoon/runtime/except.h>
#include <octoon/runtime/rttiFactory.h>


namespace octoon
{
    OctoonImplementSubClass(Physics2DFeature, GameFeature, "Physics2DFeature")
    
    void Physics2DFeature::onActivate() except
    {

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
        // get gravity
        math::Vector2 g = Physics2D::getGravity();
        b2Vec2 gravity;
        gravity.Set(g.x,g.y);


        b2World *world = runtime::Singleton<b2World>::instance();

        world->SetAllowSleeping(true);
        world->SetWarmStarting(true);
    }

	void Physics2DFeature::onCloseScene(const GameScenePtr& scene) noexcept
    {

    }

}