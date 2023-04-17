#ifndef PLAIN_ENGINE_PLAOBJSTATE_HPP
#define PLAIN_ENGINE_PLAOBJSTATE_HPP

#include "PLAObject.hpp"
#include "Object/Model/PLAOBJModel.hpp"

class PLAAGTState;

class PLAOBJState final: public PLAObject
{
  PLAOBJModel *_context = nullptr;

protected:
  PLAOBJState();

public:
  static PLAOBJState *Create();
  static PLAOBJState *Object(const PLAString &aName);
  static PLAOBJState *Object(PLAId aId);

  ~PLAOBJState();

  void Init();

  PLAAGTState AssignAgent();

  void AddModel(PLAOBJModel *aModel);
  void PrintModels() const;
};

#endif //PLAIN_ENGINE_PLAOBJSTATE_HPP
