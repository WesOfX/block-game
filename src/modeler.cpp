#include "modeler.hpp"

model modeler::generate_chunk_model(
	const chunk& c,
	const std::optional<chunk>& north_chunk,
	const std::optional<chunk>& east_chunk,
	const std::optional<chunk>& south_chunk,
	const std::optional<chunk>& west_chunk
) const{
	model m;
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = 0; layer < chunk::layers; ++layer){
				// check surrounding blocks
				if(c.blocks[row][column][layer].visible()){
					const auto id = c.blocks[row][column][layer].id;
					const chunk::block_position_type position{row, column, layer};
					quad q;
					if(
						layer == 0 
					 || c.blocks[row][column][layer - 1].transparent()
					){
						q = generate_block_face(id, position, bottom);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						layer == chunk::layers - 1 
					 || c.blocks[row][column][layer + 1].transparent()
					){
						q = generate_block_face(id, position, top);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							column == 0  
						 && west_chunk 
						 && west_chunk->blocks[row][chunk::columns - 1][layer].transparent()
					 	)
					 || (
					 		column > 0 
					 	 && c.blocks[row][column - 1][layer].transparent()
					 	)
					){
						q = generate_block_face(id, position, left);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							column == chunk::columns - 1
						 && east_chunk 
						 && east_chunk->blocks[row][0][layer].transparent()
					 	)
					 || (
					 		column < chunk::columns - 1 
					 	 && c.blocks[row][column + 1][layer].transparent()
					 	)
					){
						q = generate_block_face(id, position, right);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							row == 0 
						 && north_chunk 
						 && north_chunk->blocks[chunk::rows - 1][column][layer].transparent()
					 	)
					 || (
					 		row > 0 
					 	 && c.blocks[row - 1][column][layer].transparent()
					 	)
					){
						q = generate_block_face(id, position, back);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							row == chunk::rows - 1
						 && south_chunk 
						 && south_chunk->blocks[0][column][layer].transparent()
					 	)
					 || (
					 		row < chunk::rows - 1 
					 	 && c.blocks[row + 1][column][layer].transparent()
					 	)
					){
						q = generate_block_face(id, position, front);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
				}
			}
		}
	}
	return m;
}

quad modeler::generate_block_face(
	block::id_type id,
	const chunk::block_position_type& position, 
	block_face face
) const{
	quad q;
	switch(face){
	case top:
		q[0].position = {0.0f, 1.0f, 1.0f};
		q[1].position = {1.0f, 1.0f, 1.0f};		
		q[2].position = {1.0f, 1.0f, 0.0f};
		q[3].position = {0.0f, 1.0f, 0.0f};
		for(auto& i: q) i.color = {1.0f, 1.0f, 1.0f};
		break;
	case bottom:
		q[0].position = {0.0f, 0.0f, 0.0f};
		q[1].position = {1.0f, 0.0f, 0.0f};		
		q[2].position = {1.0f, 0.0f, 1.0f};
		q[3].position = {0.0f, 0.0f, 1.0f};
		for(auto& i: q) i.color = {0.5f, 0.5f, 0.5f};
		break;
	case front:
		q[0].position = {0.0f, 0.0f, 1.0f};
		q[1].position = {1.0f, 0.0f, 1.0f};		
		q[2].position = {1.0f, 1.0f, 1.0f};
		q[3].position = {0.0f, 1.0f, 1.0f};
		for(auto& i: q) i.color = {0.83f, 0.83f, 0.83f};
		break;
	case back:
		q[0].position = {1.0f, 0.0f, 0.0f};
		q[1].position = {0.0f, 0.0f, 0.0f};		
		q[2].position = {0.0f, 1.0f, 0.0f};
		q[3].position = {1.0f, 1.0f, 0.0f};
		for(auto& i: q) i.color = {0.83f, 0.83f, 0.83f};
		break;
	case left:
		q[0].position = {0.0f, 0.0f, 0.0f};
		q[1].position = {0.0f, 0.0f, 1.0f};		
		q[2].position = {0.0f, 1.0f, 1.0f};
		q[3].position = {0.0f, 1.0f, 0.0f};
		for(auto& i: q) i.color = {0.66f, 0.66f, 0.66f};
		break;
	case right:
		q[0].position = {1.0f, 0.0f, 1.0f};
		q[1].position = {1.0f, 0.0f, 0.0f};		
		q[2].position = {1.0f, 1.0f, 0.0f};
		q[3].position = {1.0f, 1.0f, 1.0f};
		for(auto& i: q) i.color = {0.66f, 0.66f, 0.66f};
		break;
	}
	typedef decltype(decltype(q)::value_type::position) position_type;
	typedef position_type::coordinate_type coordinate_type;
	for(auto& i: q) i.position += position_type{
		(coordinate_type)position.y, // column
		(coordinate_type)position.z, // layer
		(coordinate_type)position.x  // row
	};
	for(auto& i: q) i.uv = {0.0f, 0.0f};
	return q;
}
