#include <octoon/edge_collider2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(EdgeCollider2D, GameComponent, "EdgeCollider2D")

    EdgeCollider2D::EdgeCollider2D() noexcept
        :is_registered(false)
    {

    }

    EdgeCollider2D::~EdgeCollider2D()
    {

    }

    GameComponentPtr EdgeCollider2D::clone() const noexcept
    {
        return std::make_shared<EdgeCollider2D>();
    }

    void EdgeCollider2D::set_edge_count(int n) noexcept
    {
        edge_count = n;
        on_collision_change();
    }

    int EdgeCollider2D::get_edge_count() const noexcept
    {
        return edge_count;
    }

    void EdgeCollider2D::set_point_count(int n) noexcept
    {
        point_count = n;
        on_collision_change();
    }

    int EdgeCollider2D::get_point_count() const noexcept
    {
        return point_count;
    }

    void EdgeCollider2D::set_edge_radius(float r) noexcept
    {
        edge_radius = r;
        on_collision_change();
    }

    float EdgeCollider2D::get_edge_radius() const noexcept
    {
        return edge_radius;
    }

    void EdgeCollider2D::set_points(const math::Vector2Array& pts) noexcept
    {
        points = pts;
        on_collision_change();
    }

    math::Vector2Array EdgeCollider2D::get_points() const noexcept
    {
        return points;
    }

    void EdgeCollider2D::on_collision_change() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        if(!is_registered)
            return;
        
        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2PolygonShape shape_def;
        shape_def.Set(vertices.data(), vertices.size());
        shape_def.m_radius = edge_radius;

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        rigid_body->body->DestroyFixture(collider);
        collider = rigid_body->body->CreateFixture(&fixture_def);
    }

    void EdgeCollider2D::on_collision_enter() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;
        
        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2PolygonShape shape_def;
        shape_def.Set(vertices.data(), vertices.size());
        shape_def.m_radius = edge_radius;

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        collider = rigid_body->body->CreateFixture(&fixture_def);

        is_registered = true;
    }

    void EdgeCollider2D::on_collision_exit() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        if(!is_registered)
            return;

        rigid_body->body->DestroyFixture(collider);
    }

    void EdgeCollider2D::on_collision_stay() noexcept
    {

    }

    void EdgeCollider2D::on_attach() except
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        on_collision_enter();
    }

    void EdgeCollider2D::on_detach() noexcept
    {
        on_collision_exit();
    }

    void EdgeCollider2D::on_attach_component(const GameComponentPtr& component) except
    {
        if (component->is_a<Rigidbody2D>())
        {
            on_collision_enter();
        }
    }

    void EdgeCollider2D::on_detach_component(const GameComponentPtr& component) noexcept
    {
    }
}