//
// Created by Kentaro Kawai on 2023/05/20.
//

#include "PLAOBJPhase.hpp"

#include "Agent/PLAAGTPhase.hpp"

PLAOBJPhase *PLAOBJPhase::Create()
{
  PLAOBJPhase *phase = new PLAOBJPhase();
  phase->Bind();
  return phase;
}

PLAOBJPhase *PLAOBJPhase::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Phase, aName);
  return static_cast<PLAOBJPhase *>(object);
}

PLAOBJPhase *PLAOBJPhase::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Phase, aId);
  return static_cast<PLAOBJPhase *>(object);
}

PLAOBJPhase::PLAOBJPhase() :
  PLAObject(PLAObjectType::Phase)
{

}

PLAOBJPhase::PLAOBJPhase(PLAString aName) :
  PLAObject(PLAObjectType::Phase, aName)
{

}

PLAOBJPhase::~PLAOBJPhase()
{

}

void PLAOBJPhase::Init()
{

}

PLAAGTPhase PLAOBJPhase::AssignAgent() {
  return PLAAGTPhase(this);
}

void PLAOBJPhase::PrintPhases() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  auto phases = _phases;
  while (!phases.empty())
  {
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
    auto phase = phases.top();
    phase->PrintPhases();
    phases.pop();
  }
  --indentLevel;
}
