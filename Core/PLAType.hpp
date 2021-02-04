#ifndef PLAIN_ENGINE_PLATYPE_HPP
#define PLAIN_ENGINE_PLATYPE_HPP

#include <cstdio>
#include "../Grain/GRAColor.hpp"
#include "../Grain/GRAPoint.hpp"
#include "../Grain/GRALine.hpp"
#include "../Grain/GRARect.hpp"
#include "../Grain/GRACircle.hpp"
#include "../Grain/GRAVector.hpp"

static const size_t      kPLASizeUndefined  = 0;
static const int         kPLAIntUndefined   = 0;
/*
static const int8_t      kPLAInt8Undefined  = INT8_MIN;
static const int16_t     kPLAInt16Undefined = INT16_MIN;
static const int32_t     kPLAInt32Undefined = INT32_MIN;
static const int64_t     kPLAInt64Undefined = INT64_MIN;
static const uintmax_t   kPLAUIntUndefined  = 0;
*/
static const char       *kPLACharUndefined  = " == UNDEFINED == ";

using PLAColor = GRAColorRGBA8888;
static PLAColor PLAColorMake(float aV)
{ return { aV, aV, aV, aV }; };
static PLAColor PLAColorMake(float aR, float aG, float aB, float aA)
{ return { aR, aG, aB, aA }; };
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

using PLACode = unsigned;

using PLAVec2 = GRAVec2<float>;
static PLAVec2 PLAVec2Make(float aV) { return { aV, aV }; };
static PLAVec2 PLAVec2Make(float aX, float aY)
{ return { aX, aY }; };
static const PLAVec2 kPLAVec2None = PLAVec2Make(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2Make(1);

using PLAVec3 = GRAVec3<float>;
static PLAVec3 PLAVec3Make(float aV) { return { aV, aV, aV }; };
static PLAVec3 PLAVec3Make(float aX, float aY, float aZ)
{ return { aX, aY, aZ }; };
static const PLAVec3 kPLAVec3None = PLAVec3Make(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3Make(1);

using PLAVec4 = GRAVec4<float>;
static PLAVec4 PLAVec4Make(float aV) { return { aV, aV, aV, aV }; }
static PLAVec4 PLAVec4Make(float aX, float aY, float aZ, float aW)
{ return { aX, aY, aZ, aW }; }
static const PLAVec4 kPLAVec4None = PLAVec4Make(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4Make(1);

using PLAPoint = GRAPoint<float>;
static PLAVec2 PLAPointMake(float aV) { return { aV, aV }; };
static PLAVec2 PLAPointMake(float aX, float aY) { return { aX, aY }; };
static const PLAPoint kPLAPointNone = PLAPointMake(0);
static const PLAPoint kPLAPointNorm = PLAPointMake(1);

using PLALine = GRALine<float>;
static PLALine PLALineMake(PLAVec2 aP0, PLAVec2 aP1) { return { aP0, aP1 }; };
static const PLALine kPLALineNone = PLALineMake(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALineMake(kPLAVec2None, kPLAVec2Norm);

using PLARect = GRARect<float>;
static PLARect PLARectMake(PLAVec2 aPos, PLAVec2 aSize)
{ return { aPos, aSize }; };
static PLARect PLARectMake(float aX, float aY, float aWidth, float aHeight)
{ return { { aX, aY }, { aWidth, aHeight } }; };
static const PLARect kPLARectNone = PLARectMake(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARectMake(kPLAVec2None, kPLAVec2Norm);

using PLACircle = GRACircle<float>;
static PLACircle PLACircleMake(PLAVec2 aPos, float aRadius)
{ return { aPos, aRadius }; }  ;
static PLACircle PLACircleMake(float aX, float aY, float aRadius)
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