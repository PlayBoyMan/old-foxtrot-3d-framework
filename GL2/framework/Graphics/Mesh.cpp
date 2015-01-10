#include "Mesh.h"

#include "../Math/vector.h"

namespace framework{

	namespace graphics {
		
		
		Mesh::Mesh()
		{
		}		

		Mesh::Mesh(const Mesh &m)
		{
			vertex_array_id = m.vertex_array_id;
			vertex_buffer_id = m.vertex_buffer_id;
			element_buffer_id = m.element_buffer_id;

			vertex_data = m.vertex_data;
			indices = m.indices;
		}

		Mesh::~Mesh()
		{
			clear();
		}


		void Mesh::add_vertex(const float data[8])
		{
			Vertex temp;

			memcpy((void *)&temp.data[0], &data[0], 8*sizeof(float));			
			vertex_data.push_back(temp);			
		}

		void Mesh::add_vertex(int count, const float *data)
		{
			for (int i = 0; i < count; i++)
				add_vertex(&data[i * 8]);
		}

		void Mesh::add_vertex(const Vertex &vert)
		{
			vertex_data.push_back(vert);
		}

		void Mesh::load()
		{			
			// Generate and bind VAO
			glGenVertexArrays(1, &vertex_array_id);
			glBindVertexArray(vertex_array_id);			

			// Generate and bind VBO
			glGenBuffers(1, &vertex_buffer_id);			

			// Load data to VBO
			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
			glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(Vertex), &vertex_data[0], GL_STATIC_DRAW);

			// If there are indices, upload them to EBO
			if (indices.size() > 0)
			{
				glGenBuffers(1, &element_buffer_id);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
				//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				element_render = true;
			}

			// Setup position (x, y, z) vertex attribute to the shader
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(0);

			// Setup normal (nx, ny, nz) vertex attribute to the shader
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
			glEnableVertexAttribArray(1);

			// Setup texture coords (u, v) vertex attribute to the shader
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 6));
			glEnableVertexAttribArray(2);

			// Unbind VBO and VAO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}

		void Mesh::render()
		{
			// Bind the VAO and call glDrawArrays. A shader program must be active.
			glBindVertexArray(vertex_array_id);					

			// If element render is enabled, use glDrawElements; else glDrawArrays
			if (element_render)
			{
				glDrawElements(GL_TRIANGLES, (GLuint) indices.size(), GL_UNSIGNED_INT, 0);				
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, (GLuint) vertex_data.size());				
			}

			glBindVertexArray(0);			

		}

		void Mesh::clear()
		{
			glDeleteBuffers(1, &vertex_buffer_id);
			glDeleteVertexArrays(1, &vertex_array_id);
			
			vertex_data.clear();
		}

		void print_vertex(const Vertex &vert)
		{
			vec::Vector<8> vec(vert.data);
			vec::print_vector(vec);
		}
		
		void print_mesh(const Mesh &mesh)
		{
			printf("\n VAO = %d, VBO = %d, size = %d, indices = %d \n", mesh.vertex_array_id, mesh.vertex_buffer_id, mesh.vertex_data.size(), mesh.indices.size());

			for (Vertex i : mesh.vertex_data)
				print_vertex(i);
		}

	}

}
