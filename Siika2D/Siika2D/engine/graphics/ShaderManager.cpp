#include "ShaderManager.h"
using namespace graphics;


void ShaderManager::useShader(bool color, bool texture)
{
	if(!_currentShader)
	{
		//Gets default shader
		if(_defaultIndx == -1)
		{
			_currentShader = new Shader(_camera,color,texture);
			//_camera->initialize();
			_shaders.push_back(_currentShader);
			_defaultIndx = _shaders.size()-1;
			
		}
		else  //should never come here
		{
			//s2d_error("No current shader but default shader loaded: ShaderManager::useShader()");
			_currentShader = _shaders[_defaultIndx];
		}
	}
	s2d_assert(_currentShader);
	//_camera->useProjection(_currentShader);

}
void ShaderManager::useDefaultShader(bool color, bool texture)
{
	Shader * shdr = new Shader(_camera,color, texture);
	Shader * found = findShader(shdr->_vertSource, shdr->_fragSource);
	if(found)
	{
		_currentShader = found;
		useShader();
		delete shdr;
	}
	else
	{
		_shaders.push_back(shdr);
		_currentShader = shdr;
	}
}
Shader * ShaderManager::createShader(char * vertPath, char * fragPath)
{ 
	std::string * fragSource;
	std::string * vertSource;

	vertSource = _rmngr->loadTextFile(vertPath);
	fragSource = _rmngr->loadTextFile(fragPath);

	Shader * newShdr = findShader(vertSource->c_str(), fragSource->c_str());
	if(!newShdr)
	{
		newShdr = new Shader(fragSource->c_str(), vertSource->c_str(),_camera);
		if(newShdr->_valid)
			_shaders.push_back(newShdr); 
		else // Compile or link failed infolog in logcat
		{
			delete newShdr;
			newShdr = nullptr;
		}
	}
	_currentShader = newShdr;
	return _currentShader; 
}
Shader * ShaderManager::findShader(const char * vertSource, const char * fragSource)
{
	for(std::vector<Shader*>::iterator it = _shaders.begin(); it != _shaders.end(); it++)
	{
		Shader * shdr = *it;
		if(strcmp(shdr->_vertSource,vertSource) == 0)
		{
			if(strcmp(shdr->_fragSource, fragSource) == 0)
				return shdr;
		}
	}
	return nullptr;
}

void ShaderManager::initializeProjection()
{
	/*_currentShader->use();
	glm::mat4 proj = glm::ortho(0.0f, _windowSize.x, _windowSize.y, 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(_currentShader->_projectionLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&proj));
	_currentShader->use(false);*/
}

void ShaderManager::ReinitializeShaders()
{
	for (unsigned int i = 0; i < _shaders.size(); i++)
	{
		_shaders[i]->compileShaders();
		_shaders[i]->linkProgram();
	}
}
