#pragma once
#include "Shader.h"
#include "../core/ErrorHandler.h"
#include "../core/ResourceManager.h"
#include "Camera.h"
#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <vector>
#include <map>

namespace core
{
	class Siika2D;
}


namespace graphics
{
	
	class ShaderManager
	{
		/***
			Class for managing and loading shaders
			Default values for shader attributes are: "position", "color", "texture" 
			and they will be used unless new values are set with either setAtrib or setAtribs

			To use default shader 
			1) call useShader()
			
			To use custom shaders 
			1) call createShader(vertexshaderPath, fragmentShaderPath)
			2) call useShader()

			If colors or textures are needed use shader::setColor and shader::setTexture

		*/

		friend class core::Siika2D;
		friend class SpriteManager;
	public:
		

		/**
			Loads shader code with resourceManager. 
			If shader attribute values are not set default ones will be used. 
			Returns nullptr if compliling or linking fails infolog in logcat
		*/
		Shader * createShader(char * vertPath, char * fragPath);
		
		/**Compiles shaders links program for _currentShader. 
		If there is no _currentShaders it will create it from default shaders with given parameters
		On subsequent when a shader has been made it will call _currentShader::useShader();
		*/
		void useShader(bool color = true, bool texture = false);
		//Gets current shader
		Shader * getShader(){return _currentShader;}
		/** Gets a default shader with the given parameters and sets it as currentShader must call useShader to use it.
		
		*/
		void useDefaultShader(bool color, bool texture);
		///Sets the shader to be used by useShader()
		void setCurrentShader(Shader * shaderToUse){ _currentShader = shaderToUse; }
	protected:
		ShaderManager(core::ResourceManager * resMngr, glm::vec2 windowSize, Camera *camera) :_rmngr(resMngr),_windowSize(windowSize), _currentShader(nullptr), _defaultIndx(-1),_camera(camera){
			s2d_info("SHADER MANAGER CREATED");

		};

		void initializeProjection();
		~ShaderManager();// { _shaders.empty(); }
		//Finds already created shader in _shaders
		Shader * findShader(const char * vertSource, const char * fragSource);
		//Reinitializes shaders
		void ReinitializeShaders();

		Camera * _camera;
		int _defaultIndx;
		Shader * _currentShader;
		glm::vec2 _windowSize;
		std::vector<Shader*> _shaders;
		std::map<SHADER_ATTRIBUTE, char*> _shaderAtribs;
		core::ResourceManager * _rmngr;
	};
}