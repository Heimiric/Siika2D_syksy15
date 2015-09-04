#pragma once

#include "Text.h"
#include "ShaderManager.h"

namespace core
{
	class Siika2D;
}

namespace graphics
{
	/**
		Class for creating and drawing text.
	*/
	class TextManager
	{
		friend class core::Siika2D;
	public:
		/**
			Constructor.
			Creates shader for drawing text.
		*/
		TextManager(core::ResourceManager* resourceManager, ShaderManager* shaderManager, glm::vec2 displaySize);
		~TextManager();

		/**
			Creates Text object and returns it.
		*/
		Text* createText();

		/**
			Draws all created Text objects that have been properly initialized.
		*/
		void drawTexts();

	private:
		/**
			Loads shaders from files.
			Vertex shader from "vertexTextShader.glsl" and fragment shader from "fragmentTextShader.glsl".
		*/
		Shader* createShaders();

		/**
			Get attribute location for position and texture coordinates.
			Set attribute pointers.
		*/
		void setAttributes(GLint& positionLoc);

		/**
			Get color uniform location and set it's color value.
		*/
		void setColorUniform(GLint &colLoc);

		/**
			Get texture sampler location, generate texture for text and set texture parameters.
		*/
		void setTextureUniform(GLint& textureSampler, GLuint& texture); // Text needs it's own texture initialization because of reasons.

		/**
			Initializes FreeType.
		*/
		void initFreetype();


		core::ResourceManager* _resourceManager;
		FT_Library _library;
		ShaderManager* _shaderManager;
		Shader* _textShader;
		std::vector<Text*> _texts;
		glm::vec2 _displaySize;
		GLuint _program;
	};
}