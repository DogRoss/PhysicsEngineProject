#include "physics.h"

physics::physics() {
	gravity = *new Vector2();
	gravity.x = 0; gravity.y = -9.81;
}
physics::physics(float gravityForce) {
	gravity = *new Vector2();
	gravity.x = 0; gravity.y = gravityForce;
}

void physics::checkCollisions() {

}
