#include <octoon/circleCollider2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(CircleCollider2D, Collider2D, "CircleCollider2D")

    CircleCollider2D::CircleCollider2D() noexcept
        :isRegistered(false)
    {

    }

    CircleCollider2D::~CircleCollider2D()
    {

    }

    GameComponentPtr CircleCollider2D::clone() const noexcept
    {
        return std::makeShared<CircleCollider2D>();
    }

    void CircleCollider2D::setRadius(float r) noexcept
    {
        radius = r;
        onCollisionChange();
    }

    float CircleCollider2D::getRadius() const noexcept
    {
        return radius;
    }

    void CircleCollider2D::onCollisionChange() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;
        
        b2CircleShape shapeDef;
        shapeDef.mP = b2Vec2(rigidBody->getPosition().x, rigidBody->getPosition().y);
        shapeDef.mRadius = this->getRadius();

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        rigidBody->body->DestroyFixture(collider);
        collider = rigidBody->body->CreateFixture(&fixtureDef);
    }

    void CircleCollider2D::onCollisionEnter() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;
        
        b2CircleShape shapeDef;
        shapeDef.mP = b2Vec2(rigidBody->getPosition().x, rigidBody->getPosition().y);
        shapeDef.mRadius = this->getRadius();

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        collider = rigidBody->body->CreateFixture(&fixtureDef);

        isRegistered = true;
    }

    void CircleCollider2D::onCollisionExit() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;

        rigidBody->body->DestroyFixture(collider);
    }

    void CircleCollider2D::onCollisionStay() noexcept
    {

    }

    void CircleCollider2D::onAttach() except
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        onCollisionEnter();
    }

    void CircleCollider2D::onDetach() noexcept
    {
        onCollisionExit();
    }

    void CircleCollider2D::onAttachComponent(const GameComponentPtr& component) except
    {
        if (component->isA<Rigidbody2D>())
        {
            onCollisionEnter();
        }
    }

    void CircleCollider2D::onDetachComponent(const GameComponentPtr& component) noexcept
    {
    }
}