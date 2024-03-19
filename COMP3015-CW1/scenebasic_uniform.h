#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/objmesh.h"

class SceneBasic_Uniform : public Scene
{
private:
    //GLuint vaoHandle;
    GLuint quadVaoHandle;
    GLSLProgram prog;
    GLSLProgram progModel;
    GLSLProgram projSkybox;
    GLuint sVAO;
    unsigned int skyboxTexture;

    float angle;

    void compile();

    Camera myCamera;

    GLuint texVec[3];
    std::unique_ptr<TriangleMesh> pModelTable;
    std::unique_ptr<TriangleMesh> pModelPhong;
public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
