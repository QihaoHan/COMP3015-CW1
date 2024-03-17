#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "model.h"

using glm::vec3;

SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f) {}

Model* pModelTable;
Model* pModelPhone;

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
void SceneBasic_Uniform::initScene()
{
    compile();

    std::cout << std::endl;

    prog.printActiveUniforms();

    /////////////////// Create the VBO ////////////////////
    float quadPosition[] = {
        5.f, -0.0f,  5.f,
       -5.f, -0.0f,  5.f,
       -5.f, -0.0f, -5.f,
        5.f, -0.0f,  5.f,
       -5.f, -0.0f, -5.f,
        5.f, -0.0f, -5.f,
    };

    float quadNormal[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    float quadTexcoord[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    // Create and populate the buffer objects
    GLuint quadVboHandles[3];
    glGenBuffers(3, quadVboHandles);
    GLuint quadPositionBufferHandle = quadVboHandles[0];
    GLuint quadNormalBufferHandle = quadVboHandles[1];
    GLuint quadTexCoordBufferHandle = quadVboHandles[2];

    glBindBuffer(GL_ARRAY_BUFFER, quadPositionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadPosition), quadPosition, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, quadNormalBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadNormal), quadNormal, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexcoord), quadTexcoord, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays( 1, &quadVaoHandle );
    glBindVertexArray(quadVaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color
    glEnableVertexAttribArray(2);  



    #ifdef __APPLE__
        glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

        glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    #else
        glBindVertexBuffer(0, quadPositionBufferHandle, 0, sizeof(GLfloat) * 3);
        glBindVertexBuffer(1, quadNormalBufferHandle, 0, sizeof(GLfloat) * 3);
        glBindVertexBuffer(2, quadTexCoordBufferHandle, 0, sizeof(GLfloat) * 2);

        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(1, 1);
        glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(2, 2);

    #endif
        glBindVertexArray(0);


     //model
    pModelTable = new Model("model/table/table.obj");
    pModelPhone = new Model("model/oldphone/newPhone.obj");


    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    // skybox VAO

    GLuint sVBO;
    glGenVertexArrays(1, &sVAO);
    glGenBuffers(1, &sVBO);
    glBindVertexArray(sVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> faces
    {

        "skybox/left.png",
        "skybox/right.png",
        "skybox/up.png",
        "skybox/down.png",
        "skybox/front.png",
        "skybox/back.png"
    };
    skyboxTexture = loadCubemap(faces);


    myCamera.Position = glm::vec3(0, 3, 5);

    glEnable(GL_DEPTH_TEST);
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

    try {
        progModel.compileShader("shader/model.vert");
        progModel.compileShader("shader/model.frag");
        progModel.link();
        progModel.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }


    try {
        projSkybox.compileShader("shader/skybox.vert");
        projSkybox.compileShader("shader/skybox.frag");
        projSkybox.link();
        projSkybox.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}



bool isFirstIn = true;
static float lastTime;
void SceneBasic_Uniform::update(float t)
{
    if (isFirstIn) {
        isFirstIn = false;
        lastTime = t;
    }
    float dt = t - lastTime;

    //update your angle here
    if (updateMove) {
        myCamera.ProcessKeyboard(m_cameraStatus, dt);
        updateMove = false;
    }


    myCamera.ProcessMouseMovement(scOffsetX, scOffsetY);


    lastTime = t;
}


void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //create the rotation matrix here and update the uniform in the shader 
    glm::mat4 projection = glm::perspective(glm::radians(60.f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = myCamera.GetViewMatrix();

    prog.use();
    prog.setUniform("projection", projection);
    prog.setUniform("view", view);
   
    // render floor
    glBindVertexArray(quadVaoHandle);
    glm::mat4 model = glm::mat4(1.f);
    prog.setUniform("model", model);
    prog.setUniform("floorColor", glm::vec3(139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f));


    if (openLight) {
        prog.setUniform("openLight", true);
    }
    else {
        prog.setUniform("openLight", false);
    }

    glDrawArrays(GL_TRIANGLES, 0, 6);


    // render Model
    progModel.use();
    progModel.setUniform("projection", projection);
    progModel.setUniform("view", view);
    progModel.setUniform("pointLights[0].position", glm::vec3(5, 5, 5));
    progModel.setUniform("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
    progModel.setUniform("pointLights[0].diffuse", 1.0, 1.0, 1.0);
    progModel.setUniform("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    progModel.setUniform("viewPos", myCamera.Position);

    if (openLight) {
        progModel.setUniform("openLight", true);
    }
    else {
        progModel.setUniform("openLight", false);
    }



    model = glm::mat4(1.0f);
    progModel.setUniform("model", model);
    pModelTable->Draw(progModel);


    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 1.9, 0));
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
    progModel.setUniform("model", model);

    pModelPhone->Draw(progModel);


    // draw skybox
    glDepthFunc(GL_LEQUAL);
    projSkybox.use();
    view = glm::mat4(glm::mat3(view));
    projSkybox.setUniform("view", view);
    projSkybox.setUniform("projection", projection);
    // skybox cube
    glBindVertexArray(sVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);

    glBindVertexArray(0);
}

void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0,0,w,h);
}
