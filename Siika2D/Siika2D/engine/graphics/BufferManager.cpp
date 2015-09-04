#include "BufferManager.h"

using namespace graphics;

BufferManager::BufferManager() :_indexBuffer(GL_ELEMENT_ARRAY_BUFFER), _vertexBuffer(GL_ARRAY_BUFFER)
{
	s2d_info("BUFFERMANAGER CREATED");
	_positionId = -1;
	_colorId = -1;
	_textureId = -1;
}

void BufferManager::setAttributes(GLint pos, GLint col, GLint textr)
{
	GLint err = glGetError();
	s2d_assert(err == 0);

	_positionId = pos;
	_colorId = col;
	_textureId = textr;

	//Position length
	_strideLength = 2 * sizeof(GLfloat);

	//Color length
	if (col != -1)
		_strideLength += 4 * sizeof(GLfloat);

	//Texture length
	if (textr != -1)
		_strideLength += 2 * sizeof(GLfloat);

	err = glGetError();
	s2d_assert(err == 0);

}

void BufferManager::addVertices(GLfloat* vertices, GLsizei size)
{
	_vertexBuffer.setBufferData(vertices, size);
}

void BufferManager::addIndices(GLint* indices, GLsizei size)
{
	_indexBuffer.setBufferData(indices, size);
}
void BufferManager::clear()
{
	_vertices.clear();
	_indices.clear();
}
void BufferManager::addRectangle(glm::vec2* pos, glm::vec2* textr, Color* col)
{
	GLint err = glGetError();
	s2d_assert(err == 0);

	for (int i = 0; i < 4; i++)
	{
		_vertices.push_back(pos[i].x);
		_vertices.push_back(pos[i].y);

		if (textr != nullptr)
		{
			_vertices.push_back(textr[i].x);
			_vertices.push_back(textr[i].y);
		}

		if (col != nullptr)
		{
			glm::vec4 glColor = col->getGLColor();

			_vertices.push_back(glColor.r);
			_vertices.push_back(glColor.g);
			_vertices.push_back(glColor.b);
			_vertices.push_back(glColor.a);

		}
	}

	err = glGetError();
	s2d_assert(err == 0);

	int indicesSize = _indices.size();
	int startingIndex = (indicesSize / 6) * 2;
	_indices.push_back(indicesSize-startingIndex);
	_indices.push_back(indicesSize+1-startingIndex);
	_indices.push_back(indicesSize + 3 - startingIndex);
	_indices.push_back(indicesSize + 1 - startingIndex);
	_indices.push_back(indicesSize + 2 - startingIndex);
	_indices.push_back(indicesSize + 3 - startingIndex);

	err = glGetError();
	s2d_assert(err == 0);
}

void BufferManager::draw()
{
	bindBuffers();
	setAttribPointers();

	GLint err = glGetError();
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	err = glGetError();
	s2d_assert(err == 0);


	unbindBuffers();
}

void BufferManager::setAttribPointers()
{
	GLint err = glGetError();
	glVertexAttribPointer(_positionId, 2, GL_FLOAT, GL_FALSE, _strideLength, reinterpret_cast<GLvoid*>(0));

	if (_textureId != -1)
		glVertexAttribPointer(_textureId, 2, GL_FLOAT, GL_FALSE, _strideLength, reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));

	if (_colorId != -1)
	{
		if (_textureId != -1)
			glVertexAttribPointer(_colorId, 4, GL_FLOAT, GL_FALSE, _strideLength, reinterpret_cast<GLvoid*>(4 * sizeof(GLfloat)));
		else
			glVertexAttribPointer(_colorId, 4, GL_FLOAT, GL_FALSE, _strideLength, reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	}

	err = glGetError();
	s2d_assert(err == 0);

}

void BufferManager::bindBuffers()
{
	if (_vertices.size() != 0)
		_vertexBuffer.setBufferData(_vertices.data(), _vertices.size() * sizeof(GLfloat));

	if (_indices.size() != 0)
		_indexBuffer.setBufferData(_indices.data(), _indices.size() * sizeof(GLint));

	_vertexBuffer.bindBuffer();
	_indexBuffer.bindBuffer();

	GLint err = glGetError();
	s2d_assert(err == 0);
}

void BufferManager::unbindBuffers()
{
	_vertexBuffer.unbindBuffer();
	_indexBuffer.unbindBuffer();
}

BufferManager::~BufferManager()
{
}
