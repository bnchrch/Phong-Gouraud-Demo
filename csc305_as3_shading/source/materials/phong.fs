#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;
uniform vec3 lightPos;
uniform vec4 lightCol;
uniform mat3 normalMatrix;


in vec4 vColor;
in vec4 texcoord0;

in vec3 N;
in vec4 position;
in vec4 normal;
in vec3 newVertex;

out vec4 fColor;

void main()
{

//variables
vec3 vecLight;
vec3 vecEye;
vec3 vecRef;
vec4 diffuse;
vec4 spec;
vec4 ambient;

    vecLight = normalize(lightPos - position.xyz); //lightpos vector
    vecEye = normalize(-newVertex);              //eye vector
    vecRef = normalize(reflect(vecLight,N));            //reflect vector

        //here we calculate the ambient light, diffusion light and specular light and add it all together
        ambient = vColor * 0.4;
        diffuse = max(vColor*max(dot(N,vecLight),0.0),0.0);
        spec = max(lightCol* pow(max(dot(vecRef,vecEye),0.0),10.0),0.0);

        fColor = diffuse+spec+ambient;

}


