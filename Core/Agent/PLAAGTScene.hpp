//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGTSCENE_HPP
#define ANHR_PLAAGTSCENE_HPP

#include "PLAAgent.hpp"
#include "Object/PLAOBJScene.hpp"

class PLAAGTScene final : public PLAAgent
{
public:
  /// Agent is const method only.
  //static PLAAGTScene *Create(PLAOBJScene *aScene);

  explicit PLAAGTScene(PLAOBJScene *aScene);
  virtual ~PLAAGTScene() noexcept;

protected:
  const PLAOBJScene *GetStage() const
  { return static_cast<const PLAOBJScene *>(this->GetOwner()); }
  PLAOBJScene *RefStage() const
  { return static_cast<PLAOBJScene *>(this->RefOwner()); }
};


#endif //ANHR_PLAAGTSCENE_HPP
