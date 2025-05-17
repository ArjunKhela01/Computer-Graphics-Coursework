#pragma once

#include <glm/glm.hpp>

class Maths
{
public:
    static glm::mat4 translate(const glm::vec3& v);
    static glm::mat4 scale(const glm::vec3& v);
    static glm::mat4 rotate(float angle, const glm::vec3& axis);
};