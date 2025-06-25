// Implementation of Light system for Lumin Engine

#include "Renderer/Light.h"
#include "Renderer/Renderer.h"

Light lights[MAX_LIGHTS];

void InitDefaultLights() {
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        lights[i] = Light();
        lights[i].enabled = true;
    }
    lights[0].enabled = true;
    lights[0].direction = glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f));
    lights[0].color = glm::vec3(1.0f);
    lights[0].intensity = 1.0f;
    lights[0].type = LightType::Directional;
}

Light::Light()
    : direction(glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f))), color(glm::vec3(1.0f)), intensity(1.0f), enabled(true), type(LightType::Directional) {}

void Light::SetLight(bool en) {
    enabled = en;
}

bool Light::IsEnabled() const {
    return enabled;
}

void Light::DrawDebug(ShaderProgram& shader) const {
    glm::vec3 lightPos = -direction * 2.0f;
    DrawPoint(lightPos, color, shader);
    DrawLine(lightPos, glm::vec3(0.0f), color, shader);
} 