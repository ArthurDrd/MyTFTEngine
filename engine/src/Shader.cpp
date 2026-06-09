#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace MyTFTEngine {
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		std::string vertexCode = ReadFile(vertexPath);
		std::string fragmentCode = ReadFile(fragmentPath);

		unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexCode);
		unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertex);
		glAttachShader(m_RendererID, fragment);
		glLinkProgram(m_RendererID);
		CheckCompileErrors(m_RendererID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

	std::string Shader::ReadFile(const std::string& filepath) {
		std::ifstream file(filepath);
		std::stringstream stream;

		if (!file.is_open()) {
			std::cerr << "[Shader Error] Could not open file: " << filepath << std::endl;
			return "";
		}

		stream << file.rdbuf();
		file.close();
		return stream.str();
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		std::string typeStr = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
		CheckCompileErrors(id, typeStr);
		return id;
	}

	void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				std::cerr << "[Shader Compile Error] Type: " << type << "\n" << infoLog << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				std::cerr << "[Shader Linking Error] Type: " << type << "\n" << infoLog << std::endl;
			}
		}
	}

	void Shader::SetInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) {
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}