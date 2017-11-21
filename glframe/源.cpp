#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include "vmath.h"
#include "mat.h"
#include "LoadShaders.h"
#include "Teapot.h"

#pragma comment (lib,"glew32.lib")

using namespace std;
//using namespace vmath;

GLuint  PLoc;  // Projection matrix
GLuint  InnerLoc;  // Inner tessellation paramter
GLuint  OuterLoc;  // Outer tessellation paramter

GLfloat  Inner = 1.0;
GLfloat  Outer = 1.0;

float aspect;
GLuint render_prog;
GLuint vao[1], vaoID;
GLuint vbo[1];
GLuint ebo[1];

GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;

//----------------------------------------------------------------------------

//void init(void)
//{
//	static ShaderInfo shader_info[] =
//    {
//        { GL_VERTEX_SHADER, "primitive_restart.vs.glsl" },
//        { GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl" },
//        { GL_NONE, NULL }
//    };
//
//    render_prog = LoadShaders(shader_info);
//
//   /* glUseProgram(render_prog);*/
//
//    // "model_matrix" is actually an array of 4 matrices
//    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
//    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");
//
//    // 8 corners of a cube, side length 2, centered on the origin
//    static const GLfloat cube_positions[] =
//    {
//        -1.0f, -1.0f, -1.0f, 1.0f,
//        -1.0f, -1.0f,  1.0f, 1.0f,
//        -1.0f,  1.0f, -1.0f, 1.0f,
//    };
//
//    // Color for each vertex
//    static const GLfloat cube_colors[] =
//    {
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 0.0f, 1.0f, 1.0f,
//    };
//
//    // Indices for the triangle strips
//    static const GLushort cube_indices[] =
//    {
//        0, 1, 2, 3, 6, 7, 4, 5,         // First strip
//        0xFFFF,                         // <<-- This is the restart index
//        2, 6, 0, 4, 1, 5, 3, 7          // Second strip
//    };
//
//    // Set up the element array buffer
//    /*glGenBuffers(1, ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);*/
//
//    // Set up the vertex attributes
//    glGenVertexArrays(1, vao);
//    glBindVertexArray(vao[0]);
//
//    glGenBuffers(1, vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);
//
//    
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions));
//
//	glClearColor(0.0, 0.0, 1.0, 1.0);
//	
//	float t = float(GetTickCount() & 0x1FFF) / float(0x1FFF);
//    static float q = 0.0f;
//    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
//    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
//    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);
//
//    // Setup
//    //glEnable(GL_CULL_FACE);
//    //glDisable(GL_DEPTH_TEST);
//
//    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Activate simple shading program
//    //glUseProgram(render_prog);
//
//    // Set up the model and projection matrix
//	//vmath::mat4 model_matrix(vmath::translate(0.0f, 0.0f, -5.0f) * vmath::rotate(t * 360.0f, Y) * vmath::rotate(t * 720.0f, Z));
//	vmath::mat4 model_matrix(vmath::translate(0.0f, 0.0f, -5.0f) );
//    //vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
//	mat4 projection_matrix(Ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f));
//
//    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
//    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
//
//    // Set up for a glDrawElements call
//    /*glBindVertexArray(vao[0]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);*/
//
//    
//
//}
void init(void)
{
	static ShaderInfo shader_info[] =
	{
		{ GL_VERTEX_SHADER, "basic.vert" },
		{ GL_FRAGMENT_SHADER, "basic.frag" },
		{ GL_NONE, NULL }
	};

	render_prog = LoadShaders(shader_info);

	 glUseProgram(render_prog);
	 render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");

	 float positionData[] = {
		 -0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f ,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f
	 };

	 float colorData[] = {
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, 
		  1.0f, 1.0f, 0.0f,
		 1.0f, 0.0f, 1.0f
	 };



	 // Create and set-up the vertex array object
	 glGenVertexArrays(1, &vaoID);
	 glBindVertexArray(vaoID);


	 // Create and populate the buffer objects
	 GLuint vboHandles[2];
	 glGenBuffers(2, vboHandles);
	 GLuint positionBufferHandle = vboHandles[0];
	 GLuint colorBufferHandle = vboHandles[1];

	 glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	 glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), positionData, GL_STATIC_DRAW);

	 glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	 glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), colorData, GL_STATIC_DRAW);


	 glEnableVertexAttribArray(0);  // Vertex position
	 glEnableVertexAttribArray(1);  // Vertex color

	 glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	 glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);


	glClearColor(0.0, 0.0, 1.0, 1.0);

	mat4 projection_matrix(Ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f));
	static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
	mat4 model_matrix(Translate(0.0f, 0.0f, -5.0f) *RotateY(30.0f));

	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);

}
//----------------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoID);

	glDrawArrays(GL_TRIANGLES,0,6);

	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	GLfloat  aspect = GLfloat(width) / height;

	//mat4  projection = Perspective(60.0, aspect, 5, 10);
	////     mat4  projection = Frustum( -3, 3, -3, 3, 5, 10 );
	//glUniformMatrix4fv(PLoc, 1, GL_TRUE, projection);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	/*glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);*/
	glutCreateWindow("teapot");

	bool glewExperimental = true;
	glewInit();
	glGetError();

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	/*glutKeyboardFunc(keyboard);*/

	glutMainLoop();
	return 0;
}
