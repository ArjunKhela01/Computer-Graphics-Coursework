#pragma once //  prevents mutliple inclusions 

#include <glm/glm.hpp>

class Maths
{
public:
    static glm::mat4 translate(const glm::vec3& v); // allows object to move
    static glm::mat4 scale(const glm::vec3& v); //resize object
    static glm::mat4 rotate(float angle, const glm::vec3& axis); // rotate object
};