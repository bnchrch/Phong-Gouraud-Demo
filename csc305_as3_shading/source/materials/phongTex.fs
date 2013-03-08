#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int usePostMultiply;
uniform vec3 lightPos;
uniform vec4 lightCol;
uniform mat3 normalMatrix;
uniform sampler2D colormap;
uniform sampler2D bumpmap;

in vec4 vColor;
in vec3 N;
in vec4 position;
in vec4 normal;
in vec3 newVertex;
in vec2 newTex;

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


    vec4 texture0 = texture(colormap, newTex.st); //add texture to colormap


    vecLight = normalize(lightPos - position.xyz); //lightpos vector
    vecEye = normalize(-newVertex);              //eye vector
    vecRef = normalize(reflect(vecLight,N));            //reflect vector

        //here we calculate the ambient light, diffusion light and specular light and add it all together
        ambient = texture0 * 0.4;
        diffuse = max(texture0*max(dot(N,vecLight),0.0),0.0);
        spec = max(lightCol* pow(max(dot(vecRef,vecEye),0.0),10.0),0.0);

        fColor = diffuse+spec+ambient;

}


