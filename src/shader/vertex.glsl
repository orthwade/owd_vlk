#version 450

vec2 vec2_pos[3] = vec2[]
(
	vec2(0.0f, -0.5f),
	vec2(0.5f, 0.5f),
	vec2(-0.5f, -0.5f)
);

void main()
{
	gl_Position = vec4(vec2_pos[gl_VertexIndex], 0.0f, 1.0f);
}