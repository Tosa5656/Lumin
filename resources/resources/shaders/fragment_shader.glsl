// Fragment shader for Lumin Engine. Handles single directional sunlight and texture mapping.
#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 materialColor;

struct Light {
    vec3 direction;
    vec3 color;
    float intensity;
    bool enabled;
};
uniform Light sunLight;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lighting = vec3(0.0);
    if (sunLight.enabled) {
        float diff = max(dot(normal, -sunLight.direction), 0.0);
        lighting += sunLight.color * sunLight.intensity * diff;
    }
    vec3 baseColor;
    if (useTexture) {
        baseColor = materialColor * texture(texture1, TexCoord).rgb;
    } else {
        baseColor = materialColor;
    }
    FragColor = vec4(baseColor * lighting, 1.0);
}