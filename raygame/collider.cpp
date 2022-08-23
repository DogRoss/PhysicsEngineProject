#include "collider.h"

collider::collider() {
	//default to box collider
	circleCol = false;
	radius = 1;
	enabled = false;
}
collider::collider(bool isActive) {
	//default to box collider
	circleCol = false;
	radius = 1;
	enabled = isActive;
}
collider::collider(float radiusLength, bool isCircleCollider) {
	radius = radiusLength;
	circleCol = isCircleCollider;
	enabled = true;
}
collider::collider(float radiusLength, bool isCircleCollider, bool isActive) {
	radius = radiusLength;
	circleCol = isCircleCollider;
	enabled = isActive;
}

//functions
void collider::collision() {

}