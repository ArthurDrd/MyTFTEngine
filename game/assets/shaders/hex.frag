#version 450 core

in vec2 v_LocalPosition;

uniform vec4 u_FillColor;
uniform vec4 u_BorderColor;
uniform float u_HexRadius; 
uniform float u_BorderThickness;

out vec4 FragColor;

float HexagonDistance(vec2 p)
{
    p = abs(p);
    float c = dot(p, normalize(vec2(1.0,sqrt(3))));
    return max(c, p.x);
}

void main()
{
    float dist = HexagonDistance(v_LocalPosition);
    
    float outerRadius = u_HexRadius;
    float innerRadius = u_HexRadius - u_BorderThickness;

    float edge = smoothstep(innerRadius, outerRadius, dist);

    FragColor =  mix(u_FillColor, u_BorderColor, edge);
}