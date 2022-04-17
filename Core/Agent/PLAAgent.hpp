//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP

#include "Core/Class/PLAObject.hpp"

class PLAAgent: public PLAObject
{
  PLAObject *_object = nullptr;

public:
  const PLAObject *GetObject() const { return _object; }
  PLAId GetObjectId() const { return _object->GetObjectId(); }

protected:
  PLAAgent(PLAObject *aObject);
  virtual ~PLAAgent();
};


#endif //ANHR_PLAAGENT_HPP
