#ifndef PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP
#define PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP

#include <unordered_map>
#include "PLAGLUT.h"

class PLAOBJImage;

class PLAGLUTTextureManager
{
  static PLAGLUTTextureManager _instance;

  std::unordered_map<const PLAOBJImage*, GLuint> _cache;

  PLAGLUTTextureManager();

public:
  static PLAGLUTTextureManager* Instance() { return &_instance; }

  ~PLAGLUTTextureManager();

  GLuint GetOrCreateTexture(const PLAOBJImage* aImage);
  void OnImageReleased(const PLAOBJImage* aImage);
  void Clear();
};

#endif //PLAIN_ENGINE_PLAGLUTTEXTUREMANAGER_HPP
