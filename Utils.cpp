//Utils.cpp

#include"Utils.h"

std::string ReadGLSL(std::string filePath) {
	std::ifstream fileStream(filePath.c_str());
	assert(fileStream);
	return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

void ProgramErrorCheck(GLint program) {
	GLint logLength = 0;
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength <= 0)	return;
	std::string errorlog(logLength, '\0');
	glGetProgramInfoLog(program, logLength, nullptr, errorlog.data());
	std::cerr << errorlog << std::endl;
}

GLuint LoadShaderSource(GLuint flag, std::string shaderSourcePath, GLsizei count) {
	auto PrintErrorLog = [](GLuint shader, std::string fileName = "") {
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength <= 0)	return;
		std::string errorlog(logLength, '\0');
		glGetShaderInfoLog(shader, logLength, nullptr, errorlog.data());
		std::cerr << fileName << ": " << errorlog << std::endl;
	};
	std::string shaderSource = ReadGLSL(shaderSourcePath);
	const char* c_strShaderSource = shaderSource.c_str();
	GLuint shader = glCreateShader(flag);
	glShaderSource(shader, count, &c_strShaderSource, NULL);
	glCompileShader(shader);
	PrintErrorLog(shader, shaderSourcePath);
	return shader;
}

glm::mat4 buildTranslateMat(float x, float y, float z) {
	using namespace glm;
	return mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x,   y,   z,   1.0
		);
}

glm::mat4 buildRotateMat(float rad, RotateAxis axis) {
	using namespace glm;
	if (axis == RotateAxis::X) {
		return mat4(f1, f0, f0, f0,
			f0, cos(rad), -sin(rad), f0,
			f0, sin(rad), cos(rad), f0,
			f0, f0, f0, f1
		);
	}
	else if (axis == RotateAxis::Y) {
		return mat4(cos(rad), f0,sin(rad), f0,
			f0, f1, f0, f0,
			-sin(rad), f0, cos(rad), f0,
			f0, f0, f0, f1
		);
	}
	else if (axis == RotateAxis::Z) {
		return mat4(
			cos(rad), -sin(rad), f0, f0,
			sin(rad), cos(rad), f0, f0,
			f0, f0, f1, f0,
			f0, f0, f0, f1
		);
	}
	else {
		assert(-1 && "undefine RotateAxis");
	}
	return mat4();
}

glm::mat4 buildScaleMat(float x, float y, float z) {
	using namespace glm;
	constexpr auto f0 = 0.0;
	constexpr auto f1 = 1.0;
	return mat4(x, f0, f0, f0,
		f0, y, f0, f0,
		f0, f0, z, f0,
		f0, f0, f0, f1
	);
}

GLuint loadTexture(const char* texImagePath) {
	auto textureID = SOIL_load_OGL_texture(texImagePath,
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0)
		std::cout << "Textrue Load Failed, FileName:" << texImagePath << std::endl;
	return textureID;
}

GLuint loadTexture(const std::string& texImagePath) {
	return loadTexture(texImagePath.c_str());
}