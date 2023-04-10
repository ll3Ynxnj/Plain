//
// Created by Kentaro Kawai on 2021/07/29.
//

#include "PLAOBJState.hpp"
#include "Agent/PLAAGTState.hpp"
#include "Agent/PLAAGTModel.hpp"

PLAOBJState *PLAOBJState::Create()
{
  PLAOBJState *state = new PLAOBJState();
  state->Bind();
  return state;
}

PLAOBJState::PLAOBJState() :
  PLAObject(PLAObjectType::Stage)
{
  _context = PLAOBJModel::Create();
  _context->SetObjectName("StateContext");
}

PLAOBJState::~PLAOBJState()
{
  delete(_context);
  _context = nullptr;
}

void PLAOBJState::Init()
{
  _context->Init();
}

void PLAOBJState::AddModel(PLAOBJModel *aModel)
{
  GRA_PRINT("AddModel : %s\n", aModel->GetObjectDescription().c_str());

  PLAString actorName = aModel->GetObjectName();
  if (actorName == kPLAStrUndefined) {
    GRA_TRACE("");
  }
  _context->AddModel(aModel);
}

void PLAOBJState::PrintModels() const
{
  GRA_PRINT("");
  _context->PrintModels();
}

