#ifndef PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
#define PLAIN_ENGINE_PLAGLUTTEXTURE_HPP

// TODO: 動的リソース読み込み/解放機能の実装時に以下を対応する
//       - Resource → Image → Texture::Manager の通知チェーン
//       - Video → Texture::Manager の通知チェーン
//       現状は静的リソースのみ

#include <unordered_map>
#include "PLAGLUT.h"
#include "plain/core/primitive/PLAPRMType.hpp"

class PLAOBJImage;
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
  void SetParameters();
  void UploadData(const PLAUInt8* aData, GLsizei aWidth, GLsizei aHeight);

private:
  void Generate();
  void Delete();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::unordered_map<const PLAOBJImage*, PLAGLUTTexture*> _imageTextures;
    std::unordered_map<const PLAOBJVideo*, PLAGLUTTexture*> _videoTextures;

    Manager();

  public:
    static Manager* Instance() { return &_instance; }

    ~Manager();

    // Image texture management
    PLAGLUTTexture* GetOrCreate(const PLAOBJImage* aImage);

    // Video texture management
    void BindAndUpdate(const PLAOBJVideo* aVideo, const PLAOBJImage* aImage);

    void Clear();
  };
};

#endif //PLAIN_ENGINE_PLAGLUTTEXTURE_HPP
