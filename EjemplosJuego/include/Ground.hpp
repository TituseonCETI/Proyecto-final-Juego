#include <chipmunk/chipmunk.h>

class Suelo {
public:
    Suelo(cpSpace* space) {
        cpBody* ground = cpSpaceGetStaticBody(space);
        shape = cpSegmentShapeNew(ground, cpv(0, 500), cpv(800, 500), 0);
        cpShapeSetFriction(shape, 1.0);
        cpSpaceAddShape(space, shape);
    }

    ~Suelo() {
        cpShapeFree(shape);
    }

private:
    cpShape* shape;
};