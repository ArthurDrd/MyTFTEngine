#version 450 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_LocalPosition;

void main()
{
    v_LocalPosition = a_Position.xz;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}