#pragma once

#include "model.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace ef
{

struct TransformComponent
{
	glm::vec3 translation{};
	glm::vec3 scale{ 1.f, 1.f, 1.f };
	glm::vec3 rotation;
	glm::mat3 normalMatrix();
	// matrix correspond to translate * Ry * Rx * Rz * scale transformation
	// Roptation convention uses trait-brian
	glm::mat4 mat4();
};

class GameObject
{
public:
	using id_t = unsigned int;

	static GameObject createGameObject() {
		static id_t currentId = 0;
		return GameObject{ currentId++ };
	}


	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	id_t getId() const { return id; }

	std::shared_ptr<Model> model{};
	glm::vec3 color{};

	TransformComponent transform{};

private:
	GameObject(id_t objId) :id{ objId } {}
	id_t id;

};
}
