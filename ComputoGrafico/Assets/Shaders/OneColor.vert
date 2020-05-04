#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);

	if (gl_Position.z > 0.5f)
	{
		vCol = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else 
	{
		vCol = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}