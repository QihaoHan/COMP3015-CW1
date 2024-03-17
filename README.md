# COMP3015-CW1

## System Version
 Visual Studio Version: Visual Studio 2022(17.1.0)<br/>
 Operating System Version: Windows10 Home Edition 22H2

## How to do open and control prototype
Open:<br/>
Open the file and double-click to run the Project_Template.exe file.

Control:<br/>
Move the mouse to control the turn<br/>
"W", "A", "S" and "D" control forward, left, backward and left movement respectively.<br/>
T: Turn on light light<br/>
F: Turn off light light

## How does the program work

This OpenGL-based application showcases fundamental 3D graphics techniques, providing an immersive scene with Phong lighting, basic textures, skybox, and interactive controls:<br>

Basic Lighting: Implements the Phong lighting model, creating lifelike interactions between light and objects through ambient, diffuse, and specular reflections.<br>

Basic textures: Apply detailed images to the surface of a 3D model with texture mapping, enhancing its appearance with details such as color, pattern, and material properties.<br>

Skybox: Uses a cubemap to render a surrounding environment, offering a distant background that adds depth and immersion to the 3D space.<br>

Mouse and Keyboard Controls: The user can control the movement by moving the angle of view with the mouse, WASD, and T and F can control the switch of light.<br>

## 
Special place: I created a new OpenGL texture object with my name "Qihao Han" surrounded by quadrangles using "name.png". Use `glBindTexture` to bind the newly created texture object to the currently active texture unit. It is to paste my name on the flashlight by this operation.<br/>

Idea: The flashlight lighting idea came from a light source I saw on the BIlibili website. For this I produced a light switch interaction scene.<br/>

How I do it: Understanding lighting requires looking at shader, which is key to my project. I need to understand vertex shaders such as coordinate transformations, do a good job of mapping colors and textures, understand basic lighting models, etc. This project allowed me to learn a lot from different resources and tools, such as learnopengl.com. Gave me a lot of help.<br/>

## Video Link
YouTube: https://youtu.be/3km-amrwrBQ

## Git Repository
GitHub: 
