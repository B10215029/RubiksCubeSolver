#version 430
uniform sampler2DArray cubeTexture;
uniform int size;
in vec3 normal;
in vec3 texcoord;

out vec4 fragColor;
const vec3 colors[] = {
	vec3(0, 1, 0),
	vec3(1, 0, 0),
	vec3(1, 1, 1),
	vec3(0, 0, 1),
	vec3(1, 0.5, 0),
	vec3(1, 1, 0),
};

void main() {
	float diffuse = abs(normalize(normal).z) / 2.0f + 0.5f;
	float color = texture(cubeTexture, texcoord).x;
	float board = 1.0f;
	if (size != 0) {
		vec2 boardValue = texcoord.xy;
		boardValue = abs(boardValue * size - ivec2(boardValue * size));
		boardValue = abs(boardValue * 2.0f - 1.0f);
		boardValue = pow(boardValue, vec2(10));
		board = max(1.0f - (boardValue.x + boardValue.y), 0);
	}
	fragColor = vec4(vec3(colors[int(color * 255f)] * diffuse * board), 1);
}
