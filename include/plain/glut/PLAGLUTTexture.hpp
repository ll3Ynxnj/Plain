#ifndef PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
#define PLAIN_ENGINE_PLAGLUTTEXTURE_HPP

// TODO: 動的リソース読み込み/解放機能の実装時に以下を対応する
//       - Resource → Image → Texture::Manager の通知チェーン
//       - Video → Texture::Manager の通知チェーン
//       現状は静的リソースのみ

#include <unordered_map>
#include "PLAGLUT.h"
#include "plain/core/primitive/PLAPRMType.hpp"

class PLAObject;
class PLAOBJImage;

class PLAGLUTTexture
{
public:
  enum class Type
  {
    Image,
    Video,

    None
  };

private:
  GLuint _textureId = 0;
  Type _type = Type::None;
  uint64_t _cachedRevision = 0;

public:
  PLAGLUTTexture(Type aType);
  ~PLAGLUTTexture();

  GLuint GetTextureId() const { return _textureId; }
  Type GetType() const { return _type; }
  uint64_t GetCachedRevision() const { return _cachedRevision; }
  void SetCachedRevision(uint64_t aRevision) { _cachedRevision = aRevision; }

  void Bind() const;
  void UploadData(const PLAUInt8* aData, GLsizei aWidth, GLsizei aHeight);

private:
  void Generate();
  void Delete();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::unordered_map<const PLAObject*, PLAGLUTTexture*> _textures;

    Manager();

  public:
    static Manager* Instance() { return &_instance; }

    ~Manager();

    // Static content - resolve and cache texture
    PLAGLUTTexture* ResolveTexture(const PLAOBJImage* aImage);

    // Dynamic content - resolve and update texture
    PLAGLUTTexture* UpdateTexture(const PLAObject* aKey, const PLAOBJImage* aData);

    void Clear();
  };
};

#endif //PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
