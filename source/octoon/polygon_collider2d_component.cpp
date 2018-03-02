#include <octoon/polygon_collider2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(PolygonCollider2D, GameComponent, "PolygonCollider2D")

    PolygonCollider2D::PolygonCollider2D() noexcept
        :is_registered(false)
    {

    }

    PolygonCollider2D::~PolygonCollider2D()
    {

    }

    GameComponentPtr PolygonCollider2D::clone() const noexcept
    {
        return std::make_shared<PolygonCollider2D>();
    }

    void PolygonCollider2D::set_auto_tiling(bool is_auto_tilling) noexcept
    {
        auto_tiling = is_auto_tilling;
        on_collision_change();
    }

    bool PolygonCollider2D::get_auto_tiling() const noexcept
    {
        return auto_tiling;
    }

    void PolygonCollider2D::set_path_count(int n) noexcept
    {
        path_count = n;
        on_collision_change();
    }

    int PolygonCollider2D::get_path_count() const noexcept
    {
        return path_count;
    }

    void PolygonCollider2D::set_points(const math::Vector2Array& pts) noexcept
    {
        points = pts;
        on_collision_change();
    }

    math::Vector2Array PolygonCollider2D::get_points() const noexcept
    {
        return points;
    }

    void PolygonCollider2D::on_collision_change() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        if(!is_registered)
            return;
        
        b2PolygonShape shape_def;
        shape_def.SetAsBox(size.x, size.y);
        shape_def.m_radius = edge_radius;

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        rigid_body->body->DestroyFixture(collider);
        collider = rigid_body->body->CreateFixture(&fixture_def);
    }

    void PolygonCollider2D::on_collision_enter() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;
        
        b2PolygonShape shape_def;
        shape_def.SetAsBox(size.x, size.y);
        shape_def.m_radius = edge_radius;

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        collider = rigid_body->body->CreateFixture(&fixture_def);

        is_registered = true;
    }

    void PolygonCollider2D::on_collision_exit() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        if(!is_registered)
            return;

        rigid_body->body->DestroyFixture(collider);
    }

    void PolygonCollider2D::on_collision_stay() noexcept
    {

    }

    void PolygonCollider2D::on_attach() except
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        on_collision_enter();
    }

    void PolygonCollider2D::on_detach() noexcept
    {
        on_collision_exit();
    }

    void PolygonCollider2D::on_attach_component(const GameComponentPtr& component) except
    {
        if (component->is_a<Rigidbody2D>())
        {
            on_collision_enter();
        }
    }

    void PolygonCollider2D::on_detach_component(const GameComponentPtr& component) noexcept
    {
    }
}