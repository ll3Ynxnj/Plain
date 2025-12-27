#ifndef PLAIN_PLASTROKE_HPP
#define PLAIN_PLASTROKE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/PLAStrokeJoinType.hpp"
#include "plain/core/PLAStrokeAlignType.hpp"

struct PLAStroke
{
  PLAColor color = kPLAColorNone;
  PLAFloat width = 2.0f;
  PLAStrokeJoinType join = PLAStrokeJoinType::Miter;
  PLAStrokeAlignType align = PLAStrokeAlignType::Center;

  PLAStroke() = default;

  PLAStroke(const PLAColor &aColor, PLAFloat aWidth)
    : color(aColor), width(aWidth) {}

  PLAStroke(const PLAColor &aColor, PLAFloat aWidth,
            PLAStrokeJoinType aJoin, PLAStrokeAlignType aAlign)
    : color(aColor), width(aWidth), join(aJoin), align(aAlign) {}
};

static const PLAStroke kPLAStrokeNone = PLAStroke();

#endif //PLAIN_PLASTROKE_HPP
