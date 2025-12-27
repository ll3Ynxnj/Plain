#ifndef PLAIN_PLASTROKE_HPP
#define PLAIN_PLASTROKE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "grain/primitive/GRAPRMStroke.hpp"

using PLAStroke = GRAStroke<PLAFloat>;
static const PLAStroke kPLAStrokeNone = PLAStroke();
static const PLAStroke kPLAStrokeNorm = PLAStroke(kPLAColorGray, 1.0f);

#endif //PLAIN_PLASTROKE_HPP
