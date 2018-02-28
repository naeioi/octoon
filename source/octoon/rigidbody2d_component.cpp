#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Rigidbody2DComponent, GameComponent, "Rigidbody2DComponent")

    Rigidbody2DComponent::Rigidbody2DComponent() noexcept
    {
    }

	Rigidbody2DComponent::~Rigidbody2DComponent()
    {

    }

	GameComponentPtr Rigidbody2DComponent::clone() const noexcept
    {

    }

    void Rigidbody2DComponent::set_body_type(RigidbodyType2D type) noexcept
    {
        body_type = type;
    }

    RigidbodyType2D Rigidbody2DComponent::get_body_type() const noexcept
    {
        return body_type;
    }

    void Rigidbody2DComponent::set_position(math::Vector2 pos) noexcept
    {
        position = pos;
    }

    math::Vector2 Rigidbody2DComponent::get_position() const noexcept
    {
        return position;
    }

    void Rigidbody2DComponent::set_rotation(float delta) noexcept
    {
        rotation = delta;
    }

    float Rigidbody2DComponent::get_rotation() const noexcept
    {
        return rotation;
    }

    void Rigidbody2DComponent::on_activate() noexcept
    {
        add_component_dispatch(GameDispatchType::MoveAfter, this);
        build_rigibody();
    }

    void Rigidbody2DComponent::on_deactivate() noexcept
    {
        remove_component_dispatch(GameDispatchType::MoveAfter, this);
    }

    void Rigidbody2DComponent::on_attach_component(const GameComponentPtr& component) noexcept
    {
        /*
        if (component->is_a<Collider2DComponent>())
		    component->downcast<Collider2DComponent>()->addShapeChangeListener(&_onCollisionChange);
            */
    }

    void Rigidbody2DComponent::on_detach_component(const GameComponentPtr& component) noexcept
    {
        /*
        if (component->is_a<Collider2DComponent>())
		    component->downcast<Collider2DComponent>()->removeShapeChangeListener(&_onCollisionChange);
            */
    }

    void Rigidbody2DComponent::on_collision_change() noexcept
    {
        build_rigibody();
    }
    void Rigidbody2DComponent::on_collision_enter() noexcept
    {

    }
    void Rigidbody2DComponent::on_collision_exit() noexcept
    {

    }
    void Rigidbody2DComponent::on_collision_stay() noexcept
    {

    }

    void Rigidbody2DComponent::build_rigibody() noexcept
    {
        b2World *world = runtime::Singleton<b2World>::instance();

        auto colliderShape = get_component<Collider2DComponent>();
        if (!colliderShape)
            return;

        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)get_body_type();
        bodyDef.position.Set(position.x, position.y);
        
        b2PolygonShape shape;
        shape.SetAsBox(VisibleRect::right().x * PTM_RATIO, 0);

        b2FixtureDef fixture;
        fixture.shape = &shape;
        body = world->CreateBody(&bodyDef);
        body->CreateFixture(&fixture); 
    }
}