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
	        // mip_level = log2(height); // width?
	        mip_level = 1;
	        
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexStorage3D(
		GL_TEXTURE_2D_ARRAY,
		mip_level,
		GL_RGBA8,
		width,
		height,
		layers
	);

	/*glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR
	);*/
	
	glTexParameteri(
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR
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
	
	// glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	
	// TODO implement mipmapping 
	// see https://www.khronos.org/opengl/wiki/Array_Texture
	// auto pixels = ;
	glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY,
		0, // mipmap level
		0,
		0,
		0,
		width,
		height,
		layers,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image.getPixelsPtr()
	);
	/*glTexImage3D(
		GL_TEXTURE_2D_ARRAY,
		0, // mipmap level
		GL_RGBA8,
		width,
		height,
		layers,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image.getPixelsPtr()
	);*/
	/*for(auto i = 0; i < mip_level; ++i){
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0, // mipmap level
			0,
			0,
			i,
			width,
			height,
			1,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr()
		);
		glTexImage3D(
			GL_TEXTURE_2D_ARRAY,
			i, // mipmap level
			GL_RGBA8,
			width / pow(2, i),
			height / pow(2, i),
			layers,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr()
		);
	}*/
}

uv_quad atlas::get_uv(const vec2<size_t>& position) const{
	// note inverted y axis
	return {
		{
			{
				0.0f,
				1.0f,
				1.0f * position.x
			},
			{
				1.0f,
				1.0f,
				1.0f * position.x
			},
			{
				1.0f,
				0.0f,
				1.0f * position.x
			},
			{
				0.0f,
				0.0f,
				1.0f * position.x
			}
		}
	};
}

void atlas::bind() const{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}
