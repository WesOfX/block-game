#include "modeler.hpp"

modeler::modeler():
	block_atlas("textures/blocks.png", 16, 1)
{
	/*block_atlas.rows = 16;
	block_atlas.columns = 16;
	block_atlas.texture.loadFromFile("textures/blocks.png");
	block_atlas.texture.setSmooth(false);
	block_atlas.texture.setRepeated(false);
	*/
	//block_atlas.texture.generateMipmap();
}

model modeler::generate_chunk_model(
	const chunk3x3& chunks,
	const chunk::position_type& position
) const{
	model m;
	auto& c = chunks[1][1].value().get();
	/*auto& west_chunk = chunks[1][0].value().get();
	auto& east_chunk = chunks[1][2].value().get();
	auto& north_chunk = chunks[0][1].value().get();
	auto& south_chunk = chunks[2][1].value().get();*/
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = 0; layer < chunk::layers; ++layer){
				// check surrounding blocks
				if(c.get({row, column, layer}).visible()){
					const auto& block = c.get({row, column, layer});
					const chunk::block_position_type block_position{row, column, layer};
					quad q;
					if(
						layer == 0 
					 || c.get({row, column, layer - 1}).opacity() < 15
					){
						q = generate_block_face(block, c, block_position, bottom, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						layer == chunk::layers - 1 
					 || c.get({row, column, layer + 1}).opacity() < 15
					){
						q = generate_block_face(block, c, block_position, top, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							column == 0  
						 && chunks[1][0] 
						 && chunks[1][0].value().get().get({row, chunk::columns - 1, layer}).opacity() < 15
					 	)
					 || (
					 		column > 0 
					 	 && c.get({row, column - 1, layer}).opacity() < 15
					 	)
					){
						q = generate_block_face(block, c, block_position, left, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							column == chunk::columns - 1
						 && chunks[1][2]
						 && chunks[1][2].value().get().get({row, 0, layer}).opacity() < 15
					 	)
					 || (
					 		column < chunk::columns - 1 
					 	 && c.get({row, column + 1, layer}).opacity() < 15
					 	)
					){
						q = generate_block_face(block, c, block_position, right, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							row == 0 
						 && chunks[0][1]
						 && chunks[0][1].value().get().get({chunk::rows - 1, column, layer}).opacity() < 15
					 	)
					 || (
					 		row > 0 
					 	 && c.get({row - 1, column, layer}).opacity() < 15
					 	)
					){
						q = generate_block_face(block, c, block_position, back, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
					if(
						(
							row == chunk::rows - 1
						 && chunks[2][1] 
						 && chunks[2][1].value().get().get({0, column, layer}).opacity() < 15
					 	)
					 || (
					 		row < chunk::rows - 1 
					 	 && c.get({row + 1, column, layer}).opacity() < 15
					 	)
					){
						q = generate_block_face(block, c, block_position, front, position);
						m.vertices.insert(m.vertices.end(), q.begin(), q.end());
					}
				}
			}
		}
	}
	return m;
}

