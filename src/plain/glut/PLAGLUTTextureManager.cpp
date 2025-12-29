#include "plain/glut/PLAGLUTTextureManager.hpp"
#include "plain/core/object/PLAOBJImage.hpp"
#include <grain/grain.h>

PLAGLUTTextureManager PLAGLUTTextureManager::_instance = PLAGLUTTextureManager();

PLAGLUTTextureManager::PLAGLUTTextureManager()
{
}

PLAGLUTTextureManager::~PLAGLUTTextureManager()
{
  Clear();
}

GLuint PLAGLUTTextureManager::GetOrCreateTexture(const PLAOBJImage* aImage)
{
  if (!aImage)
  {
    return 0;
  }

  auto it = _cache.find(aImage);
  if (it != _cache.end())
  {
    glBindTexture(GL_TEXTURE_2D, it->second);
    return it->second;
  }

  GRA_PRINT("TextureManager: Creating texture (image=%p)\n", aImage);
  GLuint textureId = 0;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  const PLAUInt8* textureData = aImage->GetResourceData();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               aImage->GetSize().x, aImage->GetSize().y, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, textureData);

  aImage->SetOnReleasedCallback([this, aImage]() {
    this->OnImageReleased(aImage);
  });

  _cache[aImage] = textureId;

  return textureId;
}

void PLAGLUTTextureManager::OnImageReleased(const PLAOBJImage* aImage)
{
  auto it = _cache.find(aImage);
  if (it != _cache.end())
  {
    GRA_PRINT("TextureManager: Deleting texture (image=%p, textureId=%u)\n", aImage, it->second);
    glDeleteTextures(1, &it->second);
    _cache.erase(it);
  }
}

void PLAGLUTTextureManager::Clear()
{
  for (auto& pair : _cache)
  {
    glDeleteTextures(1, &pair.second);
  }
  _cache.clear();
}
