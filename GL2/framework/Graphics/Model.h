#ifndef __MODEL_H__
#define __MODEL_H__

#pragma once

#include "Mesh.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

using namespace framework::graphics;
using namespace std;

namespace framework {
	namespace graphics {

		class Model
		{
		public:

			vector<Mesh> meshes;

			Model();
			~Model();

			void load_model(const string &fname);
			void render();
			void clear();
			void print_model();
			
		private:

			void process_scene(aiNode *node, const aiScene *scene);
			Mesh process_mesh(aiMesh *mesh);

		};
	}
}

#endif
