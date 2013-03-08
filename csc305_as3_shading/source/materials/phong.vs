#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;
uniform mat3 normalMatrix;


in vec3 vertex;
in vec4 color;
in vec3 normal;



out vec4 position;
out vec3 N;
out vec3 newVertex;
out vec4 vColor;


void main()
{
position = modelMatrix * vec4(vertex, 1.0);
gl_Position = projectionMatrix * viewMatrix * position; //calculate position, given
N = normalize(normalMatrix*normal); //create normal vector and pass

//forwarding vertex, color and texture coordinates to the fragment shader
newVertex = vertex;
vColor = color;

}



