#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 tex_coords;

uniform mat4 transform_matrix;

out vec3 fs_color;
out vec2 texture_coordinate;

void main ()
{	
	const vec3 triangle[3] = vec3[3](vec3(-1.0, -1.0, 0.0),
								 vec3(0.0, 1.0, 0.0),
								 vec3(1.0, -1.0, 0.0));
								 
	//gl_Position.xyz = triangle[gl_VertexID];
	

	gl_Position = transform_matrix * vec4(position, 1.0f);
	
	fs_color = normals;

	texture_coordinate = tex_coords;
}
