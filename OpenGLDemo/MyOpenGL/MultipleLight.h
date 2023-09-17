#ifndef MULTIPLELIGHT_H
#define MULTIPLELIGHT_H

#include "IDemo.h"

class MultipleLight :public IDemo {
public:
	MultipleLight(unsigned int screen_width, unsigned int screen_height);
	~MultipleLight();
	void init() override;
	void draw(Camera camera, glm::vec3 lightPosition) override;
private:
	Shader* pLightingShader, * pLightCubeShader;
	unsigned int cubeVAO, lightCubeVAO, VBO;
	unsigned int texture1, texture2;
	glm::vec3 *pointLightPositions, *cubePositions;
};
#endif // !MULTIPLELIGHT_H
