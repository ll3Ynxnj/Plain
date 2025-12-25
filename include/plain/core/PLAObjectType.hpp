#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "plain/core/primitive/PLAPRMVector.hpp"

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

  Motion,
  MotionNode,

  Resource,
  Stream,

  Renderer,
  ImageClip,
  Video,
  VideoClip,
  LYRTileDataSource,
  FaceDetector,
  FaceTracker,
  SmileDetector,
  FontRasterizer,
  FrameAnalyzer,

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

  "Motion",
  "MotionNode",

  "Resource",
  "Stream",

  "Renderer",
  "ImageClip",
  "Video",
  "VideoClip",
  "LYRTileDataSource",
  "FaceDetector",
  "FaceTracker",
  "SmileDetector",
  "FontRasterizer",
  "FrameAnalyzer",
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
