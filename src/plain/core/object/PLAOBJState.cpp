//
// Created by Kentaro Kawai on 2021/07/29.
//

#include "plain/core/object/PLAOBJState.hpp"
#include "plain/core/agent/PLAAGTState.hpp"
#include "plain/core/agent/PLAAGTModel.hpp"

PLAOBJState *PLAOBJState::Create()
{
  PLAOBJState *state = new PLAOBJState();
  state->Init();
  state->Bind();
  return state;
}

PLAOBJState *PLAOBJState::Create(const PLAString &aName)
{
  PLAOBJState *state = new PLAOBJState(aName);
  state->Init();
  state->Bind();
  return state;
}

PLAOBJState *PLAOBJState::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::State, aName);
  return static_cast<PLAOBJState *>(object);
}

PLAOBJState *PLAOBJState::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::State, aId);
  return static_cast<PLAOBJState *>(object);
}

PLAOBJState::PLAOBJState() :
  PLAObject(PLAObjectType::State)
{
  _context = PLAOBJModel::Create();
}

PLAOBJState::PLAOBJState(const PLAString &aName) :
  PLAObject(PLAObjectType::State, aName)
{
  _context = PLAOBJModel::Create(aName + "::Context");
}

PLAOBJState::~PLAOBJState()
{
  delete(_context);
  _context = nullptr;
}

void PLAOBJState::Init()
{
  //_context->Init();
}

PLAAGTState PLAOBJState::AssignAgent() {
  return PLAAGTState(this);
}

void PLAOBJState::AddModel(PLAOBJModel *aModel)
{
  GRA_PRINT("AddModel : %s\n", aModel->GetObjectDescription().c_str());

  PLAString actorName = aModel->GetObjectName();
  if (actorName == kPLAStrUndefined) {
    GRA_TRACE("Object name is undefined");
  }
  _context->AddModel(aModel);
}

void PLAOBJState::PrintModels() const
{
  GRA_PRINT("");
  _context->PrintModels();
}

