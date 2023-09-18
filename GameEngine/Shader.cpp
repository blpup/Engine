#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int GameEngine::Shader::CreateShader(const std::string& vertextShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

std::string GameEngine::Shader::CreateVertexShader()
{
    return
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec3 position;"
        "layout(location = 1) in vec3 aColor;"
        "layout(location = 2) in vec2 aTexCoord;"
        "out vec3 ourColor;"
        "out vec2 TexCoord;"
        "\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position, 1.0);\n"
        "ourColor = aColor;\n"
        "TexCoord = aTexCoord;\n"
        "}\n";
}

std::string GameEngine::Shader::CreateFragmentShader()
{
    return
        "#version 330 core\n"
        "\n"
        "out vec4 color;"
        "in vec3 ourColor;"
        "in vec2 TexCoord;"
        "uniform sampler2D ourTexture;"
        "\n"
        "void main()\n"
        "{\n"
        "color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
        "}\n";
}

unsigned int GameEngine::Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader." << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
