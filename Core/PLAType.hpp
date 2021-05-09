#ifndef PLAIN_ENGINE_PLATYPE_HPP
#define PLAIN_ENGINE_PLATYPE_HPP

#include <cstdio>
#include <cstdint>
#include <cmath>
#include "Grain/Grain-Macro.h"
#include "Grain/GRAType.hpp"
#include "Grain/GRAColor.hpp"
#include "Grain/GRAPoint.hpp"
#include "Grain/GRALine.hpp"
#include "Grain/GRARect.hpp"
#include "Grain/GRACircle.hpp"
#include "Grain/GRAVector.hpp"
#include "Grain/GRAFunctor.hpp"
#include "Grain/GRABinder.hpp"
#include "Grain/GRAListener.hpp"
#include "Grain/GRATransform.hpp"
#include "Grain/GRACollision.hpp"

using PLAColor = GRAColorRGBA8888<GRAFloat>;
static const PLAColor kPLAColorNone    = PLAColor(0);
static const PLAColor kPLAColorNorm    = PLAColor(1);
static const PLAColor kPLAColorBlack   = PLAColor(0.00, 0.00, 0.00, 1.00);
static const PLAColor kPLAColorRed     = PLAColor(1.00, 0.00, 0.00, 1.00);
static const PLAColor kPLAColorGreen   = PLAColor(0.00, 1.00, 0.00, 1.00);
static const PLAColor kPLAColorBlue    = PLAColor(0.00, 0.00, 1.00, 1.00);
static const PLAColor kPLAColorYellow  = PLAColor(1.00, 1.00, 0.00, 1.00);
static const PLAColor kPLAColorCyan    = PLAColor(0.00, 1.00, 1.00, 1.00);
static const PLAColor kPLAColorMagenta = PLAColor(1.00, 0.00, 1.00, 1.00);
static const PLAColor kPLAColorGray    = PLAColor(0.50, 0.50, 0.50, 1.00);
static const PLAColor kPLAColorWhite   = PLAColor(1.00, 1.00, 1.00, 1.00);

using PLAVec2 = GRAVec2<GRAFloat>;
static const PLAVec2 kPLAVec2None = PLAVec2(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2(1);

using PLAVec3 = GRAVec3<GRAFloat>;
static const PLAVec3 kPLAVec3None = PLAVec3(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3(1);

using PLAVec4 = GRAVec4<GRAFloat>;
static const PLAVec4 kPLAVec4None = PLAVec4(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4(1);

using PLAPoint = GRAPoint<GRAFloat>;
static const PLAPoint kPLAPointNone = PLAPoint(0);
static const PLAPoint kPLAPointNorm = PLAPoint(1);

using PLALine = GRALine<GRAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALine(kPLAVec2None, kPLAVec2Norm);

using PLARect = GRARect<GRAFloat>;
static const PLARect kPLARectNone = PLARect(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARect(kPLAVec2None, kPLAVec2Norm);

using PLACircle = GRACircle<GRAFloat>;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec2None, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec2None, 1);

using PLATransform = GRATransform<GRAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3None);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3Norm);

using PLACollision = GRACollision<GRAFloat>;

#endif // PLAIN_ENGINE_PLATYPE_HPP
