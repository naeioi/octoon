#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Rigidbody2D, GameComponent, "Rigidbody2D")

    Rigidbody2D::Rigidbody2D() noexcept
        :body(nullptr)
    {
    }

	Rigidbody2D::~Rigidbody2D()
    {

    }

	GameComponentPtr Rigidbody2D::clone() const noexcept
    {

    }

    void Rigidbody2D::set_angular_velocity(float v) noexcept
    {
        angular_velocity = v;
        if(body)
            body->SetAngularVelocity(angular_velocity);
    }

    float Rigidbody2D::get_angular_velocity() const noexcept
    {
        return angular_velocity;
    }

    void Rigidbody2D::set_gravity_scale(float scale) noexcept
    {
        gravity_scale = scale;
        if(body)
            body->SetGravityScale(scale);
    }

    float Rigidbody2D::get_gravity_scale() const noexcept
    {
        return gravity_scale;
    }

    void Rigidbody2D::set_mass(float m) noexcept
    {
        mass = m;
        if(body)
        {
            b2MassData data;
            body->GetMassData(&data);
            data.mass = m;
            body->SetMassData(&data);
        }
    }

    float Rigidbody2D::get_mass() const noexcept
    {
        return mass;
    }

    void Rigidbody2D::set_sleep_mode(RigidbodySleepMode2D mode) noexcept
    {
        sleep_mode = mode;
        if(sleep_mode == RigidbodySleepMode2D::NeverSleep)
        {
            body->SetSleepingAllowed(false);
        }
        else if(sleep_mode == RigidbodySleepMode2D::StartAsleep)
        {
            body->SetSleepingAllowed(true);
        }
        else if(sleep_mode == RigidbodySleepMode2D::StartAwake)
        {
            body->SetSleepingAllowed(true);
        }
    }

    RigidbodySleepMode2D Rigidbody2D::get_sleep_mode() const noexcept
    {
        return sleep_mode;
    }

    void Rigidbody2D::set_body_type(RigidbodyType2D type) noexcept
    {
        body_type = type;
        if(body)
            body->SetType(static_cast<b2BodyType>(type));
    }

    RigidbodyType2D Rigidbody2D::get_body_type() const noexcept
    {
        return body_type;
    }

    void Rigidbody2D::set_position(math::Vector2 pos) noexcept
    {
        position = pos;
        if(body)
            body->SetTransform(b2Vec2(pos.x, pos.y), rotation);
    }

    math::Vector2 Rigidbody2D::get_position() const noexcept
    {
        return position;
    }

    void Rigidbody2D::set_rotation(float delta) noexcept
    {
        rotation = delta;
        if(body)
            body->SetTransform(b2Vec2(position.x, position.y), rotation);
    }

    float Rigidbody2D::get_rotation() const noexcept
    {
        return rotation;
    }

    void Rigidbody2D::on_attach() except
    {
        add_component_dispatch(GameDispatchType::MoveAfter, this);
        if(body == nullptr)
            rigidbody_enter();
    }

    void Rigidbody2D::on_detach() noexcept
    {
        remove_component_dispatch(GameDispatchType::MoveAfter, this);
    }

    void Rigidbody2D::on_attach_component(const GameComponentPtr& component) noexcept
    {
        //if (component->is_a<Collider2D>())
		//    component->downcast<Collider2D>()->addShapeChangeListener(&_onCollisionChange);
    }

    void Rigidbody2D::on_detach_component(const GameComponentPtr& component) noexcept
    {
        //if (component->is_a<Collider2D>())
		//    component->downcast<Collider2D>()->removeShapeChangeListener(&_onCollisionChange);
    }

    void Rigidbody2D::rigidbody_enter() noexcept
    {
        b2World *world = runtime::Singleton<b2World>::instance();

        b2BodyDef body_def;
        body_def.type = (b2BodyType)get_body_type();
        body_def.position.Set(get_position().x, get_position().y);
        body_def.angularVelocity = angular_velocity;
        body_def.linearVelocity = b2Vec2(velocity.x, velocity.y);
        body_def.gravityScale = gravity_scale;
        if(sleep_mode == RigidbodySleepMode2D::NeverSleep)
        {
            body_def.allowSleep = false;
        }
        else if(sleep_mode == RigidbodySleepMode2D::StartAsleep)
        {
            body_def.allowSleep = true;
            body_def.awake = false;
        }
        else if(sleep_mode == RigidbodySleepMode2D::StartAwake)
        {
            body_def.allowSleep = false;
            body_def.awake = true;
        }
        body = world->CreateBody(&body_def);
    }

    void Rigidbody2D::rigidbody_change() noexcept
    {
    }

    void Rigidbody2D::rigidbody_exit() noexcept
    {
        b2World *world = runtime::Singleton<b2World>::instance();

        if(body != nullptr)
            world->DestroyBody(body);
    }
}