#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 vPosition;

void main()
{
    vPosition = aPos;
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

#type fragment
#version 330 core

layout(location=0) out vec4 color;

uniform vec4 u_Color;

in vec3 vPosition;

void main()
{
    color = u_Color;
};
