#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 color1;


void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	//vec3 pp = clamp(playerPos,0,1);
	vCol = vec4(color1,1.0);
}