// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJDECODER_HPP
#define PLAIN_ENGINE_PLAOBJDECODER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/PLADecoderType.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include <vector>

class PLAOBJDecoder : public PLAObject,
                      private GRAOBJBinder<PLAOBJDecoder>::Item
{
  using Binder = GRAOBJBinder<PLAOBJDecoder>;

protected:
  bool _isInitialized = false;

  PLAOBJDecoder(const PLAString &aName);

public:
  using PLADecoderItem  = GRAOBJBinder<PLAOBJDecoder>::Item;
  using PLADecoderError = GRAOBJBinder<PLAOBJDecoder>::Error;

  static PLAOBJDecoder *Create(PLADecoderType aType,
                               const PLAString &aName = "Decoder");
  static PLAOBJDecoder *Decoder(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
  virtual ~PLAOBJDecoder();

  virtual bool Initialize() = 0;
  virtual bool Decode(const std::vector<PLAUInt8> &aInput,
                      std::vector<PLAUInt8> &aOutput) = 0;

  bool IsInitialized() const { return _isInitialized; }

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager : public GRAOBJBinder<PLAOBJDecoder>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void Init();
  };
};

#endif // PLAIN_ENGINE_PLAOBJDECODER_HPP
