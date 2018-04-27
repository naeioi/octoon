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
		auto instance = std::make_shared<Rigidbody2D>();
		return instance;
    }

    void Rigidbody2D::setAngularVelocity(float v) noexcept
    {
        angularVelocity = v;
        if(body)
            body->SetAngularVelocity(angularVelocity);
    }

    float Rigidbody2D::getAngularVelocity() const noexcept
    {
        return angularVelocity;
    }

    void Rigidbody2D::setGravityScale(float scale) noexcept
    {
        gravityScale = scale;
        if(body)
            body->SetGravityScale(scale);
    }

    float Rigidbody2D::getGravityScale() const noexcept
    {
        return gravityScale;
    }

    void Rigidbody2D::setMass(float m) noexcept
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

    float Rigidbody2D::getMass() const noexcept
    {
        return mass;
    }

    void Rigidbody2D::setSleepMode(RigidbodySleepMode2D mode) noexcept
    {
        sleepMode = mode;
        if(sleepMode == RigidbodySleepMode2D::NeverSleep)
        {
            body->SetSleepingAllowed(false);
        }
        else if(sleepMode == RigidbodySleepMode2D::StartAsleep)
        {
            body->SetSleepingAllowed(true);
        }
        else if(sleepMode == RigidbodySleepMode2D::StartAwake)
        {
            body->SetSleepingAllowed(true);
        }
    }

    RigidbodySleepMode2D Rigidbody2D::getSleepMode() const noexcept
    {
        return sleepMode;
    }

    void Rigidbody2D::setBodyType(RigidbodyType2D type) noexcept
    {
        bodyType = type;
        if(body)
            body->SetType(static_cast<b2BodyType>(type));
    }

    RigidbodyType2D Rigidbody2D::getBodyType() const noexcept
    {
        return bodyType;
    }

    void Rigidbody2D::setPosition(math::Vector2 pos) noexcept
    {
        position = pos;
        if(body)
            body->SetTransform(b2Vec2(pos.x, pos.y), rotation);
    }

    math::Vector2 Rigidbody2D::getPosition() const noexcept
    {
        return position;
    }

    void Rigidbody2D::setRotation(float delta) noexcept
    {
        rotation = delta;
        if(body)
            body->SetTransform(b2Vec2(position.x, position.y), rotation);
    }

    float Rigidbody2D::getRotation() const noexcept
    {
        return rotation;
    }

    void Rigidbody2D::onAttach() except
    {
        addComponentDispatch(GameDispatchType::MoveAfter);
        if(body == nullptr)
            rigidbodyEnter();
    }

    void Rigidbody2D::onDetach() noexcept
    {
        removeComponentDispatch(GameDispatchType::MoveAfter);
    }

    void Rigidbody2D::onAttachComponent(const GameComponentPtr& component) noexcept
    {
        //if (component->isA<Collider2D>())
		//    component->downcast<Collider2D>()->addShapeChangeListener(&OnCollisionChange);
    }

    void Rigidbody2D::onDetachComponent(const GameComponentPtr& component) noexcept
    {
        //if (component->isA<Collider2D>())
		//    component->downcast<Collider2D>()->removeShapeChangeListener(&OnCollisionChange);
    }

    void Rigidbody2D::rigidbodyEnter() noexcept
    {
        auto world = runtime::Singleton<Physics2DFeature>::instance()->getWorld();

        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)getBodyType();
        bodyDef.position.Set(getPosition().x, getPosition().y);
        bodyDef.angularVelocity = angularVelocity;
        bodyDef.linearVelocity = b2Vec2(velocity.x, velocity.y);
        bodyDef.gravityScale = gravityScale;
        if(sleepMode == RigidbodySleepMode2D::NeverSleep)
        {
            bodyDef.allowSleep = false;
        }
        else if(sleepMode == RigidbodySleepMode2D::StartAsleep)
        {
            bodyDef.allowSleep = true;
            bodyDef.awake = false;
        }
        else if(sleepMode == RigidbodySleepMode2D::StartAwake)
        {
            bodyDef.allowSleep = false;
            bodyDef.awake = true;
        }
        body = world->CreateBody(&bodyDef);
    }

    void Rigidbody2D::rigidbodyChange() noexcept
    {
    }

    void Rigidbody2D::rigidbodyExit() noexcept
    {
		auto world = runtime::Singleton<Physics2DFeature>::instance()->getWorld();

        if(body != nullptr)
            world->DestroyBody(body);
    }
}