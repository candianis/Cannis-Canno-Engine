#pragma once

#include "ccpch.h"
#include "Component.h"
#include "Renderer/Model/Model.h"

namespace Cannis {
	struct ModelComponent {
		ModelComponent() : modelMatrix(1) {}

		ModelComponent(const std::string& p_path) : modelMatrix(glm::mat4(1)) {
			model = Model::Create(p_path);
		}

		glm::mat4 modelMatrix;
		std::shared_ptr<Model> model;
	};
}