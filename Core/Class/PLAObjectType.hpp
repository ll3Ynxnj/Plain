#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "Type/PLAVector.hpp"

enum class PLAObjectType : PLAInt
{
  App,
  Input,
  Scene,
  Stage,
  Actor,
  Layer,
  Style,
  Image,
  Error,
  Node,
  NodeThread,
  Resource,
  Renderer,
  ImageClip,

  LYRTileDataSource,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

static const char *kPLAObjectTypeName[static_cast<PLAInt>(PLAObjectType::kNumberOfItems)] = {
  "App",
  "Input",
  "Scene",
  "Stage",
  "Actor",
  "Layer",
  "Style",
  "Image",
  "Error",
  "Node",
  "NodeThread",
  "Resource",
  "Renderer",
  "ImageClip",

  "LYRTileDataSource",
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
