#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Rigidbody2D, GameComponent, "Rigidbody2D")

    Rigidbody2D::Rigidbody2D() noexcept
    {
    }

	Rigidbody2D::~Rigidbody2D()
    {

    }

	GameComponentPtr Rigidbody2D::clone() const noexcept
    {

    }

    void Rigidbody2D::set_body_type(RigidbodyType2D type) noexcept
    {
        body_type = type;
    }

    RigidbodyType2D Rigidbody2D::get_body_type() const noexcept
    {
        return body_type;
    }

    void Rigidbody2D::set_position(math::Vector2 pos) noexcept
    {
        position = pos;
    }

    math::Vector2 Rigidbody2D::get_position() const noexcept
    {
        return position;
    }

    void Rigidbody2D::set_rotation(float delta) noexcept
    {
        rotation = delta;
    }

    float Rigidbody2D::get_rotation() const noexcept
    {
        return rotation;
    }

    void Rigidbody2D::on_activate() noexcept
    {
        add_component_dispatch(GameDispatchType::MoveAfter, this);
        build_rigibody();
    }

    void Rigidbody2D::on_deactivate() noexcept
    {
        remove_component_dispatch(GameDispatchType::MoveAfter, this);
    }

    void Rigidbody2D::on_attach_component(const GameComponentPtr& component) noexcept
    {
        if (component->is_a<Collider2D>())
		    component->downcast<Collider2D>()->addShapeChangeListener(&_onCollisionChange);
    }

    void Rigidbody2D::on_detach_component(const GameComponentPtr& component) noexcept
    {
        if (component->is_a<Collider2D>())
		    component->downcast<Collider2D>()->removeShapeChangeListener(&_onCollisionChange);
    }

    void Rigidbody2D::build_rigibody() noexcept
    {
        b2World *world = runtime::Singleton<b2World>::instance();

        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)get_body_type();
        bodyDef.position.Set(get_position().x, get_position().y);
        body = world->CreateBody(&bodyDef);
    }
}