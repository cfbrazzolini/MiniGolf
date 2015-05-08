#include "camera.h"


Camera::Camera(point4 eye, point4 at, vec4 up) : eye(eye), at(at), up(up)
{
}

Camera::Camera(){
	this->eye = point4(0.0, 0.0, -1.0, 1.0);
	this->at  = point4(0.0, 0.0, -2.0, 1.0);
	this->up  = vec4(0.0, 1.0, 0.0, 0.0);
}

Camera::~Camera()
{
}
