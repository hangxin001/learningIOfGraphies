#version 430
uniform float offset;
uniform float scaleOffset;
void main(void){
	if (gl_VertexID == 0)
		gl_Position = vec4((0 + offset) * scaleOffset, (-0.25 ) * scaleOffset, 0.0, 1.0);
	else if(gl_VertexID == 1)
		gl_Position = vec4( ( - 0.25 + offset) * scaleOffset, (0.25 ) * scaleOffset, 0.0, 1.0);
	else if (gl_VertexID == 2)
		gl_Position = vec4((0.25 + offset) * scaleOffset, (0.25 ) * scaleOffset, 0.0, 1.0);
	}