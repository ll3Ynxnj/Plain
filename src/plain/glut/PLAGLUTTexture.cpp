#include "plain/glut/PLAGLUTTexture.hpp"
#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJImage.hpp"

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
  // Use gluBuild2DMipmaps to upload texture with mipmap generation
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, aWidth, aHeight,
                    GL_RGBA, GL_UNSIGNED_BYTE, aData);

  // Set texture parameters
  // Use trilinear filtering (GL_LINEAR_MIPMAP_LINEAR) for smooth minification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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

PLAGLUTTexture* PLAGLUTTexture::Manager::ResolveTexture(const PLAOBJImage* aImage)
{
  if (!aImage)
  {
    return nullptr;
  }

  PLAGLUTTexture* texture = nullptr;
  auto it = _textures.find(aImage);

  if (it != _textures.end())
  {
    texture = it->second;
    texture->Bind();
  }
  else
  {
    texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Image);
    texture->Bind();
    texture->UploadData(aImage->GetResourceData(),
                        aImage->GetSize().x, aImage->GetSize().y);

    _textures[aImage] = texture;
  }

  return texture;
}

PLAGLUTTexture* PLAGLUTTexture::Manager::UpdateTexture(const PLAObject* aKey,
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
    texture = new PLAGLUTTexture(PLAGLUTTexture::Type::Image);
    texture->Bind();
    texture->UploadData(aData->GetResourceData(),
                        aData->GetSize().x, aData->GetSize().y);
    texture->SetCachedRevision(aData->GetRevision());

    _textures[aKey] = texture;
  }

  return texture;
}

void PLAGLUTTexture::Manager::Clear()
{
  for (auto& pair : _textures)
  {
    delete pair.second;
  }
  _textures.clear();
}
