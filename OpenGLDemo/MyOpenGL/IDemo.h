#ifndef IDEMO_H
#define IDEMO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "stb_image.h"
#include "shader_m.h"
#include "camera.h"

class IDemo {
public:
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

	IDemo(unsigned int screen_width, unsigned int screen_height) {
		std::cout << "Demo create" << std::endl;
		SCR_WIDTH = screen_width;
		SCR_HEIGHT = screen_height;
	}

	virtual void init() { };
	virtual void draw(Camera camera, glm::vec3 lightPosition) { };
};



#endif // !IDEMO_H
