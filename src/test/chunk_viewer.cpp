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

sf::RenderWindow window{
	sf::VideoMode(900, 900),
	"Block Game"
};

modeler m;
chunk c;
generator gen;
model cm;
vbo vb;
vao va;

using namespace std::chrono;
steady_clock::time_point start, end;

int main(){
	glewInit();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	start = steady_clock::now();
	c = gen({0, 0});
	end = steady_clock::now();
	std::cout 
 << "Chunk generated in " 
 << duration<float>(end - start).count()
 << "seconds" 
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
 
 	sf::Shader shader;
 	shader.loadFromFile(
 		"shaders/vertex_shader", 
 		"shaders/fragment_shader"
 	);
 
 	va.load();
 	vb.load_from_model(cm, vbo::static_draw);
	
	bool running = true;
	while(running){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
			case sf::Event::Closed:
				running = false;
			default:
				break;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Make matrix for triangle
		glm::mat4 projection = glm::perspective(
			glm::radians(90.0f), 
			1.0f / 1.0f, 
			0.1f, 
			1000.0f
		);
		
		glm::mat4 view = glm::lookAt(
			glm::vec3(18, 8, 18),
			glm::vec3(8.0f, 8.0f, 8.0f),
			glm::vec3(0, 1, 0)
		);
		
		glm::mat4 model{1.0f};
		
		glm::mat4 mvp = projection * view * model;
		
		float matrix[16] = {
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
		};
		
		shader.setUniform(
			"mvp", 
			sf::Glsl::Mat4(
				matrix
			)
		);
		
		sf::Shader::bind(&shader);
		va.bind();
		glDrawArrays(GL_QUADS, 0, vb.vertex_count);
		window.display();
	}
}
