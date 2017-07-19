#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // TODO Remove
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../modeler.hpp"
#include "../generator.hpp"
#include "../vbo.hpp"
#include "../vao.hpp"
#include "../atlas.hpp"
#include "../shader.hpp"

using namespace std::chrono;
steady_clock::time_point start, end;

int main(){
	std::cout << "size of block: " << sizeof(block) << std::endl;

	// Open window
	sf::RenderWindow window(
		sf::VideoMode(800, 600), 
		"Block Game",
		sf::Style::Default,
		sf::ContextSettings(
			24,
			8,
			0,
			4,
			3
		)
	);	

	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	glewInit();
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	
	modeler m;
	chunk c;
	generator gen;
	model cm;
	vbo vb;
	vao va;
	// atlas at;
	
	start = steady_clock::now();
	c = gen({0, 0});
	end = steady_clock::now();
	std::cout 
 << "Chunk generated in " 
 << duration<float>(end - start).count()
 << " seconds" 
 << std::endl;
 
 	std::cout
 << "Number of blocks: "
 << chunk::rows * chunk::columns * chunk::layers
 << std::endl;
	
	start = steady_clock::now();
	cm = m.generate_chunk_model(c);
	end = steady_clock::now();
	std::cout 
 << "Chunk modeled generated in " 
 << duration<float>(end - start).count() 
 << " seconds" 
 << std::endl;
 
	std::cout 
 << "Number of vertices: " 
 << cm.vertices.size() 
 << std::endl;

	/*at.rows = 16;
	at.columns = 16;
	at.texture.loadFromFile("textures/blocks.png");*/
	 
 	/*sf::Shader shader;
 	shader.loadFromFile(
 		"shaders/vertex_shader", 
 		"shaders/fragment_shader"
 	);*/
 	
 	shader s{
 		"shaders/vertex_shader",
 		"shaders/fragment_shader"
 	};
 	
 	GLint mvp_id{glGetUniformLocation(s.get_id(), "mvp")};
 	GLint sampler_id{glGetUniformLocation(s.get_id(), "sampler")};
 
 	va.load();
 	vb.load_from_model(cm, vbo::static_draw);
	/*
	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
	*/
 	
 	// TODO make OOP
 	/*GLuint sampler;
 	glGenSamplers(1, &sampler);*/

 	
 	glm::vec3 camera_position{18.0f, 8.0f, 18.0f},
 	          camera_velocity{0.0f, 0.0f, 0.0f};
 	          
 	float camera_speed = 16.0f;
 	
 	sf::Clock clock;
	
	bool running = true;
	while(running){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
			case sf::Event::Closed:
				running = false;
			case sf::Event::KeyPressed:
				switch(e.key.code){
				case sf::Keyboard::A:
					camera_velocity.x += camera_speed;
					break;
				case sf::Keyboard::E:
					camera_velocity.x -= camera_speed;
					break;
				case sf::Keyboard::Comma:
					camera_velocity.z += camera_speed;
					break;
				case sf::Keyboard::O:
					camera_velocity.z -= camera_speed;
					break;
				case sf::Keyboard::LShift:
					camera_velocity.y -= camera_speed;
					break;
				case sf::Keyboard::Space:
					camera_velocity.y += camera_speed;
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(e.key.code){
				case sf::Keyboard::A:
					camera_velocity.x -= camera_speed;
					break;
				case sf::Keyboard::E:
					camera_velocity.x += camera_speed;
					break;
				case sf::Keyboard::Comma:
					camera_velocity.z -= camera_speed;
					break;
				case sf::Keyboard::O:
					camera_velocity.z += camera_speed;
					break;
				case sf::Keyboard::LShift:
					camera_velocity.y += camera_speed;
					break;
				case sf::Keyboard::Space:
					camera_velocity.y -= camera_speed;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		
		camera_position += camera_velocity * clock.getElapsedTime().asSeconds();
		clock.restart();
		
		// Make matrix for triangle
		glm::mat4 projection = glm::perspective(
			glm::radians(60.0f), 
			4.0f / 3.0f, 
			0.1f, 
			1000.0f
		);
		
		glm::mat4 view = glm::lookAt(
			camera_position,
			glm::vec3(8.0f, camera_position.y - 4.0f, 8.0f),
			glm::vec3(0, 1, 0)
		);
		
		glm::mat4 model{1.0f};
		
		glm::mat4 mvp = projection * view * model;
		
		/*float matrix[16] = {
			mvp[0][0],
			mvp[0][1],
			mvp[0][2],
			mvp[0][3],
			mvp[1][0],
			mvp[1][1],
			mvp[1][2],
			mvp[1][3],
			mvp[2][0],
			mvp[2][1],
			mvp[2][2],
			mvp[2][3],
			mvp[3][0],
			mvp[3][1],
			mvp[3][2],
			mvp[3][3],
		};*/
		
		/*sf::Shader::bind(&shader);
		
		shader.setUniform(
			"mvp", 
			sf::Glsl::Mat4(
				matrix
			)
		);
		
		shader.setUniform(
			"sampler",
			sf::Glsl::Vec4()
		);*/
		
		// glBindSampler(0, sampler);
		
		// TODO make uniform OOP		
		s.bind();
		
		m.block_atlas.bind();
		glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
		glUniform1i(sampler_id, 0);
		
		// sf::Texture::bind(&at.texture);
		// sf::Texture::bind(&m.block_atlas.texture);
		va.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_QUADS, 0, vb.vertex_count);
		window.display();
	}
}
