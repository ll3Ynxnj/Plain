#ifndef PLAIN_PLARANGE_HPP
#define PLAIN_PLARANGE_HPP

#include "plain/core/primitive/PLAPRMVector.hpp"
#include "grain/primitive/GRAPRMRange.hpp"

using PLARange = GRAPRMRange<PLAFloat>;
static const PLARange kPLARangeNone = PLARange(0, 0);
static const PLARange kPLARangeNorm = PLARange(0, 1);

#endif //PLAIN_PLARANGE_HPP
