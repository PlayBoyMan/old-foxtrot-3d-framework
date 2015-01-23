#include <string>

#pragma once

using namespace std;

namespace framework {
	namespace graphics {

		class Texture
		{
		public:

			GLuint texture_id;
			string type;
			string filename;

		};

		Texture load_texture(string filename);

	}
};