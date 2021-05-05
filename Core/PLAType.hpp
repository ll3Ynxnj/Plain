#ifndef PLAIN_ENGINE_PLATYPE_HPP
#define PLAIN_ENGINE_PLATYPE_HPP

#include <cstdio>
#include <cstdint>
#include <cmath>
#include "Grain/GRAColor.hpp"
#include "Grain/GRAPoint.hpp"
#include "Grain/GRALine.hpp"
#include "Grain/GRARect.hpp"
#include "Grain/GRACircle.hpp"
#include "Grain/GRAVector.hpp"

//-- Boolean value --///////////////////////////////////////////////////////////
using PLABool = bool;

//-- Signed integer value --////////////////////////////////////////////////////
using PLAByte = int_fast8_t;
static const PLAByte kPLAByteMin = INT_FAST8_MIN;
static const PLAByte kPLAByteMax = INT_FAST8_MAX;
static const PLAByte kPLAByteUndefined = kPLAByteMin;

using PLAInt = int_fast64_t;
static const PLAInt kPLAIntMin = INT_FAST64_MIN;
static const PLAInt kPLAIntMax = INT_FAST64_MAX;
static const PLAInt kPLAIntUndefined = kPLAIntMin;

using PLAInt8 = int_least8_t;
static const PLAInt8 kPLAInt8Min = INT_LEAST8_MIN;
static const PLAInt8 kPLAInt8Max = INT_LEAST8_MAX;
static const PLAInt8 kPLAInt8Undefined = kPLAInt8Min;

using PLAInt16 = int_least16_t;
static const PLAInt16 kPLAInt16Min = INT_LEAST16_MIN;
static const PLAInt16 kPLAInt16Max = INT_LEAST16_MAX;
static const PLAInt16 kPLAInt16Undefined = kPLAInt16Min;

using PLAInt32 = int_least32_t;
static const PLAInt32 kPLAInt32Min = INT_LEAST32_MIN;
static const PLAInt32 kPLAInt32Max = INT_LEAST32_MAX;
static const PLAInt32 kPLAInt32Undefined = kPLAInt32Min;

using PLAInt64 = int_least64_t;
static const PLAInt64 kPLAInt64Min = INT_LEAST64_MIN;
static const PLAInt64 kPLAInt64Max = INT_LEAST64_MAX;
static const PLAInt64 kPLAInt64Undefined = kPLAInt64Min;

//-- Unsigned integer value --//////////////////////////////////////////////////
using PLAUByte = uint_fast8_t;
static const PLAUByte kPLAUByteMax = UINT_FAST8_MAX;
static const PLAUByte kPLAUByteUndefined = kPLAUByteMax;

using PLAUInt = uint_fast64_t;
static const PLAUInt kPLAUIntMax = UINT_FAST64_MAX;
static const PLAUInt kPLAUIntUndefined = kPLAUIntMax;

using PLAUInt8 = uint_least8_t;
static const PLAUInt8 kPLAUInt8Max = UINT_LEAST8_MAX;
static const PLAUInt8 kPLAUInt8Undefined = kPLAUInt8Max;

using PLAUInt16 = uint_least16_t;
static const PLAUInt16 kPLAUInt16Max = UINT_LEAST16_MAX;
static const PLAUInt16 kPLAUInt16Undefined = kPLAUInt16Max;

using PLAUInt32 = uint_least32_t;
static const PLAUInt32 kPLAUInt32Max = UINT_LEAST32_MAX;
static const PLAUInt32 kPLAUInt32Undefined = kPLAUInt32Max;

using PLAUInt64 = uint_least64_t;
static const PLAUInt64 kPLAUInt64Max = UINT_LEAST64_MAX;
static const PLAUInt64 kPLAUInt64Undefined = kPLAUInt64Max;

//-- Floating point value --////////////////////////////////////////////////////
using PLAFloat = float_t;

//-- Size value --//////////////////////////////////////////////////////////////
using PLASize = size_t;
static const PLASize kPLASizeMax = SIZE_MAX;
static const PLASize kPLASizeUndefined = 0;

static const char *kPLACharUndefined  = " == UNDEFINED == ";

