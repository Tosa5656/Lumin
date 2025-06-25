// Fragment shader for Lumin Engine. Handles multiple directional lights and diffuse lighting.
#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;
#define MAX_LIGHTS 4

struct Light {
    vec3 direction;
    vec3 color;
    float intensity;
    bool enabled;
};
uniform Light lights[MAX_LIGHTS];

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lighting = vec3(0.0);
    int dummy = 0;
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        if (lights[i].enabled) {
            float diff = max(dot(normal, -lights[i].direction), 0.0);
            lighting += lights[i].color * lights[i].intensity * diff;
        }
        dummy += lights[i].enabled ? 1 : 0;
    }
    FragColor = vec4(lighting, 1.0);
}