#version 430
uniform samplerCube cubeTexture;
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
	//fragColor = vec4(1 * abs(normalize(normal).z), 0, 0, 1);
	//fragColor = vec4(1, 0, 0, 1);
	float diffuse = abs(normalize(normal).z) / 2 + 0.5f;
	float color = texture(cubeTexture, texcoord).x;
	float board = 1.0f;
	if (size != 0) {
		vec3 boardValue;
		for (int i = 0; i < 3; i++) {
			float t = (texcoord[i] + 1.0f) / 2.0f;
			t = abs(t * size - int(t * size));
			float lineWidth = 1.0 / size;
			t = t * 2.0f - 1.0f;
			boardValue[i] = 1 - pow(abs(t), 10);
		}
		//board = boardValue.x + boardValue.y + boardValue.z;
		//board -= max(boardValue.x, max(boardValue.y, boardValue.z));
		//board -= min(boardValue.x, min(boardValue.y, boardValue.z));
		board = max(min(boardValue.x, boardValue.y), min(max(boardValue.x, boardValue.y), boardValue.z));
	}
	fragColor = vec4(vec3(colors[int(color * 255f)] * diffuse * board), 1);
}
