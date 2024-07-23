#pragma once

#include "../../../Mesh/Mesh.h"

#include <memory>

struct MeshComponent {
	std::shared_ptr<Cannis::Mesh> m_mesh;
};

