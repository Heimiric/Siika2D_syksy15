#pragma once
#include "../graphics/SpriteManager.h"
#include "../graphics/Camera.h"
#include "Siika2D.h"
#include <vector>
namespace core
{
	class Scene
	{
		friend class SceneManager;
	public:
		Scene(graphics::ShaderManager * sMngr, graphics::BufferManager * bMngr, core::ResourceManager * rMngr, glm::vec2 size)
		{ 
			_sprtMngr = new graphics::SpriteManager(sMngr,bMngr); 
			_camera = new graphics::Camera();
			_txtMngr = new graphics::TextManager(rMngr,sMngr,size);
			_camera->setCameraPosition(glm::vec2(0, 0));
		}
		Scene(graphics::SpriteManager * sMngrm, graphics::Camera * cmr, graphics::TextManager * txtMngr) :_sprtMngr(sMngrm), _camera(cmr), _txtMngr(txtMngr){};
		~Scene(){ delete _sprtMngr; delete _camera; delete _txtMngr; }
		void use()
		{
			Siika2D::UI()->_spriteManager = _sprtMngr;
			//Siika2D::UI()->_camera = _camera;
			Siika2D::UI()->_textManager = _txtMngr;
		}

	private:
		graphics::SpriteManager * _sprtMngr;
		graphics::Camera * _camera;
		graphics::TextManager * _txtMngr;
	};

	class SceneManager
	{
	public:
		/**
			Creates scenemanager and sets current scene as first scene
			It can be accesed by getScene(0);
		*/
		SceneManager()
		{
			graphics::SpriteManager * sMngr = Siika2D::UI()->_spriteManager;
			graphics::Camera * cmr = Siika2D::UI()->_camera;
			graphics::TextManager * txtMngr = Siika2D::UI()->_textManager;
			_scenes.push_back(new Scene(sMngr, cmr,txtMngr));
		};
		/**
			Creates a new scene and start using it in Siika
			Returns a pointer to the created scene
		*/
		Scene * newScene()
		{
			Scene * nScene = new Scene(Siika2D::UI()->_shaderManager, Siika2D::UI()->_bufferManager,&Siika2D::UI()->_resourceManager, Siika2D::UI()->_graphicsContext->getDisplaySize());
			_scenes.push_back(nScene);
			nScene->use();
			//Siika2D::UI()->_spriteManager = nScene->_sprtMngr;
			//Siika2D::UI()->_camera = nScene->_camera;
			return nScene;
		}
		Scene * getScene(int i)
		{ 
			return _scenes[i]; 
		}

		bool useScene(int i)
		{
			if (_scenes.size() < i)
				return false;
			_scenes[i]->use();
			return true;
		}

		~SceneManager()
		{
			for (Scene * sc : _scenes)
			{
				delete sc;
			}
			_scenes.clear();
		}
	private:
		std::vector<Scene*> _scenes;

	};
}
