//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGTSCENE_HPP
#define ANHR_PLAAGTSCENE_HPP

#include "PLAAgent.hpp"
#include "Class/PLAScene.hpp"

class PLAAGTScene final : public PLAAgent
{
public:
  /// Agent is const method only.
  static PLAAGTScene *Create(PLAScene *aScene);

  virtual ~PLAAGTScene();

protected:
  PLAAGTScene(PLAScene *aScene);
};


#endif //ANHR_PLAAGTSCENE_HPP
