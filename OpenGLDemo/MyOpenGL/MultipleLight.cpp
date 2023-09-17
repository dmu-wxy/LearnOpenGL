#include "MultipleLight.h"
#include "utils/TextureUtils.h"

MultipleLight::MultipleLight(unsigned int screen_width, unsigned int screen_height) : IDemo(screen_width, screen_height), cubeVAO(-1), lightCubeVAO(-1), VBO(-1), pLightingShader(nullptr), pLightCubeShader(nullptr) {}

MultipleLight::~MultipleLight() {
    delete pLightingShader;
    delete pLightCubeShader;

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

void MultipleLight::init() {
    std::cout << "Demo init" << std::endl;

    // build and compile our shader zprogram
    // ------------------------------------
    pLightingShader = new Shader("2.2.basic_lighting.vs", "2.6.basic_lighting.fs");
    pLightCubeShader = new Shader("2.2.light_cube.vs", "2.2.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    // positions all containers
    glm::vec3 pcubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    cubePositions = pcubePositions;
    // µã¹âÔ´
    glm::vec3 ppointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    pointLightPositions = ppointLightPositions;
    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coords
    texture1 = TextureUtils::loadTexture("container2.png");
    texture2 = TextureUtils::loadTexture("container2_specular.png");
}
glm::vec3 pcubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 ppointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};
void MultipleLight::draw(Camera camera, glm::vec3 lightPosition) {


    // be sure to activate shader when setting uniforms/drawing objects
    pLightingShader->use();
    pLightingShader->setVec3("viewPos", camera.Position);
    pLightingShader->setInt("material.diffuse", 0);
    pLightingShader->setInt("material.specular", 1);
    pLightingShader->setFloat("material.shininess", 32.0f);

    // set light param
    glm::vec3 lightColor;
    lightColor.x = 1;// sin(glfwGetTime() * 2.0f);
    lightColor.y = 1;// sin(glfwGetTime() * 0.7f);
    lightColor.z = 1;// sin(glfwGetTime() * 1.3f);

    /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
    */
    // directional light
    pLightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    pLightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    pLightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    pLightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    pLightingShader->setVec3("pointLights[0].position", ppointLightPositions[0]);
    pLightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    pLightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    pLightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    pLightingShader->setFloat("pointLights[0].constant", 1.0f);
    pLightingShader->setFloat("pointLights[0].linear", 0.09f);
    pLightingShader->setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    pLightingShader->setVec3("pointLights[1].position", ppointLightPositions[1]);
    pLightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    pLightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    pLightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    pLightingShader->setFloat("pointLights[1].constant", 1.0f);
    pLightingShader->setFloat("pointLights[1].linear", 0.09f);
    pLightingShader->setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    pLightingShader->setVec3("pointLights[2].position", ppointLightPositions[2]);
    pLightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    pLightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    pLightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    pLightingShader->setFloat("pointLights[2].constant", 1.0f);
    pLightingShader->setFloat("pointLights[2].linear", 0.09f);
    pLightingShader->setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    pLightingShader->setVec3("pointLights[3].position", ppointLightPositions[3]);
    pLightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    pLightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    pLightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    pLightingShader->setFloat("pointLights[3].constant", 1.0f);
    pLightingShader->setFloat("pointLights[3].linear", 0.09f);
    pLightingShader->setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    pLightingShader->setVec3("spotLight.position", camera.Position);
    pLightingShader->setVec3("spotLight.direction", camera.Front);
    pLightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    pLightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    pLightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    pLightingShader->setFloat("spotLight.constant", 1.0f);
    pLightingShader->setFloat("spotLight.linear", 0.09f);
    pLightingShader->setFloat("spotLight.quadratic", 0.032f);
    pLightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    pLightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    pLightingShader->setMat4("projection", projection);
    pLightingShader->setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    glBindVertexArray(cubeVAO);
    // render texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    for (unsigned int i = 0; i < 10; i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pcubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        pLightingShader->setMat4("model", model);

        // render the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // also draw the lamp object
    pLightCubeShader->use();
    pLightCubeShader->setMat4("projection", projection);
    pLightCubeShader->setMat4("view", view);
    for (unsigned int i = 0; i < 4; i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, ppointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        pLightCubeShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // glBindVertexArray(lightCubeVAO);
}

