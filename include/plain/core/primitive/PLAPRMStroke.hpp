#ifndef PLAIN_PLASTROKE_HPP
#define PLAIN_PLASTROKE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"
#include "grain/primitive/GRAPRMStroke.hpp"

using PLAStroke = GRAStroke<PLAFloat>;

static const PLAStroke kPLAStrokeNone = PLAStroke();

#endif //PLAIN_PLASTROKE_HPP
