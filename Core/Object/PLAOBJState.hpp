#ifndef PLAIN_ENGINE_PLAOBJSTATE_HPP
#define PLAIN_ENGINE_PLAOBJSTATE_HPP

#include "PLAObject.hpp"
#include "Object/Model/PLAOBJModel.hpp"

class PLAOBJState final: public PLAObject
{
  PLAOBJModel *_context = nullptr;

protected:
  PLAOBJState();

public:
  static PLAOBJState *Create();

  ~PLAOBJState();

  void Init();

  void AddModel(PLAOBJModel *aModel);
  void PrintModels() const;
};

#endif //PLAIN_ENGINE_PLAOBJSTATE_HPP
