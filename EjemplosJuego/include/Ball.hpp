#include <chipmunk/chipmunk.h>

class Ball {
public:
    Ball(cpSpace* space, float radius, float mass, const cpVect& position) {
        cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
        body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
        cpBodySetPosition(body, position);
        shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
        cpShapeSetFriction(shape, 0.7);
    }

    sf::CircleShape GetShape() {
        sf::CircleShape ballShape(20.0);
        cpVect ballPosition = cpBodyGetPosition(body);
        ballShape.setPosition(ballPosition.x, ballPosition.y);
        ballShape.setFillColor(sf::Color::Red);
        return ballShape;
    }

    ~Ball() {
        cpShapeFree(shape);
        cpBodyFree(body);
    }

    cpBody* getBody() {
        return body;
    }

private:
    int radius;
    cpBody* body;
    cpShape* shape;
};