#version 330 core
out vec4 fragColor;
in vec3 ourColor;

void main()
{
	//FragColor = ourColor;
	fragColor = vec4(ourColor,1.0);
};