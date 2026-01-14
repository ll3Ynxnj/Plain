#include "plain/glut/PLAGLUTTexture.hpp"
#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/object/PLAOBJVideo.hpp"

// PLAGLUTTexture //////////////////////////////////////////////////////////////

PLAGLUTTexture::PLAGLUTTexture(Type aType) :
  _type(aType)
{
  Generate();
}

PLAGLUTTexture::~PLAGLUTTexture()
{
  Delete();
}

void PLAGLUTTexture::Generate()
{
  glGenTextures(1, &_textureId);
}

void PLAGLUTTexture::Delete()
{
  if (_textureId != 0)
  {
    glDeleteTextures(1, &_textureId);
    _textureId = 0;
  }
}

void PLAGLUTTexture::Bind() const
{
  glBindTexture(GL_TEXTURE_2D, _textureId);
}

void PLAGLUTTexture::UploadData(const PLAUInt8* aData, GLsizei aWidth, GLsizei aHeight)
{
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aWidth, aHeight, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, aData);

  // Set default texture parameters (required for texture to render properly)
  // Default MIN_FILTER is GL_NEAREST_MIPMAP_LINEAR which requires mipmaps
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

// PLAGLUTTexture::Manager /////////////////////////////////////////////////////

PLAGLUTTexture::Manager PLAGLUTTexture::Manager::_instance = PLAGLUTTexture::Manager();

PLAGLUTTexture::Manager::Manager()
{
}

PLAGLUTTexture::Manager::~Manager()
{
  Clear();
}

PLAGLUTTexture* PLAGLUTTexture::Manager::ResolveTexture(const PLAObject* aKey,
                                                         const PLAOBJImage* aData)
{
  if (!aKey || !aData)
  {
    return nullptr;
  }

  PLAGLUTTexture* texture = nullptr;
  auto it = _textures.find(aKey);

  if (it != _textures.end())
  {
    texture = it->second;
    texture->Bind();

    // Check if data has been updated
    uint64_t dataRevision = aData->GetRevision();
    if (texture->GetCachedRevision() != dataRevision)
    {
      texture->UploadData(aData->GetResourceData(),
                          aData->GetSize().x, aData->GetSize().y);
      texture->SetCachedRevision(dataRevision);
    }
  }
  else
  {
    // Create new texture
    texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Image);
    texture->Bind();
    texture->UploadData(aData->GetResourceData(),
                        aData->GetSize().x, aData->GetSize().y);
    texture->SetCachedRevision(aData->GetRevision());

    _textures[aKey] = texture;
  }

  return texture;
}

PLAGLUTTexture* PLAGLUTTexture::Manager::GetTexture(const PLAOBJImage* aImage)
{
  if (!aImage)
  {
    return nullptr;
  }

  auto it = _imageTextures.find(aImage);
  if (it != _imageTextures.end())
  {
    it->second->Bind();
    return it->second;
  }

  const PLAUInt8* data = aImage->GetResourceData();
  PLASize width = aImage->GetSize().x;
  PLASize height = aImage->GetSize().y;

  PLAGLUTTexture* texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Image);
  texture->Bind();
  texture->UploadData(data, width, height);

  _imageTextures[aImage] = texture;

  return texture;
}

void PLAGLUTTexture::Manager::BindAndUpdate(const PLAOBJVideo* aVideo,
                                             const PLAOBJImage* aImage)
{
  if (!aVideo || !aImage)
  {
    return;
  }

  PLAGLUTTexture* texture = nullptr;
  auto it = _videoTextures.find(aVideo);

  if (it != _videoTextures.end())
  {
    texture = it->second;
    texture->Bind();
  }
  else
  {
    texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Video);
    texture->Bind();

    _videoTextures[aVideo] = texture;
  }

  texture->UploadData(aImage->GetResourceData(),
                      aImage->GetSize().x, aImage->GetSize().y);
}

void PLAGLUTTexture::Manager::Clear()
{
  for (auto& pair : _textures)
  {
    delete pair.second;
  }
  _textures.clear();

  // Legacy maps
  for (auto& pair : _imageTextures)
  {
    delete pair.second;
  }
  _imageTextures.clear();

  for (auto& pair : _videoTextures)
  {
    delete pair.second;
  }
  _videoTextures.clear();
}
