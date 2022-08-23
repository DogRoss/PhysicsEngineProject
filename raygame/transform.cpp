#include "transform.h"

transform::transform() {
	position = *new Vector2();
	position.x = 0; position.y = 0;
}
transform::transform(float x, float y) {
	position = *new Vector2();
	position.x = x; position.y = y;
}
transform::transform(Vector2 pos) {
	position = pos;
}

void transform::translate(float newX, float newY) {
	position.x = newX; position.y = newY;
}
void transform::translate(Vector2 newPos) {
	position = newPos;
}