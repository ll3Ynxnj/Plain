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

  auto it = _imageCache.find(aImage);
  if (it != _imageCache.end())
  {
    glBindTexture(GL_TEXTURE_2D, it->second);
    return it->second;
  }

  GRA_PRINT("TextureManager: Creating image texture (image=%p)\n", aImage);
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

  _imageCache[aImage] = textureId;

  return textureId;
}

void PLAGLUTTextureManager::OnImageReleased(const PLAOBJImage* aImage)
{
  auto it = _imageCache.find(aImage);
  if (it != _imageCache.end())
  {
    GRA_PRINT("TextureManager: Deleting image texture (image=%p, textureId=%u)\n",
              aImage, it->second);
    glDeleteTextures(1, &it->second);
    _imageCache.erase(it);
  }
}

void PLAGLUTTextureManager::BindAndUpdateVideoTexture(
  const PLAOBJVideoClip* aVideoClip, const PLAOBJImage* aImage)
{
  if (!aVideoClip || !aImage)
  {
    return;
  }

  auto it = _videoCache.find(aVideoClip);
  GLuint textureId;

  if (it != _videoCache.end())
  {
    textureId = it->second;
    glBindTexture(GL_TEXTURE_2D, textureId);
  }
  else
  {
    GRA_PRINT("TextureManager: Creating video texture (videoClip=%p)\n", aVideoClip);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    _videoCache[aVideoClip] = textureId;
  }

  const PLAUInt8* textureData = aImage->GetResourceData();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               aImage->GetSize().x, aImage->GetSize().y, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, textureData);
}

void PLAGLUTTextureManager::OnVideoClipReleased(const PLAOBJVideoClip* aVideoClip)
{
  auto it = _videoCache.find(aVideoClip);
  if (it != _videoCache.end())
  {
    GRA_PRINT("TextureManager: Deleting video texture (videoClip=%p, textureId=%u)\n",
              aVideoClip, it->second);
    glDeleteTextures(1, &it->second);
    _videoCache.erase(it);
  }
}

void PLAGLUTTextureManager::Clear()
{
  for (auto& pair : _imageCache)
  {
    glDeleteTextures(1, &pair.second);
  }
  _imageCache.clear();

  for (auto& pair : _videoCache)
  {
    glDeleteTextures(1, &pair.second);
  }
  _videoCache.clear();
}
