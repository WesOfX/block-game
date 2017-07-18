#include "atlas.hpp"
#include "math.h"

atlas::atlas(
	const std::string& filename, 
	size_t rows, 
	size_t columns
):
	rows(rows),
	columns(columns)
{
	sf::Image image;
	image.loadFromFile(filename);
	GLsizei width = image.getSize().x / columns,
	        height = image.getSize().y / rows,
	        layers = rows * columns,
	        // mip_level = log2(std::min(width, height));
	        mip_level = 1;
	        
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexStorage3D(
		GL_TEXTURE_2D_ARRAY,
		mip_level,
		GL_RGBA8,
		width,
		height,
		layers
	);
	// TODO implement mipmapping 
	// see https://www.khronos.org/opengl/wiki/Array_Texture
	glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY,
		0, // mipmap level
		0, // x offset
		0, // y offset
		0, // layer
		width,
		height,
		layers,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image.getPixelsPtr()
	);
	
	glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_MIN_FILTER,
		GL_NEAREST
	);
	glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST
	);
	glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE
	);
	glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE
	);
}

uv_quad atlas::get_uv(const vec2<size_t>& position) const{
	return {
		{
			{
				0.0f,
				1.0f,
				0.0f
			},
			{
				1.0f,
				1.0f,
				0.0f
			},
			{
				1.0f,
				0.0f,
				0.0f
			},
			{
				0.0f,
				0.0f,
				0.0f
			}
		}
	};
}

void atlas::bind() const{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}
