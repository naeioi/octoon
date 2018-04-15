#include <octoon/edgeCollider2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(EdgeCollider2D, Collider2D, "EdgeCollider2D")

    EdgeCollider2D::EdgeCollider2D() noexcept
        :isRegistered(false)
    {

    }

    EdgeCollider2D::~EdgeCollider2D()
    {

    }

    GameComponentPtr EdgeCollider2D::clone() const noexcept
    {
        return std::makeShared<EdgeCollider2D>();
    }

    void EdgeCollider2D::setEdgeCount(int n) noexcept
    {
        edgeCount = n;
        onCollisionChange();
    }

    int EdgeCollider2D::getEdgeCount() const noexcept
    {
        return edgeCount;
    }

    void EdgeCollider2D::setPointCount(int n) noexcept
    {
        pointCount = n;
        onCollisionChange();
    }

    int EdgeCollider2D::getPointCount() const noexcept
    {
        return pointCount;
    }

    void EdgeCollider2D::setEdgeRadius(float r) noexcept
    {
        edgeRadius = r;
        onCollisionChange();
    }

    float EdgeCollider2D::getEdgeRadius() const noexcept
    {
        return edgeRadius;
    }

    void EdgeCollider2D::setPoints(const math::Vector2Array& pts) noexcept
    {
        points = pts;
        onCollisionChange();
    }

    math::Vector2Array EdgeCollider2D::getPoints() const noexcept
    {
        return points;
    }

    void EdgeCollider2D::onCollisionChange() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;
        
        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2ChainShape shapeDef;
        shapeDef.CreateChain(vertices.data(), vertices.size());
        shapeDef.mRadius = edgeRadius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        rigidBody->body->DestroyFixture(collider);
        collider = rigidBody->body->CreateFixture(&fixtureDef);
    }

    void EdgeCollider2D::onCollisionEnter() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;
        
        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2ChainShape shapeDef;
        shapeDef.CreateChain(vertices.data(), vertices.size());
        shapeDef.mRadius = edgeRadius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        collider = rigidBody->body->CreateFixture(&fixtureDef);

        isRegistered = true;
    }

    void EdgeCollider2D::onCollisionExit() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;

        rigidBody->body->DestroyFixture(collider);
    }

    void EdgeCollider2D::onCollisionStay() noexcept
    {

    }

    void EdgeCollider2D::onAttach() except
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        onCollisionEnter();
    }

    void EdgeCollider2D::onDetach() noexcept
    {
        onCollisionExit();
    }

    void EdgeCollider2D::onAttachComponent(const GameComponentPtr& component) except
    {
        if (component->isA<Rigidbody2D>())
        {
            onCollisionEnter();
        }
    }

    void EdgeCollider2D::onDetachComponent(const GameComponentPtr& component) noexcept
    {
    }
}