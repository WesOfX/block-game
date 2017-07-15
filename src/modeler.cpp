#include "modeler.hpp"

model modeler::generate_chunk_model(const chunk& c) const{
	model m;
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = 0; layer < chunk::layers; ++layer){
				// check surrounding blocks
				if(c.blocks[row][column][layer].visible()){
					const auto id = c.blocks[row][column][layer].id;
					const chunk::block_position_type position{row, column, layer};
					rect r;
					if(
						layer == 0 
					 || c.blocks[row][column][layer - 1].transparent()
					){
						r = generate_block_face(id, position, bottom);
						m.insert(m.end(), r.begin(), r.end());
					}
					if(
						layer == chunk::layers - 1 
					 || c.blocks[row][column][layer + 1].transparent()
					){
						r = generate_block_face(id, position, top);
						m.insert(m.end(), r.begin(), r.end());
					}
					if(
						column == 0 
					 || c.blocks[row][column - 1][layer].transparent()
					){
						r = generate_block_face(id, position, left);
						m.insert(m.end(), r.begin(), r.end());
					}
					if(
						column == chunk::columns - 1
					 || c.blocks[row][column + 1][layer].transparent()
					){
						r = generate_block_face(id, position, right);
						m.insert(m.end(), r.begin(), r.end());
					}
					if(
						row == 0 
					 || c.blocks[row - 1][column][layer].transparent()
					){
						r = generate_block_face(id, position, front);
						m.insert(m.end(), r.begin(), r.end());
					}
					if(
						row == chunk::rows - 1
					 || c.blocks[row + 1][column][layer].transparent()
					){
						r = generate_block_face(id, position, back);
						m.insert(m.end(), r.begin(), r.end());
					}
				}
			}
		}
	}
	return m;
}

rect modeler::generate_block_face(
	block::id_type id,
	const chunk::block_position_type& position, 
	block_face face
) const{
	rect r;
	switch(face){
	case top:
		r[0].position = {0.0f, 1.0f, 1.0f};
		r[1].position = {1.0f, 1.0f, 1.0f};		
		r[2].position = {1.0f, 1.0f, 0.0f};
		r[3].position = {0.0f, 1.0f, 0.0f};
		break;
	case bottom:
		r[0].position = {0.0f, 1.0f, 0.0f};
		r[1].position = {1.0f, 1.0f, 0.0f};		
		r[2].position = {1.0f, 1.0f, 1.0f};
		r[3].position = {0.0f, 1.0f, 1.0f};
		break;
	case front:
		r[0].position = {0.0f, 0.0f, 1.0f};
		r[1].position = {1.0f, 0.0f, 1.0f};		
		r[2].position = {1.0f, 1.0f, 1.0f};
		r[3].position = {0.0f, 1.0f, 1.0f};
		break;
	case back:
		r[0].position = {1.0f, 0.0f, 0.0f};
		r[1].position = {0.0f, 0.0f, 0.0f};		
		r[2].position = {0.0f, 1.0f, 0.0f};
		r[3].position = {1.0f, 1.0f, 0.0f};
		break;
	case left:
		r[0].position = {0.0f, 0.0f, 0.0f};
		r[1].position = {0.0f, 0.0f, 1.0f};		
		r[2].position = {0.0f, 1.0f, 1.0f};
		r[3].position = {0.0f, 1.0f, 0.0f};
		break;
	case right:
		r[0].position = {1.0f, 0.0f, 1.0f};
		r[1].position = {1.0f, 0.0f, 0.0f};		
		r[2].position = {1.0f, 1.0f, 0.0f};
		r[3].position = {1.0f, 1.0f, 1.0f};
		break;
	}
	typedef decltype(decltype(r)::value_type::position) position_type;
	typedef position_type::coordinate_type coordinate_type;
	r[0].position += position_type{
		(coordinate_type)position.x,
		(coordinate_type)position.y,
		(coordinate_type)position.z
	};
	r[0].color = {1.0f, 1.0f, 1.0f};
	r[0].uv = {0.0f, 0.0f};
	return r;
}

void bind(const model& m){

}
