/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
// Light system for Lumin Engine
// Supports single directional sunlight

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lumin/Core/Shaders/Shaders.h"

namespace Lumin {
namespace Shaders {
    class ShaderProgram;
}
namespace Renderer {

/**
 * @enum LightType
 * @brief Тип источника света.
 */
enum class LightType {
    Directional = 0 ///< Направленный свет (солнце)
};

/**
 * @class Light
 * @brief Класс источника света для Lumin Engine (только солнце).
 */
class Light {
public:
    Light();
    void SetLight(bool enabled);
    bool IsEnabled() const;
    void DrawDebug(Lumin::Shaders::ShaderProgram& shader) const;

    // Transform
    void SetPosition(const glm::vec3& pos) { position = pos; }
    void SetRotation(const glm::vec3& rot) { rotation = rot; UpdateDirectionFromRotation(); }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    void UpdateDirectionFromRotation();

    glm::vec3 direction; ///< Направление света (вычисляется из rotation для Directional)
    glm::vec3 color;     ///< Цвет света
    float intensity;     ///< Интенсивность
    bool enabled = true; ///< Включён ли свет
    LightType type = LightType::Directional; ///< Тип света
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f); // в градусах
};

/**
 * @brief Глобальный источник света (солнце).
 */
extern Light sunLight;

} // namespace Renderer
} // namespace Lumin 