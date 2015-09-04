#pragma once
//#include "../core/ResourceManager.h"
#include "GraphicsContext.h"
#include "SpriteManager.h"
#include "TextureManager.h"

namespace core
{
	class Siika2D;
}

namespace graphics
{
	class Graphics : public SpriteManager, public TextureManager, public GraphicsContext
	{
		friend class core::Siika2D;
		
	public:

		graphics::ShaderManager *SHADING;

	private:
		
		/**
			Create Graphics context, buffer- and shadermanagers
		*/
		Graphics(android_app* application, core::ResourceManager* resourceManager);
		void clearGraphics();
		~Graphics();
	};
}
