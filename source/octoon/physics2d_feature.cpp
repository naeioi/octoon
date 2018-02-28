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
    
    void Physics2DFeature::on_activate() except
    {

    }

    void Physics2DFeature::on_deactivate() noexcept
    {

    }

    void Physics2DFeature::on_input_event(const input::InputEvent& event) noexcept
    {

    }

    void Physics2DFeature::on_reset() noexcept
    {

    }

    void Physics2DFeature::on_frame_begin() noexcept
    {

    }

    void Physics2DFeature::on_frame() except
    {

    }

    void Physics2DFeature::on_frame_end() noexcept
    {

    }

    void Physics2DFeature::on_open_scene(const GameScenePtr& scene) except
    {
        // get gravity
        math::Vector2 g = Physics2D::get_gravity();
        b2Vec2 gravity;
        gravity.Set(g.x,g.y);


        b2World *world = runtime::Singleton<b2World>::instance();

        world->SetAllowSleeping(true);
        world->SetWarmStarting(true);
    }

	void Physics2DFeature::on_close_scene(const GameScenePtr& scene) noexcept
    {

    }

}