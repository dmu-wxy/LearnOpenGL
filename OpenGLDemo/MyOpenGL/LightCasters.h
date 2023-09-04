#ifndef LIGHTCASTERS_H
#define LIGHTCASTERS_H

#include "IDemo.h"

class LightCasters :public IDemo {
public:
	LightCasters(unsigned int screen_width, unsigned int screen_height);
	~LightCasters();
	void init() override;
	void draw(Camera camera, glm::vec3 lightPos) override;
private:
	Shader* pLightingShader, * pLightCubeShader;
	unsigned int cubeVAO, lightCubeVAO, VBO;
	unsigned int texture1, texture2;
};
#endif // !LIGHTCASTERS_H
