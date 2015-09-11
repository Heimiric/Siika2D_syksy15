#pragma once
#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include "..\core\ErrorHandler.h"
#include "Camera.h"
#include <assert.h>
#include <string>
namespace graphics
{
	enum SHADER_ATTRIBUTE { unknown = -1, position, color, texture};

	class Shader
	{
		friend class ShaderManager;
		/***
		Shader class includes fragment and vertex shaders. Uses default shader code if shader code is not provided in constructor.
		Default attribute names are Position: "position" Color: "color" TextureCoordinate: "texture"
		*/
	public:
		const GLuint getProgram(){ return _program; }
		///calls glUseProgram() and enables shader attributes. This is for default shader only, also gets and enables default shader atributes
		void use(bool toUse = true);
		bool hasColor(){ return _color; }
		bool hasTexture(){ return _texture; }
		GLint _windowLocation;

		bool _color, _texture;
	private:
		///Gets and activates texture sampler
		void useSampler();
		///Shader must be created using ShaderManager::createShader()
		Shader(Camera * camera = nullptr, bool color = false, bool texture = false);
		Shader(const GLchar * fragmentSource, const GLchar * vertexSource, Camera * camera = nullptr, bool color = false, bool texture = false);
		~Shader();
		void setColor(bool toSet){ _color = toSet; }
		void setTexture(bool toSet){ _texture = toSet; }

		bool compileShaders();
		bool linkProgram();
		void init();
		bool _default, _valid;
		std::string getProgramInfoLog(GLuint handle);
		std::string getShaderInfoLog(GLuint handle);
		
		GLuint _fragHandle, _vertHandle, _samplerHandle;
		const GLchar * _fragSource;
		const GLchar * _vertSource;
		GLuint _program;
		GLchar * _posString = "position";
		GLchar * _colString = "color";
		GLchar * _texString = "texture";
		GLchar * _windowString = "window";
		Camera * _camera;
	};
}