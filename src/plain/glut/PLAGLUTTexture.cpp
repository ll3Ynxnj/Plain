#include "plain/glut/PLAGLUTTexture.hpp"
#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/object/PLAOBJVideo.hpp"
#include <grain/grain.h>

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

void PLAGLUTTexture::SetParameters()
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void PLAGLUTTexture::UploadData(const PLAUInt8* aData, GLsizei aWidth, GLsizei aHeight)
{
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aWidth, aHeight, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, aData);
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

PLAGLUTTexture* PLAGLUTTexture::Manager::GetOrCreate(const PLAOBJImage* aImage)
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

  GRA_PRINT("Texture::Manager: Creating image texture (image=%p)\n", aImage);

  PLAGLUTTexture* texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Image);
  texture->Bind();
  texture->SetParameters();
  texture->UploadData(aImage->GetResourceData(),
                      aImage->GetSize().x, aImage->GetSize().y);

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
    GRA_PRINT("Texture::Manager: Creating video texture (video=%p)\n", aVideo);

    texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Video);
    texture->Bind();
    texture->SetParameters();

    _videoTextures[aVideo] = texture;
  }

  texture->UploadData(aImage->GetResourceData(),
                      aImage->GetSize().x, aImage->GetSize().y);
}

void PLAGLUTTexture::Manager::Clear()
{
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
