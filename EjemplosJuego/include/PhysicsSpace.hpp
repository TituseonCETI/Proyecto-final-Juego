
class PhysicsSpace {
public:
    PhysicsSpace() {
        space = cpSpaceNew();
        cpVect gravity = cpv(0, 1000);
        cpSpaceSetGravity(space, gravity);
    }

    ~PhysicsSpace() {
        cpSpaceFree(space);
    }

    cpSpace* getSpace() {
        return space;
    }

private:
    cpSpace* space;
};