quad modeler::generate_block_face(
	const block& b,
	const chunk& c,
	const chunk::block_position_type& position, 
	block_face face,
	const chunk::position_type& chunk_position
) const{
	quad q;
	// 0.0011 to 0.0016 seconds (fastest)
	switch(face){
	case top:
		q[0].position = {0.0f, 1.0f, 1.0f};
		q[1].position = {1.0f, 1.0f, 1.0f};		
		q[2].position = {1.0f, 1.0f, 0.0f};
		q[3].position = {0.0f, 1.0f, 0.0f};
		for(auto& i: q) i.normal = {0.0f, 1.0f, 0.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.z == chunk::layers - 1)	q[i].sky_light = 1.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x,
					position.y,
					position.z + 1
				}
			).sky_light / 15;
			if(position.z == chunk::layers - 1)	q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x,
					position.y,
					position.z + 1
				}
			).torch_light / 15;
		}
		break;
	case bottom:
		q[0].position = {0.0f, 0.0f, 0.0f};
		q[1].position = {1.0f, 0.0f, 0.0f};		
		q[2].position = {1.0f, 0.0f, 1.0f};
		q[3].position = {0.0f, 0.0f, 1.0f};
		for(auto& i: q) i.normal = {0.0f, -1.0f, 0.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.z == 0)	q[i].sky_light = 0.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x,
					position.y,
					position.z - 1
				}
			).sky_light / 15;
			if(position.z == 0)	q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x,
					position.y,
					position.z - 1
				}
			).torch_light / 15;
		}
		break;
	case front:
		q[0].position = {0.0f, 0.0f, 1.0f};
		q[1].position = {1.0f, 0.0f, 1.0f};		
		q[2].position = {1.0f, 1.0f, 1.0f};
		q[3].position = {0.0f, 1.0f, 1.0f};
		for(auto& i: q) i.normal = {0.0f, 0.0f, 1.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.x == chunk::rows - 1) q[i].sky_light = 0.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x + 1,
					position.y,
					position.z
				}
			).sky_light / 15;
			if(position.x == chunk::rows - 1) q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x + 1,
					position.y,
					position.z
				}
			).torch_light / 15;
		}
		break;
	case back:
		q[0].position = {1.0f, 0.0f, 0.0f};
		q[1].position = {0.0f, 0.0f, 0.0f};		
		q[2].position = {0.0f, 1.0f, 0.0f};
		q[3].position = {1.0f, 1.0f, 0.0f};
		for(auto& i: q) i.normal = {0.0f, 0.0f, -1.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.x == 0) q[i].sky_light = 0.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x - 1,
					position.y,
					position.z
				}
			).sky_light / 15;
			if(position.x == 0) q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x - 1,
					position.y,
					position.z
				}
			).torch_light / 15;
		}
		break;
	case left:
		q[0].position = {0.0f, 0.0f, 0.0f};
		q[1].position = {0.0f, 0.0f, 1.0f};		
		q[2].position = {0.0f, 1.0f, 1.0f};
		q[3].position = {0.0f, 1.0f, 0.0f};
		for(auto& i: q) i.normal = {-1.0f, 0.0f, 0.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.y == 0) q[i].sky_light = 0.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x,
					position.y - 1,
					position.z
				}
			).sky_light / 15;
			if(position.y == 0) q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x,
					position.y - 1,
					position.z
				}
			).torch_light / 15;
		}
		break;
	case right:
		q[0].position = {1.0f, 0.0f, 1.0f};
		q[1].position = {1.0f, 0.0f, 0.0f};		
		q[2].position = {1.0f, 1.0f, 0.0f};
		q[3].position = {1.0f, 1.0f, 1.0f};
		for(auto& i: q) i.normal = {1.0f, 0.0f, 0.0f};
		for(auto i = 0; i < 4; ++i){
			if(position.y == chunk::columns - 1) q[i].sky_light = 0.0f;
			else q[i].sky_light = (float)c.get(
				{
					position.x,
					position.y + 1,
					position.z
				}
			).sky_light / 15;
			if(position.y == chunk::columns - 1) q[i].torch_light = 0.0f;
			else q[i].torch_light = (float)c.get(
				{
					position.x,
					position.y + 1,
					position.z
				}
			).torch_light / 15;
		}
		break;
	}
	// 0.0014 to 0.0029 seconds (slowest)
	/*q[0].position = {
		face == back || face == right,
		face == top,
		face == top || face == front || face == right
	};
	q[1].position = {
		face != back && face != left,
		face == top,
		face == top || face == front || face == left
	};
	q[2].position = {
		face != back && face != left,
		face != bottom,
		face == bottom || face == front || face == left
	};
	q[3].position = {
		face == back || face == right,
		face != bottom,
		face == bottom || face == front || face == right
	};
	for(auto& i: q) i.normal = {
		-(face == left) + (face == right),
		-(face == bottom) + (face == top),
		-(face == back) + (face == front)
	};*/
	typedef decltype(decltype(q)::value_type::position) position_type;
	typedef position_type::coord_type coordinate_type;
	for(auto& i: q){
		i.position += position_type{
			(coordinate_type)position.y, // column
			(coordinate_type)position.z, // layer
			(coordinate_type)position.x  // row
		};
		i.position.z += chunk_position.x * chunk::columns;
		i.position.x += chunk_position.y * chunk::rows;
	}
	auto uv_q{block_atlas.get_uv(atlas_position((block::id_type)b.id, face))};
	for(auto i = 0; i < 4; ++i) q[i].uv = uv_q[i];
	return q;
}

/*void modeler::position_quad(
	quad& q,
	modeler::block_face face
){
	
}*/

vec2<size_t> modeler::atlas_position(
	block::id_type id,
	block_face face
){
	switch(id){
	case block::grass:
		switch(face){
		case top: return {0, 0};
		case bottom: return {2, 0};
		default: return {1, 0};
		}
	case block::dirt: return {2, 0};
	case block::stone: return {3, 0};
	case block::leaves: return {4, 0};
	case block::fire: return {5, 0};
	default: return {};
	}
}
