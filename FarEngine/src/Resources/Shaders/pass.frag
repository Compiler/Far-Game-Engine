#version 460


layout(location = 0) in vec4 o_color;
layout(location = 1) in vec2 o_texCoords;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_texture;

void main(){
    
    outColor = o_color;
}
