#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "Primitive/PLAPRMVector.hpp"

enum class PLAObjectType : PLAInt
{
  App,
  Input,
  Agent,
  Scene,
  Stage,
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

static const char *kPLAObjectTypeName[static_cast<PLAId>(PLAObjectType::kNumberOfItems)] = {
  "App",
  "Input",
  "Agent",
  "Scene",
  "Stage",
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
