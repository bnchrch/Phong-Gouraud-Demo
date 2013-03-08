#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;

in vec3 vertex;
in vec4 color;
in vec3 normal;
in vec4 texcoord0;

out vec4 vColor;

void main()
{
	vec4 position = modelMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * viewMatrix * position;
	
	vColor = color;
}