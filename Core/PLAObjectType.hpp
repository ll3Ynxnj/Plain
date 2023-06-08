#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "Primitive/PLAPRMVector.hpp"

enum class PLAObjectType : PLAInt
{
  App,

  Input,
  Agent,

  Scene,
  State,
  Stage,

  Phase,
  Model,
  Actor,

  Layer,
  Style,

  Image,
  Error,

  Timeline,
  TimelineNode,

  Resource,

  Renderer,
  ImageClip,
  LYRTileDataSource,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

/// CAUTION: This array must be synchronized with PLAObjectType. ///////////////
static const char *kPLAObjectTypeName[static_cast<size_t>(PLAObjectType::kNumberOfItems)] = {
  "App",

  "Input",
  "Agent",

  "Scene",
  "State",
  "Stage",

  "Phase",
  "Model",
  "Actor",

  "Layer",
  "Style",

  "Image",
  "Error",

  "Timeline",
  "TimelineNode",

  "Resource",

  "Renderer",
  "ImageClip",
  "LYRTileDataSource",
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
