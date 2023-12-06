#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

//bool Mesh::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
//{
//	// check cast ray with mesh triangles 
//	for (<i = 0, while less than number of vertices and increment by 3 each iteration>)
//	{
//		Triangle triangle(< set the three vertices for the triangle(m_vertices[i], [i + 1], [i + 2] > , m_material);
//		if (triangle.Hit(ray, minDistance, maxDistance, raycastHit))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool Mesh::Load(const std::string& filename, const glm::vec3& translate, const glm::vec3& rotation, const glm::vec3& scale)
//{
//	Assimp::Importer importer;
//
//	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		std::cerr << "Could not load assimp file " << filename << " error string: " << importer.GetErrorString();
//		return false;
//	}
//
//	// create transform matrix
//	glm::mat4 mt = glm::translate(translate);
//	glm::mat4 mr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
//	glm::mat4 ms = glm::scale(scale);
//
//	glm::mat4 mx = mt * mr * ms;
//
//	// process the nodes starting at the root
//	ProcessNode(scene->mRootNode, scene, mx);
//
//	return true;
//}
//
//void Mesh::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform)
//{
//	// process the current node meshes
//	for (unsigned int i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		ProcessMesh(mesh, scene, transform);
//	}
//	// process the current node children
//	for (unsigned int i = 0; i < node->mNumChildren; i++)
//	{
//		ProcessNode(node->mChildren[i], scene, transform);
//	}
//}
//
//void Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform)
//{
//	std::vector<glm::vec3> positions;
//
//	// get mesh vertex positions
//	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//	{
//		glm::vec3 position = transform * glm::vec4{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1 };
//		<add position to positions vector>
//	}
//
//	// get mesh index vertices
//	for (size_t i = 0; i < mesh->mNumFaces; i++)
//	{
//		// get mesh face, face holds three indices (triangle) into the positions of the mesh
//		aiFace face = mesh->mFaces[i];
//		for (size_t j = 0; j < face.mNumIndices; j++)
//		{
//			// add positions to vertices vector, face contains index into positions of the triangle
//			unsigned int index = face.mIndices[j];
//			<add position at index to m_vertices>
//		}
//	}
//}
