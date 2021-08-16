//
// Created by Kentaro Kawai on 2021/08/13.
//

#ifndef ANHR_PLANODE_HPP
#define ANHR_PLANODE_HPP

#include <vector>
#include "Type/PLAType.hpp"
#include "PLAObject.hpp"

class PLANode: public PLAObject
{
  PLAInt _steps = 0;
  PLAInt _length = 0;
  std::vector<PLANode *>_node = std::vector<PLANode *>();

public:
  static PLANode *Create(PLAInt aLength);

  PLANode(PLAInt aLength);
  ~PLANode();

  void Update();

  void AddNode(PLANode *aNode);

  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };
};

#endif //ANHR_PLANODE_HPP
