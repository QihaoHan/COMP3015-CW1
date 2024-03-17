#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexcoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model * vec4(VertexPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * VertexNormal;  
	TextureCoord = VertexTexcoord;
	gl_Position = projection * view * model * vec4(VertexPosition, 1.0f);
}
