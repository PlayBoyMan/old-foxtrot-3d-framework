#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <GL\glew.h>

namespace framework {
	namespace graphics {

		/// Vertex class, abstracts all vertex data to be sent to the vertex buffer.
		class Vertex
		{
		public:
			/// Union, so that we can access vertex data in multiple ways.
			union {
				/// Data as contiguous float array
				float data[8];
				
				/// Struct holding separate arrays for position, normals, and uv.
				struct {

					/// Vertex position data
					float pos_data[3];
					/// Vertex normal data
					float normal_data[3];
					/// Vertex texture coordinate data
					float uv_data[2];
				};

				/// Struct holding separate float coordinates.
				struct {
					/// x, y, z, vertex position coorinates.
					float x, y, z;
					/// nx, ny, nz, vertex normal coordinates.
					float nx, ny, nz;
					/// u, v, vertex texture coordinates.
					float u, v;
				};
			};			
		};

		/// Mesh class, abstracts a basic vertex object.
		/**
		* Mesh class, abstracts a basic vertex object, 
		* i.e., a set of vertex data, bound to a 
		* VAO and a VBO. 
		*/
		class Mesh
		{
		private:
			bool element_render = false;

		public:

			/// Vector of vertex objects, holding vertex data.
			std::vector<Vertex> vertex_data;

			/// Indices that will be loaded to the EBO for indexed drawing.
			std::vector<GLuint> indices;

			/// Vertex Array Object (VAO) ID
			GLuint vertex_array_id;

			/// Vertex Buffer Object (VBO) ID
			GLuint vertex_buffer_id;

			/// Element Buffer Object (EBO) ID
			GLuint element_buffer_id;
			
			/// Default constructor, empty.
			Mesh();

			Mesh(const Mesh &m);

			/// Destructor, deletes all buffers.
			~Mesh();			

			/// Add a single vertex from a float array.
			void add_vertex(const float data[8]);
		
			/// Adds 'count' vertices from array data;
			void add_vertex(int count, const float *data);		

			/// Add vertex.
			void add_vertex(const Vertex &vert);

			/// Load vertex data to a VBO, and sets up vertex attributes to the VAO.
			void load();

			/// Binds the VAO and renders the mesh with the current shader program (it doesen't call glUseProgram.)
			void render();

			/// Deletes the buffer and clears data.
			void clear();

		};

		/// Print vertex on console
		void print_vertex(const Vertex &vert);

		/// Print mesh on console
		void print_mesh(const Mesh &mesh);

	}
}
#endif