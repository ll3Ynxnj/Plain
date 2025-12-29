#ifndef PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP
#define PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP

#include <unordered_map>
#include "PLAGLUT.h"

class PLAOBJImage;
class PLAOBJVideoClip;

class PLAGLUTTextureManager
{
  static PLAGLUTTextureManager _instance;

  std::unordered_map<const PLAOBJImage*, GLuint> _imageCache;
  std::unordered_map<const PLAOBJVideoClip*, GLuint> _videoCache;

  PLAGLUTTextureManager();

public:
  static PLAGLUTTextureManager* Instance() { return &_instance; }

  ~PLAGLUTTextureManager();

  // Static image: texture created once, cached permanently
  GLuint GetOrCreateTexture(const PLAOBJImage* aImage);
  void OnImageReleased(const PLAOBJImage* aImage);

  // VideoClip: texture created once per clip, data updated each frame
  void BindAndUpdateVideoTexture(const PLAOBJVideoClip* aVideoClip,
                                  const PLAOBJImage* aImage);
  void OnVideoClipReleased(const PLAOBJVideoClip* aVideoClip);

  void Clear();
};

#endif //PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP
