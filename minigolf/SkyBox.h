#ifndef SKY_BOX_H
#define SKY_BOX_H

#include "Object.h"


#define SKY_BOX_SCALE 500.0

point4  skybox_vertices[8] = {
	point4(-0.5, -0.5, 0.5, 1.0),
	point4(0.5, -0.5, 0.5, 1.0),
	point4(0.5, 0.5, 0.5, 1.0),
	point4(-0.5, 0.5, 0.5, 1.0),
	point4(-0.5, -0.5, -0.5, 1.0),
	point4(0.5, -0.5, -0.5, 1.0),
	point4(0.5, 0.5, -0.5, 1.0),
	point4(-0.5, 0.5, -0.5, 1.0)
};

class SkyBox : public Object{
public:
	SkyBox() : Object("SkyCube"){}
	void triangle(unsigned int a, unsigned int b, unsigned int c){

		normal.push_back(normalize(vec4to3(skybox_vertices[a])));
		vertex.push_back(skybox_vertices[a]);

		normal.push_back(normalize(vec4to3(skybox_vertices[b])));
		vertex.push_back(skybox_vertices[b]);

		normal.push_back(normalize(vec4to3(skybox_vertices[c])));
		vertex.push_back(skybox_vertices[c]);
	}

	void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
	{
		triangle(a, b, c);
		triangle(a, c, d);
	}

	void init_data()
	{
		quad(1, 5, 6, 2);
		quad(4, 0, 3, 7);
		quad(3, 2, 6, 7);
		quad(4, 5, 1, 0);
		quad(0, 1, 2, 3);
		quad(5, 4, 7, 6);
	}

	void init_VAO()
	{
		// Init the VAO for this object on the graphics card
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GL_CHECK_ERRORS
	}

	// Call this second at setup
	void init_VBO()
	{
		// Generate 2 buffers, one for the vertex, one for the normal
		glGenBuffers(2, buffers);

		// Initialize a buffer data object of all the vertex
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * vertex.size(), &(vertex[0]), GL_STATIC_DRAW);

		// Initialize a buffer data object of all the normal
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * normal.size(), &(normal[0]), GL_STATIC_DRAW);
		GL_CHECK_ERRORS
	}

	// Call this third at setup
	void init_shader()
	{
		program = InitShader("vshader72.glsl", "fshader72.glsl");
		GL_CHECK_ERRORS
			uniforms[0] = glGetUniformLocation(program, "ModelView");
		GL_CHECK_ERRORS
			uniforms[1] = glGetUniformLocation(program, "Projection");
		GL_CHECK_ERRORS
			uniforms[2] = glGetAttribLocation(program, "vPosition");
		GL_CHECK_ERRORS
			uniforms[3] = glGetAttribLocation(program, "Normal");

		glEnableVertexAttribArray(uniforms[2]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexAttribPointer(uniforms[2], 4, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 4, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(uniforms[3]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glVertexAttribPointer(uniforms[3], 4, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 4, BUFFER_OFFSET(0));

	}

	void init(){
		init_data();
		init_VAO();
		init_VBO();
		init_shader();
	}

	// Called from draw before drawing the object
	void start_shader()
	{
		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(this_texture);
		glBindVertexArray(vao);
		glUseProgram(program);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
	}

	// Called after draw to stop drawing the object
	void stop_shader()
	{
		glUseProgram(0);
		glBindVertexArray(0);
		GL_CHECK_ERRORS
	}

	void draw(GLfloat theta[])
	{
		start_shader();

		// ship down the new the projection and viewing matrices

		glUniformMatrix4fv(uniforms[0], 1, GL_TRUE, modelview * Scale(SKY_BOX_SCALE, SKY_BOX_SCALE, SKY_BOX_SCALE) * RotateZ(theta[2]) * RotateX(theta[0]) * RotateY(theta[1]));
		GL_CHECK_ERRORS

		glUniformMatrix4fv(uniforms[1], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

		glDrawArrays(GL_TRIANGLES, 0, vertex.size());
		GL_CHECK_ERRORS

			stop_shader();

	}

	void cleanup()
	{
		glDeleteProgram(program);
		glDeleteTextures(1, &tex);
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}


};



#endif