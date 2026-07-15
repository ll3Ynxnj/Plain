#ifndef PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
#define PLAIN_ENGINE_PLAGLUTTEXTURE_HPP

// TODO: 動的リソース読み込み/解放機能の実装時に以下を対応する
//       - Resource → Texture::Manager の通知チェーン
//       - Video → Texture::Manager の通知チェーン
//       現状リソースは常駐前提。Image はキャッシュキーにしないため
//       動的な生成・破棄が可能（Telop / Pickup 等の短命レイヤー）

#include <unordered_map>
#include "PLAGLUT.h"
#include "plain/core/primitive/PLAPRMType.hpp"

class PLAOBJImage;
class PLAOBJResource;
class PLAOBJVideo;

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

public:
  PLAGLUTTexture(Type aType);
  ~PLAGLUTTexture();

  GLuint GetTextureId() const { return _textureId; }
  Type GetType() const { return _type; }

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

    // Keyed by the name-managed resident resource, NOT the image: images are
    // owned by their layers and die with them, so a dangling image pointer
    // could alias a later allocation and hit a stale cache entry (observed as
    // a dynamic layer rendering another layer's texture). Sharing one texture
    // per resource also deduplicates uploads across layers.
    std::unordered_map<const PLAOBJResource*, PLAGLUTTexture*> _imageTextures;
    std::unordered_map<const PLAOBJVideo*, PLAGLUTTexture*> _videoTextures;

    Manager();

  public:
    static Manager* Instance() { return &_instance; }

    ~Manager();

    // Image texture management
    PLAGLUTTexture* GetTexture(const PLAOBJImage* aImage);

    // Video texture management
    void BindAndUpdate(const PLAOBJVideo* aVideo, const PLAOBJImage* aImage);

    void Clear();
  };
};

#endif //PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
