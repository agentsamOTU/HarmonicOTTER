#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtc/type_ptr.hpp>
namespace syre
{
	class Transform
	{
	public:
		Transform();
		Transform(glm::vec3 pos, glm::quat rot, glm::vec3 sca);
		Transform(glm::vec3 pos);
		glm::mat4 GetModelMat();

		glm::vec3 globalPosition;
		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;
		

		Transform* parent = nullptr;

	};
}