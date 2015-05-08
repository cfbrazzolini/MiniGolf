#ifndef OBJECT_H
#define OBJECT_H

#include <cassert>
#include <vector>

#include "Angel.h"
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit

#define GL_CHECK_ERRORS \
{ \
	int err=glGetError(); \
	if (err!=0) \
		{   std::cout << "OpenGL Error: " << err << std::endl; \
		assert(err == GL_NO_ERROR); \
		} \
}

#define vec4to3( v ) vec3(v.x,v.y,v.z)

typedef Angel::vec4 point4;


class Object {
protected:
	// Data for a graphics object
	std::string name;
	std::vector<point4> vertex;
	std::vector<point4> normal;
	std::vector<vec2> mapcoord;

	static const int MAX_BUFFERS = 30;
	static const int MAX_UNIFORMS = 30;

	GLuint this_texture;

	// Shader variables for the graphics object
	GLuint program;
	GLuint vao;
	GLuint tex;
	GLuint buffers[MAX_BUFFERS];
	GLuint uniforms[MAX_UNIFORMS];
	GLuint texMapLocation;

private:

	virtual void init_data() = 0;	     // First:  init data function to set up normal and vertex and texture map coords if applicable
	virtual void init_VAO() = 0;         // Second: init VAO function
	virtual void init_VBO() = 0;         // Third:  init VBO function
	virtual void init_shader() = 0;	     // Fourth: init shader function to set up program
	virtual void init_texture_map() = 0; // Fifth:  init texture map function

public:

	Object::Object(std::string name) : name(name){};
	
	virtual void init() = 0;
	virtual void start_shader() = 0;     // Called from Draw: Start the shader for this object
	virtual void stop_shader() = 0;      // Called from Draw: STop the shader for this object
	virtual void draw() { };      // must override draw 
	virtual void cleanup() = 0;   // must provide a cleanup function
	GLuint get_shader_id() { return program; }

	vec3 pos;
};

#endif