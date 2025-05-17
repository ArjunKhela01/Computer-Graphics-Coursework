#include "maths.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Maths::translate(const glm::vec3& v)
{
    return glm::translate(glm::mat4(1.0f), v);
}

glm::mat4 Maths::scale(const glm::vec3& v)
{
    return glm::scale(glm::mat4(1.0f), v);
}

glm::mat4 Maths::rotate(float angle, const glm::vec3& axis)
{
    return glm::rotate(glm::mat4(1.0f), angle, axis);
}