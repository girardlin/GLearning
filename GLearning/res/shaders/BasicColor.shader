//#shader vertex
#version 330 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec4 v_Color;

out vec4 f_Color;

void main()
{
	gl_Position = v_Position;
	f_Color = v_Color;
};


//#shader fragment
#version 330 core

in vec4 f_Color;
out vec4 gl_Color;

void main()
{
	gl_Color = f_Color;
};