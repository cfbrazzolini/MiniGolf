#version 130
in vec4 vPosition;
in vec4 vColor;
out vec4 color;

uniform float time;
uniform float f;
uniform float h;

void main()
{
	vec4 t = vPosition;
	//t.y = vPosition.y + h*sin(f*time + vPosition.x);
    gl_Position = t;
   // color = vColor;
}