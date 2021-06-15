#ifndef ANHR_PLAVECTOR_HPP
#define ANHR_PLAVECTOR_HPP

#include "Grain/Type/GRAVector.hpp"

using PLAVec2 = GRAVec2<PLAFloat>;
static const PLAVec2 kPLAVec2None = PLAVec2(0);
static const PLAVec2 kPLAVec2Norm = PLAVec2(1);

using PLAVec3 = GRAVec3<PLAFloat>;
static const PLAVec3 kPLAVec3None = PLAVec3(0);
static const PLAVec3 kPLAVec3Norm = PLAVec3(1);

using PLAVec4 = GRAVec4<PLAFloat>;
static const PLAVec4 kPLAVec4None = PLAVec4(0);
static const PLAVec4 kPLAVec4Norm = PLAVec4(1);

#endif //ANHR_PLAVECTOR_HPP
