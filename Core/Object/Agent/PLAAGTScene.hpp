//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGTSCENE_HPP
#define ANHR_PLAAGTSCENE_HPP

#include "PLAOBJAgent.hpp"
#include "Object/PLAOBJScene.hpp"

class PLAAGTScene final : public PLAOBJAgent
{
public:
  /// Agent is const method only.
  static PLAAGTScene *Create(PLAOBJScene *aScene);

  virtual ~PLAAGTScene() noexcept;

protected:
  explicit PLAAGTScene(PLAOBJScene *aScene);
};


#endif //ANHR_PLAAGTSCENE_HPP
