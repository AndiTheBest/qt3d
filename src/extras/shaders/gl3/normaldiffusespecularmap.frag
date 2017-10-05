#version 150 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec4 worldTangent;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec4 ka;            // Ambient reflectivity
uniform float shininess;    // Specular shininess factor
uniform vec3 eyePosition;

#pragma include phong.inc.frag
#pragma include coordinatesystems.inc

void main()
{
    // Sample the textures at the interpolated texCoords
    vec4 diffuseTextureColor = texture( diffuseTexture, texCoord );
    vec4 specularTextureColor = texture( specularTexture, texCoord );
    vec3 tNormal = 2.0 * texture( normalTexture, texCoord ).rgb - vec3( 1.0 );

    mat3 tangentMatrix = calcWorldSpaceToTangentSpaceMatrix(worldNormal, worldTangent);
    mat3 invertTangentMatrix = transpose(tangentMatrix);

    vec3 wNormal = normalize(invertTangentMatrix * tNormal);

    vec3 worldView = normalize(eyePosition - worldPosition);
    fragColor = phongFunction(ka, diffuseTextureColor, specularTextureColor, shininess, worldPosition, worldView, wNormal);
}
