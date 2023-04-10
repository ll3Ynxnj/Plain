//
// Created by Kentaro Kawai on 2023/04/07.
//

#include "PLAAGTModel.hpp"

PLAAGTModel *PLAAGTModel::Create(PLAOBJModel *aModel)
{
  auto agent = new PLAAGTModel(aModel);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTModel::PLAAGTModel(PLAOBJModel *aModel) :
  PLAOBJAgent(aModel)
{

}

PLAAGTModel::~PLAAGTModel() noexcept
{

}
