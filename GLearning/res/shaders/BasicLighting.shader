//#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_FragPosition;
out vec3 v_Normal;

uniform mat4 u_ModelMatrix;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);

	v_TexCoord = texCoord;
	v_FragPosition = vec3(u_ModelMatrix * vec4(position, 1.0f));
	v_Normal = mat3(transpose(inverse(u_ModelMatrix))) * normal;
};


//#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_FragPosition;
in vec3 v_Normal;

uniform sampler2D u_Texture;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform float u_AmbientMultiplier;

void main()
{
	vec3 ambient = u_AmbientMultiplier * u_LightColor;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPosition - v_FragPosition);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_LightColor;

	vec4 texColor = texture(u_Texture, v_TexCoord);

	color = texColor * vec4(u_ObjectColor * u_LightColor * (ambient + diffuse), 1.0);
};