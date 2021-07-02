#include "shaderList.h"

std::vector<std::string> _shaders = {

R"glsl(
#version 400 core
layout(location = 0) in vec3 position;
uniform mat4 uProj;
void main() {
gl_Position = uProj * vec4(position, 1);
}
$
#version 400 core
out vec4 fragColor;
uniform vec4 uColor;
void main() {
fragColor = uColor;
}
)glsl",

R"glsl(#version 400 core
layout(location = 0) in vec3 position;
uniform mat4 uMV;
uniform mat4 uProj;
void main() {
gl_Position = uProj * uMV * vec4(position, 1);
}
$
#version 400 core
out vec4 fragColor;uniform vec4 uColor;
void main() {
fragColor = uColor;
}
)glsl",

R"glsl(#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
out vec2 vTexCoord;
uniform mat4 uMV;
uniform mat4 uProj;
void main() {
vTexCoord = texCoord;
gl_Position = uProj * uMV * vec4(position, 1);
}
$
#version 400 core
out vec4 fragColor;in vec2 vTexCoord;
uniform sampler2D uTexture;
void main() {
fragColor = texture(uTexture, vTexCoord);
}
)glsl",

R"glsl(#version 400 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
uniform mat4 uMV;
uniform mat4 uProj;
void main() {
gl_Position = uProj * uMV * vec4(position, 1);
}
$
#version 400 core
out vec4 fragColor;uniform vec4 uColor;
void main() {
fragColor = uColor;
}
)glsl",

R"glsl(#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
out vec2 vTexCoord;
uniform mat4 uMV;
uniform mat4 uProj;
void main() {
vTexCoord = texCoord;
gl_Position = uProj * uMV * vec4(position, 1);
}
$
#version 400 core
out vec4 fragColor;in vec2 vTexCoord;
uniform sampler2D uTexture;
void main() {
fragColor = texture(uTexture, vTexCoord);
}
)glsl",

};
