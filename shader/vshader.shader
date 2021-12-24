#version 430
//uniform float offset;
//uniform float scaleOffset;
uniform vec4 vertexs[3];
void main(void){
	if (gl_VertexID == 0)
		gl_Position = vertexs[0];
	else if(gl_VertexID == 1)
		gl_Position = vertexs[1];
	else if (gl_VertexID == 2)
		gl_Position = vertexs[2];
	}