#ifndef PLAIN_PLATYPE_HPP
#define PLAIN_PLATYPE_HPP

#include "Grain/GRAColor.hpp"
#include "Grain/GRARect.hpp"
#include "Grain/GRACircle.hpp"
#include "Grain/GRAVector.hpp"

typedef GRAColorRGBA8888 PLAColor;
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

typedef GRAVec2<float> PLAVec2;
static const PLAVec2 kPLAVec2None = PLAVec2(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2(1);

typedef GRAVec3<float> PLAVec3;
static const PLAVec3 kPLAVec3None = PLAVec3(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3(1);

typedef GRAVec4<float> PLAVec4;
static const PLAVec4 kPLAVec4None = PLAVec4(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4(1);

typedef GRARect<float> PLARect;
static const PLARect kPLARectNone = PLARect(kPLAVec3None, kPLAVec3None);
static const PLARect kPLARectNorm = PLARect(kPLAVec3Norm, kPLAVec3Norm);

typedef GRACircle<float> PLACircle;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec3None, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec3Norm, 1);

#endif // PLAIN_PLATYPE_HPP
