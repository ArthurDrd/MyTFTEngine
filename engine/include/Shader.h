#pragma once
#include <string>

namespace MyTFTEngine {
	class Shader {
	
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();
		
		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);

	private:
		unsigned int m_RendererID;

		std::string ReadFile(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		void CheckCompileErrors(unsigned int shader, std::string type);
	};
}