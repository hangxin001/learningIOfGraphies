#version 430
out vec4 fragcolor;
in vec4 varyingColor;
in vec2 tc;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
layout(binding = 0) uniform sampler2D samp;
void main(void){
		fragcolor = varyingColor;
}