#ifndef PLAIN_ENGINE_PLAOBJSTATE_HPP
#define PLAIN_ENGINE_PLAOBJSTATE_HPP

#include "Core/Object/PLAObject.hpp"
#include "Core/Object/Model/PLAOBJModel.hpp"

class PLAAGTState;

class PLAOBJState final: public PLAObject
{
  PLAOBJModel *_context = nullptr;

protected:
  PLAOBJState();
  PLAOBJState(const PLAString &aName);

public:
  static PLAOBJState *Create();
  static PLAOBJState *Create(const PLAString &aName);
  static PLAOBJState *Object(const PLAString &aName);
  static PLAOBJState *Object(PLAId aId);

  ~PLAOBJState();

  void Init();

  PLAAGTState AssignAgent();

  void AddModel(PLAOBJModel *aModel);
  void PrintModels() const;
};

#endif //PLAIN_ENGINE_PLAOBJSTATE_HPP
