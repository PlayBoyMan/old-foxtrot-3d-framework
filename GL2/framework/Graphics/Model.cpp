#include "Model.h"


#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Mesh.h"

using namespace framework::graphics;
using namespace std;


Model::Model()
{
}


Model::~Model()
{
	clear();
}

void Model::render()
{
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].render();
}

void Model::clear()
{
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].clear();
	meshes.clear();
}

void Model::print_model()
{	
	printf("MODEL> %d meshes: \n", meshes.size());
	for (int i = 0; i < meshes.size(); i++)
		print_mesh(meshes[i]);
}

void Model::load_model(const string &file_name)
{
	Assimp::Importer importer;
	
	const aiScene *scene = importer.ReadFile(file_name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "Error loading model " << file_name << ": " << importer.GetErrorString() << endl;
		return;
	}

	process_scene(scene->mRootNode, scene);

	for (int i = 0; i < meshes.size(); i++)
		meshes[i].load();
}

void Model::process_scene(aiNode *node, const aiScene *scene)
{
	for (GLuint i = 0; i < (node->mNumMeshes); i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(process_mesh(mesh));		
	}

	for (GLuint i = 0; i < (node->mNumChildren); i++)
		process_scene(node->mChildren[i], scene);
}

Mesh Model::process_mesh(aiMesh *mesh)
{

	Mesh temp;

	for (GLuint i = 0; i < (mesh->mNumVertices); i++)
	{
		Vertex vert;

		vert.x = mesh->mVertices[i].x;
		vert.y = mesh->mVertices[i].y;
		vert.z = mesh->mVertices[i].z;

		vert.nx = mesh->mNormals[i].x;
		vert.ny = mesh->mNormals[i].y;
		vert.nz = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			vert.u = mesh->mTextureCoords[0][i].x;
			vert.v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vert.u = 0.0f;
			vert.v = 0.0f;
		}

		temp.add_vertex(vert);

	}
	

	for (GLuint i = 0; i < (mesh->mNumFaces); i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			temp.indices.push_back(face.mIndices[j]);
	}


	return temp;
}
