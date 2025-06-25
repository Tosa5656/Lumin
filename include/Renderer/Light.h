// Light system for Lumin Engine
// Supports multiple directional lights

#pragma once
#include <glm/glm.hpp>
#include "Shaders/Shaders.h"

constexpr int MAX_LIGHTS = 4;

enum class LightType {
    Directional = 0
    // Point, Spot — soon
};

struct LightData {
    LightType type;
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    bool enabled;
};

class Light {
public:
    Light();
    void SetLight(bool enabled);
    bool IsEnabled() const;
    void DrawDebug(ShaderProgram& shader) const;

    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    bool enabled = true;
    LightType type = LightType::Directional;
};

extern Light lights[MAX_LIGHTS];
void InitDefaultLights(); 