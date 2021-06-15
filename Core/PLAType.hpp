#ifndef PLAIN_ENGINE_PLATYPE_HPP
#define PLAIN_ENGINE_PLATYPE_HPP

#include <cstdio>
#include <cstdint>
#include <cmath>

#include "Grain/GRAType/GRAType.hpp"
#include "Grain/GRACollision.hpp"

//-- Boolean value --///////////////////////////////////////////////////////////
using PLABool = GRABool;

//-- Signed integer value --////////////////////////////////////////////////////
using PLAByte = GRAByte;
static const PLAByte kPLAByteMin = kGRAByteMin;
static const PLAByte kPLAByteMax = kGRAByteMax;
static const PLAByte kPLAByteUndefined = kGRAByteUndefined;

using PLAInt = GRAInt;
static const PLAInt kPLAIntMin = kGRAIntMin;
static const PLAInt kPLAIntMax = kGRAIntMax;
static const PLAInt kPLAIntUndefined = kGRAIntUndefined;

using PLAInt8 = GRAInt8;
static const PLAInt8 kPLAInt8Min = kGRAInt8Min;
static const PLAInt8 kPLAInt8Max = kGRAInt8Max;
static const PLAInt8 kPLAInt8Undefined = kGRAInt8Undefined;

using PLAInt16 = GRAInt16;
static const PLAInt16 kPLAInt16Min = kGRAInt16Min;
static const PLAInt16 kPLAInt16Max = kGRAInt16Max;
static const PLAInt16 kPLAInt16Undefined = kGRAInt16Undefined;

using PLAInt32 = GRAInt32;
static const PLAInt32 kPLAInt32Min = kGRAInt32Min;
static const PLAInt32 kPLAInt32Max = kGRAInt32Max;
static const PLAInt32 kPLAInt32Undefined = kGRAInt32Undefined;

using PLAInt64 = GRAInt64;
static const PLAInt64 kPLAInt64Min = kGRAInt64Min;
static const PLAInt64 kPLAInt64Max = kGRAInt64Max;
static const PLAInt64 kPLAInt64Undefined = kGRAInt64Undefined;

//-- Unsigned integer value --//////////////////////////////////////////////////
using PLAUByte = GRAUByte;
static const PLAUByte kPLAUByteMax = kGRAUByteMax;
static const PLAUByte kPLAUByteUndefined = kGRAUByteUndefined;

using PLAUInt = GRAUInt;
static const PLAUInt kPLAUIntMax =  kPLAUIntMax;
static const PLAUInt kPLAUIntUndefined = kGRAUIntUndefined;

using PLAUInt8 = GRAUInt8;
static const PLAUInt8 kPLAUInt8Max = kGRAUInt8Max;
static const PLAUInt8 kPLAUInt8Undefined = kGRAUInt8Undefined;

using PLAUInt16 = GRAUInt16;
static const PLAUInt16 kPLAUInt16Max = kGRAUInt16Max;
static const PLAUInt16 kPLAUInt16Undefined = kGRAUInt16Undefined;

using PLAUInt32 = GRAUInt32;
static const PLAUInt32 kPLAUInt32Max = kGRAUInt32Max;
static const PLAUInt32 kPLAUInt32Undefined = kGRAUInt32Undefined;

using PLAUInt64 = GRAUInt64;
static const PLAUInt64 kPLAUInt64Max = kGRAUInt64Max;
static const PLAUInt64 kPLAUInt64Undefined = kGRAUInt64Undefined;

//-- Floating point value --////////////////////////////////////////////////////
using PLAFloat = GRAFloat;

//-- Size value --//////////////////////////////////////////////////////////////
using PLASize = GRASize;
static const PLASize kPLASizeMax = kGRASizeMax;
static const PLASize kPLASizeUndefined = kGRASizeUndefined;

static const char *kPLAStrUndefined = kGRAStrUndefined;

//-- Colors --//////////////////////////////////////////////////////////////////
using PLAColor = GRAColorRGBA8888<PLAFloat>;
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

//-- Vectors --/////////////////////////////////////////////////////////////////
using PLAVec2 = GRAVec2<PLAFloat>;
static const PLAVec2 kPLAVec2None = PLAVec2(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2(1);

using PLAVec3 = GRAVec3<PLAFloat>;
static const PLAVec3 kPLAVec3None = PLAVec3(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3(1);

using PLAVec4 = GRAVec4<PLAFloat>;
static const PLAVec4 kPLAVec4None = PLAVec4(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4(1);

//-- Points --//////////////////////////////////////////////////////////////////
using PLAPoint = GRAPoint<PLAFloat>;
static const PLAPoint kPLAPointNone = PLAPoint(0);
static const PLAPoint kPLAPointNorm = PLAPoint(1);

//-- Lines --////../////////////////////////////////////////////////////////////
using PLALine = GRALine<PLAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALine(kPLAVec2None, kPLAVec2Norm);

//-- Rects --/////..////////////////////////////////////////////////////////////
using PLARect = GRARect<PLAFloat>;
static const PLARect kPLARectNone = PLARect(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARect(kPLAVec2None, kPLAVec2Norm);

//-- Circles --/////////////////////////////////////////////////////////////////
using PLACircle = GRACircle<PLAFloat>;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec2None, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec2None, 1);

//-- Transforms --//////////////////////////////////////////////////////////////
using PLATransform = GRATransform<PLAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3None);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3Norm);

//-- Binders --/////////////////////////////////////////////////////////////////

//-- Collisions --//////////////////////////////////////////////////////////////
using PLACollision = GRACollision<PLAFloat>;

//-- Functors --////////////////////////////////////////////////////////////////


#endif // PLAIN_ENGINE_PLATYPE_HPP
