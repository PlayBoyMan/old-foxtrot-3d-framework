#version 430 core

in vec3 fs_color;
in vec2 texture_coordinate;

out vec4 color;

uniform sampler2D mesh_texture;

void main () 
{	
	//color  = vec4(fs_color, 1.0f);
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	color = texture(mesh_texture, texture_coordinate);
}
