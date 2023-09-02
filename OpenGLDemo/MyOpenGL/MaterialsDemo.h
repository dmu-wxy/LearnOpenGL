#ifndef MATERIALSDEMO_H
#define MATERIALSDEMO_H

#include "IDemo.h"

class MaterialsDemo : public IDemo
{
public:
    MaterialsDemo(unsigned int screen_width, unsigned int screen_height);
    ~MaterialsDemo();

	void init() override;
	void draw(Camera camera, glm::vec3 lightPos) override;
private:
    Shader *pLightingShader,*pLightCubeShader;
    unsigned int cubeVAO, lightCubeVAO,VBO;
};


#endif // !MATERIALSDEMO_H
