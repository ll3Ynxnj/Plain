#ifndef PLAIN_PLACOLOR_HPP
#define PLAIN_PLACOLOR_HPP

#include "Grain/Primitive/GRAPRMColor.hpp"

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

#endif //PLAIN_PLACOLOR_HPP
