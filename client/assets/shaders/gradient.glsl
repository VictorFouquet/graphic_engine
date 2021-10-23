#type vertex
#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 vPosition;
out vec4 vColor;

void main()
{
    vPosition = a_Pos;
    vColor = a_Color;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos.x, a_Pos.y, a_Pos.z, 1.0);
};

#type fragment
#version 330 core

layout(location=0) out vec4 color;

in vec3 vPosition;
in vec4 vColor;

void main()
{
    color = vec4(vPosition * 0.6 + 0.5, 1.0);
    color = vColor;
};
