/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lumin/Core/Shaders/Shaders.h"

namespace Lumin {
namespace Shaders {
    class ShaderProgram;
}
namespace Renderer {
enum class LightType {
    Directional = 0 
};
class Light {
public:
    Light();
    void SetLight(bool enabled);
    bool IsEnabled() const;
    void DrawDebug(Lumin::Shaders::ShaderProgram& shader) const;

    void SetPosition(const glm::vec3& pos) { position = pos; }
    void SetRotation(const glm::vec3& rot) { rotation = rot; UpdateDirectionFromRotation(); }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    void UpdateDirectionFromRotation();

    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    bool enabled = true;
    LightType type = LightType::Directional;
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
};

extern Light sunLight;

}
}