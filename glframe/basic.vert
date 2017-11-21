#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;

uniform mat4 model_matrix;

out vec3 Color;

void main()
{
    Color = VertexColor;

    gl_Position = model_matrix *vec4(VertexPosition,1.0);
}
