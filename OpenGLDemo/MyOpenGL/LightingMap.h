#ifndef LIGHTINGMAP_H
#define LIGHTINGMAP_H

#include "IDemo.h"

class LightingMap :public IDemo {
public:
	LightingMap(unsigned int screen_width, unsigned int screen_height);
	~LightingMap();
	void init() override;
	void draw(Camera camera, glm::vec3 lightPos) override;
private:
	Shader* pLightingShader, * pLightCubeShader;
	unsigned int cubeVAO, lightCubeVAO, VBO;
	unsigned int texture1,texture2;
};

#endif // !LIGHTINGMAP_H
