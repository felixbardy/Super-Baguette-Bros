#include "Animation.h"
#include <cassert>
#include <iostream>

LinearAnimation createLinearAnimation(
    Entity* object, Vec2f start_point, Vec2f movement,
    float speed, void* origin_segment
)
{
    LinearAnimation anim;
    anim.object = object;
    anim.type   = LINEAR;
    anim.origin_segment = origin_segment;

    anim.start_point    = start_point;
    anim.movement       = movement;
    anim.speed          = speed;

    return anim;
}

RotationAnimation createRotationAnimation(
    Entity* object, float start_angle, float rotation_speed,
    void* origin_segment
)
{
    RotationAnimation anim;
    anim.object = object;
    anim.type   = ROTATION;
    anim.origin_segment = origin_segment;

    anim.start_angle    = start_angle;
    anim.rotation_speed = rotation_speed;

    return anim;
}

BouncyAnimation createBouncyAnimation(
    Entity* object, float rebound_height, float rebound_width,
    int max_bounces, void* origin_segment
)
{
    BouncyAnimation anim;
    anim.object = object;
    anim.type   = BOUNCY;
    anim.origin_segment = origin_segment;

    anim.height         = rebound_height;
    anim.width          = rebound_width;
    anim.max_bounces    = max_bounces;
    anim.bounces = 0;

    return anim;
}

PhysicAnimation createPhysicAnimation(
    Entity* object, Vec2f acceleration, float bounciness,
    void* origin_segment
)
{
    PhysicAnimation anim;
    anim.object = object;
    anim.type   = PHYSIC;
    anim.origin_segment = origin_segment;

    anim.acc        = acceleration;
    anim.bounciness = bounciness;

    return anim;
}

void testRegressionAnimations()
{       
    Entity* objtest = nullptr;
    Vec2f vstart;
    Vec2f vftest;
    vftest.x = 10;
    vftest.y = 10;
    void * origin = nullptr;
    float floattest = 5.1;

    cout << "Animation: LinearAnimation... ";
    LinearAnimation linear = createLinearAnimation(objtest, vstart, vftest, floattest, origin);
    assert(linear.object == nullptr);
    assert(linear.type == LINEAR);
    assert(linear.origin_segment == nullptr);
    assert(linear.start_point.x == 0 && linear.start_point.y == 0);
    assert(linear.movement.x == 10 && linear.movement.y == 10);
    assert(linear.speed == floattest);
    cout << "OK" << endl;

    cout << "Animation: RotationAnimation... ";
    RotationAnimation rotation = createRotationAnimation(objtest, floattest, floattest, origin);
    assert(rotation.object == nullptr);
    assert(rotation.type == ROTATION);
    assert(rotation.origin_segment == nullptr);
    assert(rotation.start_angle == floattest && rotation.rotation_speed == floattest);
    cout << "OK" << endl;

    cout << "Animation: BouncyAnimation... ";
    BouncyAnimation bouncy = createBouncyAnimation(objtest, floattest, floattest, 5, origin);
    assert(bouncy.object == nullptr);
    assert(bouncy.type == BOUNCY);
    assert(bouncy.origin_segment == nullptr);
    assert(bouncy.height == floattest && bouncy.width == floattest);
    assert(bouncy.max_bounces == 5 && bouncy.bounces == 0);
    cout << "OK" << endl;

    cout << "Animation: PhysicAnimation... ";
    PhysicAnimation physic = createPhysicAnimation(objtest, vftest, floattest, origin);
    assert(physic.object == nullptr);
    assert(physic.type == PHYSIC);
    assert(physic.origin_segment == nullptr);
    assert(physic.acc.x == vftest.x && physic.acc.y == vftest.y);
    assert(physic.bounciness == floattest);
    cout << "OK" << endl;
}
