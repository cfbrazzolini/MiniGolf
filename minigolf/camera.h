#ifndef CAMERA_H
#define CAMERA_H

#include "Angel.h"

typedef vec4 point4;

class Camera
{
protected:
	Camera::Camera(point4 eye,point4 at,vec4 up) : eye(eye),at(at),up(up){}
public:
	static Camera& Camera::getInstance(point4 eye = point4(0.0, 0.0, -1.0, 1.0), point4 at = point4(0.0, 0.0, -2.0, 1.0), vec4 up = vec4(0.0, 1.0, 0.0, 0.0)){
		static Camera c(eye, at, up);
		return c;
	}

	Camera::~Camera(){}

	point4 eye;
	point4 at;
	vec4 up;
};

#endif