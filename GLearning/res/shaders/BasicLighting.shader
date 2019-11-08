//#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_FragPosition;
out vec3 v_Normal;

uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;
uniform mat4 u_MVP;

void main()
{
	/* output position */
	gl_Position = u_MVP * vec4(position, 1.0f);

	/* pass to fragment shader */
	v_TexCoord = texCoord;
	v_FragPosition = vec3(u_ModelMatrix * vec4(position, 1.0f));
	v_Normal = u_NormalMatrix * normal;
};


//#shader fragment
#version 330 core

layout(location = 0) out vec4 gl_Color;

in vec2 v_TexCoord;
in vec3 v_FragPosition;
in vec3 v_Normal;

uniform sampler2D u_Texture;
uniform float u_AmbientMultiplier;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

void main()
{
	/* ambient light calculation */
	vec3 ambient = u_AmbientMultiplier * u_LightColor;

	/* diffuse lighting calculation */
	vec3 normalVector = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPosition - v_FragPosition);

	float diff = max(dot(normalVector, lightDirection), 0.0);
	vec3 diffuse = diff * u_LightColor;

	/* specular lighting calculation */
	float specularStrength = 0.5f;

	vec3 viewDirection = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalVector);

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 64);
	vec3 specular = specularStrength * spec * u_LightColor;

	/* texture */
	vec4 textureColor = texture(u_Texture, v_TexCoord);

	/* output color */
	gl_Color = textureColor * vec4((u_ObjectColor * u_LightColor * (ambient + diffuse + specular)), 1.0f);
};