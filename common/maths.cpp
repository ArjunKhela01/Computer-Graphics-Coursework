#include "maths.hpp"
#include <glm/gtc/matrix_transform.hpp> // ads GML transformation function


glm::mat4 Maths::translate(const glm::vec3& v)
{
    return glm::translate(glm::mat4(1.0f), v); // moves object by vector (v)
}

//define scaling transformations
glm::mat4 Maths::scale(const glm::vec3& v)
{
    return glm::scale(glm::mat4(1.0f), v); // resies object based on scale 
}

//define rotation
glm::mat4 Maths::rotate(float angle, const glm::vec3& axis)
{
    return glm::rotate(glm::mat4(1.0f), angle, axis); // rotates object by an angle arround the given axis
}