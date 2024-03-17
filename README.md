# COMP3016-CW2

## System Version
 Visual Studio Version: Visual Studio 2022(17.1.0)<br/>
 Operating System Version: Windows10 Home Edition 22H2

## How to do open and control prototype
Open:<br/>
Open the file and double-click to run the Project_Template.exe file.

Control:<br/>
Move the mouse to control the turn<br/>
The "W", "A", "S" and "D" keys control movement.<br/>
T: Turn on light light<br/>
F: Turn off light light

## How does the program code work
**Initialize and configure the system**:<br/>
- Import libraries and definitions: The program first imports OpenGL, GLFW, and other required libraries and header files.<br/>
- Initialize GLFW: Initialize GLFW and set the OpenGL version and configuration by calling `glfwInit` and related functions.<br/>
- Create window: Create a window with `glfwCreateWindow` and set it to be the primary context of the current thread.<br/>
- Initialize GLEW: Initializes GLEW (a function pointer used to manage OpenGL) to use OpenGL functionality.<br/>

**Setting up the rendering environment**:<br/>
- Set Viewport: Define the size of the render window through the `glViewport`.<br>
- Enable depth testing: Use `glEnable(GL_DEPTH_TEST)` to ensure that objects are rendered correctly in 3D space.<br/>

**Load shaders and resource**:<br/>
- Load Shader: Create `shader` objects for subsequent rendering shader processing.<br/>
- Load materials and textures: Use the `loadImageToGUP` function to load image textures to the GPU for material creation.<br/>
- Create light objects: Create `LightDirectional`, `LightPoint`, `LightSpot`, etc. objects that simulate different lighting effects.<br/>

**Ready render loop**:<br/>
- Model loading: Create `Model` objects and load 3D model data.<br/>
- Set up the MVP matrix: Configure the Model, View, and Projection matrices to render 3D objects correctly.

**Render loop**:<br/>
- Event handling: Window and keyboard events are handled through the `processInput` function.<br/>
- Clean the screen: Clear the color and depth buffers.<br/>
- Update Camera view: Update the `Camera` object to reflect changes in the user's perspective.<br/>
- Model rendering:<br/>
Set the MVP matrix for each model.<br/>
Apply the shader program.<br/>
Information such as lighting and material is passed to the shader.<br/>
Call `model.draw` to Draw the 3D Model.<br/>

**End cleanup**:<br/>
- End the render loop: Exit the render loop when `glfwWindowShouldClose` returns `true`.<br/>
- Resource release: Releases allocated resources, such as texture and shader objects.<br/>
- Shut down GLFW: Use `glfwTerminate` to end the program, shut down GLFW and clean up allocated resources.<br/>

## How did I do it
Special place: I created a new OpenGL texture object with my name "Qihao Han" surrounded by quadrangles using "name.png". Use `glBindTexture` to bind the newly created texture object to the currently active texture unit. It is to paste my name on the flashlight by this operation.<br/>

Idea: The flashlight lighting idea came from a light source I saw on the BIlibili website. For this I produced a light switch interaction scene.<br/>

How I do it: Understanding lighting requires looking at shader, which is key to my project. I need to understand vertex shaders such as coordinate transformations, do a good job of mapping colors and textures, understand basic lighting models, etc. This project allowed me to learn a lot from different resources and tools, such as learnopengl.com. Gave me a lot of help.<br/>

## Video Link
YouTube: https://youtu.be/3km-amrwrBQ

## Git Repository
GitHub: https://github.com/QihaoHan/COMP3016-CW2
