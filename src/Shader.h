#ifndef _SHADER_H_
#define _SHADER_H_
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader {
    enum class ShaderType{
        PROGRAM = 0,
        VERTEX = 1,
        FRAGMENT = 2,
        OTHER = 4
    }
public:
    unsigned int m_ID;

    Shader(const char *vertexPath, const char *fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            
            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, ShaderType::VERTEX);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, ShaderType::FRAGMENT);

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        checkCompileErrors(m_ID, ShaderType::PROGRAM);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Bind() {
        glUseProgram(m_ID);
    }
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

private:
    void checkCompileErrors(unsigned int shader, ShaderType type) {
        int success;
        char infoLog[1024];
        if (type != ShaderType::PROGRAM) {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << __LINE__ << " " << #type << "\n" << infoLog << "\n ---------------------------------------------------------";
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << __LINE__ << " " << #type << "\n" << infoLog << "\n ---------------------------------------------------------";
            }
        }
    }
};

#endif