using PLAColor = GRAColorRGBA8888<PLAFloat>;
static PLAColor PLAColorMake(PLAFloat aV)
{ return { aV, aV, aV, aV }; };
static PLAColor PLAColorMake(PLAFloat aR, PLAFloat aG, PLAFloat aB, PLAFloat aA)
{ return { aR, aG, aB, aA }; };
static PLAColor PLAColorMul(const PLAColor &aColor, PLAFloat aV)
{ return { aColor.r * aV, aColor.g * aV, aColor.b * aV, aColor.a * aV }; };
static PLAColor PLAColorMul(const PLAColor &aS, const PLAColor &aD)
{ return { aS.r * aD.r, aS.g * aD.g, aS.b * aD.b, aS.a * aD.a }; };
static const PLAColor kPLAColorNone    = PLAColorMake(0);
static const PLAColor kPLAColorNorm    = PLAColorMake(1);
static const PLAColor kPLAColorBlack   = PLAColorMake(0.00, 0.00, 0.00, 1.00);
static const PLAColor kPLAColorRed     = PLAColorMake(1.00, 0.00, 0.00, 1.00);
static const PLAColor kPLAColorGreen   = PLAColorMake(0.00, 1.00, 0.00, 1.00);
static const PLAColor kPLAColorBlue    = PLAColorMake(0.00, 0.00, 1.00, 1.00);
static const PLAColor kPLAColorYellow  = PLAColorMake(1.00, 1.00, 0.00, 1.00);
static const PLAColor kPLAColorCyan    = PLAColorMake(0.00, 1.00, 1.00, 1.00);
static const PLAColor kPLAColorMagenta = PLAColorMake(1.00, 0.00, 1.00, 1.00);
static const PLAColor kPLAColorGray    = PLAColorMake(0.50, 0.50, 0.50, 1.00);
static const PLAColor kPLAColorWhite   = PLAColorMake(1.00, 1.00, 1.00, 1.00);

using PLAVec2 = GRAVec2<PLAFloat>;
static PLAVec2 PLAVec2Make(PLAFloat aV) { return { aV, aV }; };
static PLAVec2 PLAVec2Make(PLAFloat aX, PLAFloat aY)
{ return { aX, aY }; };
static const PLAVec2 kPLAVec2None = PLAVec2Make(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2Make(1);

using PLAVec3 = GRAVec3<PLAFloat>;
static PLAVec3 PLAVec3Make(PLAFloat aV) { return { aV, aV, aV }; };
static PLAVec3 PLAVec3Make(PLAFloat aX, PLAFloat aY, PLAFloat aZ)
{ return { aX, aY, aZ }; };
static const PLAVec3 kPLAVec3None = PLAVec3Make(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3Make(1);

using PLAVec4 = GRAVec4<PLAFloat>;
static PLAVec4 PLAVec4Make(PLAFloat aV) { return { aV, aV, aV, aV }; }
static PLAVec4 PLAVec4Make(PLAFloat aX, PLAFloat aY, PLAFloat aZ, PLAFloat aW)
{ return { aX, aY, aZ, aW }; }
static const PLAVec4 kPLAVec4None = PLAVec4Make(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4Make(1);

using PLAPoint = GRAPoint<PLAFloat>;
static PLAVec2 PLAPointMake(PLAFloat aV) { return { aV, aV }; };
static PLAVec2 PLAPointMake(PLAFloat aX, PLAFloat aY) { return { aX, aY }; };
static const PLAPoint kPLAPointNone = PLAPointMake(0);
static const PLAPoint kPLAPointNorm = PLAPointMake(1);

using PLALine = GRALine<PLAFloat>;
static PLALine PLALineMake(PLAVec2 aP0, PLAVec2 aP1) { return { aP0, aP1 }; };
static const PLALine kPLALineNone = PLALineMake(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALineMake(kPLAVec2None, kPLAVec2Norm);

using PLARect = GRARect<PLAFloat>;
static PLARect PLARectMake(PLAVec2 aPos, PLAVec2 aSize)
{ return { aPos, aSize }; };
static PLARect PLARectMake(PLAFloat aX, PLAFloat aY, PLAFloat aWidth, PLAFloat aHeight)
{ return { { aX, aY }, { aWidth, aHeight } }; };
static const PLARect kPLARectNone = PLARectMake(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARectMake(kPLAVec2None, kPLAVec2Norm);

using PLACircle = GRACircle<PLAFloat>;
static PLACircle PLACircleMake(PLAVec2 aPos, PLAFloat aRadius)
{ return { aPos, aRadius }; }  ;
static PLACircle PLACircleMake(PLAFloat aX, PLAFloat aY, PLAFloat aRadius)
{ return { { aX, aY }, aRadius }; };
static const PLACircle kPLACircleNone = PLACircleMake(kPLAVec2None, 0);
static const PLACircle kPLACircleNorm = PLACircleMake(kPLAVec2None, 1);

struct PLATransform
{
  PLAVec3 translation, rotation, scale;
  PLATransform() :
  translation(kPLAVec3None), rotation(kPLAVec3None), scale(kPLAVec3Norm) {};
  PLATransform(PLAVec3 aTranslation, PLAVec3 aRotation, PLAVec3 aScale) :
  translation(aTranslation), rotation(aRotation), scale(aScale) {};
};

#endif // PLAIN_ENGINE_PLATYPE_HPP
