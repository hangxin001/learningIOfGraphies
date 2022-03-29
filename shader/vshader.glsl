#version 430

layout(location = 0) in vec3 postion;
layout(location = 1) in vec2 texCoord;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;

out vec4 varyingColor;
out vec2 tc;
mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x,float y, float z);
void main(void){

	float i = gl_InstanceID + tf;
	float a = sin(203 * i/8000) * 403.0;
	float b = sin(301 * i/4001) * 401.0;
	float c = sin(400 * i/6003) * 405.0;

	mat4 localRotX = buildRotateX(1 * i);
	mat4 localRotY = buildRotateY(5 * i);
	mat4 localRotZ = buildRotateZ(5 * i);
	mat4 localTrans = buildTranslate(a,b,c);

	mat4 newM_matrix = m_matrix * localRotX;// * localTrans * localRotX * localRotY * localRotZ;	//注意是列优先存储
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(postion,1.0);
	varyingColor = vec4(postion,1.0) * 0.5 + vec4(0.5,0.5,0.5,0.5);
	tc = texCoord;
}

mat4 buildTranslate(float x,float y, float z){
	mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    x, y, z, 1.0 );
	return trans;
}

mat4 buildRotateX(float rad){
	mat4 rMatrix = mat4(1,0,0,0,
		0, cos(rad),sin(rad),0,
		0,-sin(rad),cos(rad),0,
		0,0,0,1
		);
	return rMatrix;
}
mat4 buildRotateY(float rad){
	mat4 rMatrix = mat4(
		cos(rad),0,-sin(rad),0,
		0,1,0,0,
		sin(rad),0,cos(rad),0,
		0,0,0,1
		);
	return rMatrix;
}
mat4 buildRotateZ(float rad){
	mat4 rMatrix = mat4(
			cos(rad),sin(rad),0,0,
			-sin(rad),cos(rad),0,0,
			0,0,1,0,
			0,0,0,1
		);
	return rMatrix;
}