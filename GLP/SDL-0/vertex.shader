#version 330 core
in vec3 pos;
in vec3 fragColor;
out vec3 ourColor;

void main()
{
    ourColor = fragColor;
    gl_Position = vec4(pos,1.0);
}