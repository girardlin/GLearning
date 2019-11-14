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

/* Material Definition */
struct Material
{
	sampler2D diffuseColor;
	sampler2D specularColor;
	float shininess;
};

/* Light Definition */
struct Light
{
	vec3 position;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

layout(location = 0) out vec4 gl_Color;

in vec2 v_TexCoord;
in vec3 v_FragPosition;
in vec3 v_Normal;

uniform vec3 u_ViewPosition;

uniform Material u_Material;
uniform Light u_Light;

void main()
{
	/* ambient light calculation */
	vec3 ambient = u_Light.ambientColor * vec3(texture(u_Material.diffuseColor, v_TexCoord));

	/* diffuse lighting calculation */
	vec3 normalVector = normalize(v_Normal);
	vec3 lightDirection = normalize(u_Light.position - v_FragPosition);

	float diff = max(dot(normalVector, lightDirection), 0.0);
	vec3 diffuse = u_Light.diffuseColor * diff * vec3(texture(u_Material.diffuseColor, v_TexCoord));

	/* specular lighting calculation */
	vec3 viewDirection = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalVector);

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.shininess);
	vec3 specular = u_Light.specularColor * spec * vec3(texture(u_Material.specularColor, v_TexCoord));

	/* output color */
	gl_Color = vec4(ambient + diffuse + specular, 1.0f);
};