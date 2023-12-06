#pragma once
#include "Object.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

struct aiNode;
struct aiMesh;
struct aiScene;

class Mesh : public Object
{
public:
	Mesh() = default;
	Mesh(std::shared_ptr<Material> material) :
		Object{ material }
	{
	}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;
	bool Load(const std::string& filename, const glm::vec3& translate = glm::vec3(0), const glm::vec3& rotation = glm::vec3(0), const glm::vec3& scale = glm::vec3(1));

private:
	void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);

private:
	std::vector<glm::vec3> m_vertices;
};
