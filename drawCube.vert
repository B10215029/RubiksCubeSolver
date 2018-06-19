#version 430
uniform mat4 mvMatrix;
uniform mat4 projectionMatrix;
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec3 uv;
out vec3 normal;
out vec3 texcoord;

void main() {
    normal = mat3(mvMatrix) * vNormal;
	texcoord = uv;
	gl_Position = projectionMatrix * mvMatrix * vec4(vertex, 1);
}
