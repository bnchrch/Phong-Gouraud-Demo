#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;
uniform vec3 lightPos;
uniform vec4 lightCol;
uniform mat3 normalMatrix;

in vec3 vertex;
in vec4 color;
in vec3 normal;
in vec4 texcoord0;

out vec4 vColor;



void main()
{

//variables
vec3 N;
vec3 vecLight;
vec3 vecEye;
vec3 vecRef;

vec4 diffuse;
vec4 spec;
vec4 ambient;

//specular color
vec4 specular = vec4(1,1,1,1);

        //calc position
        vec4 position = modelMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * viewMatrix * position;

        N = normalize(normalMatrix*normal); //create normal vector

        vecLight = normalize(lightPos - position.xyz); //lightpostiion vector
        vecEye = normalize(-vertex); //eye position vector
        vecRef = normalize(reflect(vecLight,N)); //reflection vector


        //calc ambient, diffuse and spec colors and add them all up
        ambient = color * 0.4;
        diffuse = max(color*max(dot(N,vecLight),0.0),0.0);
        spec = max(lightCol* pow(max(dot(vecRef,vecEye),0.0),10.0),0.0);//R,E

        vColor = diffuse+spec+ambient;

}

