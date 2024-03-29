#ifndef PLAIN_PLAVECTOR_HPP
#define PLAIN_PLAVECTOR_HPP

#include "Primitive/PLAPRMType.hpp"
#include "Grain/Primitive/GRAPRMVector.hpp"


//-- Float --///////////////////////////////////////////////////////////////////

using PLAVec2f = GRAVec2<PLAFloat>;
static const PLAVec2f kPLAVec2fNone = PLAVec2f(0);
static const PLAVec2f kPLAVec2fNorm = PLAVec2f(1);
static const PLAVec2f kPLAVec2fUndefined = PLAVec2f(kPLAFloatUndefined);

using PLAVec3f = GRAVec3<PLAFloat>;
static const PLAVec3f kPLAVec3fNone = PLAVec3f(0);
static const PLAVec3f kPLAVec3fNorm = PLAVec3f(1);
static const PLAVec3f kPLAVec3fUndefined = PLAVec3f(kPLAFloatUndefined);

using PLAVec4f = GRAVec4<PLAFloat>;
static const PLAVec4f kPLAVec4fNone = PLAVec4f(0);
static const PLAVec4f kPLAVec4fNorm = PLAVec4f(1);
static const PLAVec4f kPLAVec4fUndefined = PLAVec4f(kPLAFloatUndefined);


//-- Integer --/////////////////////////////////////////////////////////////////

using PLAVec2i = GRAVec2<PLAInt>;
static const PLAVec2i kPLAVec2iNone = PLAVec2i(0);
static const PLAVec2i kPLAVec2iNorm = PLAVec2i(1);
static const PLAVec2i kPLAVec2iUndefined = PLAVec2i(kPLAIntUndefined);

using PLAVec3i = GRAVec3<PLAInt>;
static const PLAVec3i kPLAVec3iNone = PLAVec3i(0);
static const PLAVec3i kPLAVec3iNorm = PLAVec3i(1);
static const PLAVec3i kPLAVec3iUndefined = PLAVec3i(kPLAIntUndefined);

using PLAVec4i = GRAVec4<PLAInt>;
static const PLAVec4i kPLAVec4iNone = PLAVec4i(0);
static const PLAVec4i kPLAVec4iNorm = PLAVec4i(1);
static const PLAVec4i kPLAVec4iUndefined = PLAVec4i(kPLAIntUndefined);


//-- Unsigned --////////////////////////////////////////////////////////////////

using PLAVec2ui = GRAVec2<PLAUInt>;
static const PLAVec2ui kPLAVec2uiNone = PLAVec2ui(0);
static const PLAVec2ui kPLAVec2uiNorm = PLAVec2ui(1);
static const PLAVec2ui kPLAVec2uiUndefined = PLAVec2ui(kPLAUIntUndefined);

using PLAVec3ui = GRAVec3<PLAUInt>;
static const PLAVec3ui kPLAVec3uiNone = PLAVec3ui(0);
static const PLAVec3ui kPLAVec3uiNorm = PLAVec3ui(1);
static const PLAVec3ui kPLAVec3uiUndefined = PLAVec3ui(kPLAUIntUndefined);

using PLAVec4ui = GRAVec4<PLAUInt>;
static const PLAVec4ui kPLAVec4uiNone = PLAVec4ui(0);
static const PLAVec4ui kPLAVec4uiNorm = PLAVec4ui(1);
static const PLAVec4ui kPLAVec4uiUndefined = PLAVec4ui(kPLAUIntUndefined);


//-- Size --////////////////////////////////////////////////////////////////////

using PLAVec2s = GRAVec2<PLASize>;
static const PLAVec2s kPLAVec2sNone = PLAVec2s(0);
static const PLAVec2s kPLAVec2sNorm = PLAVec2s(1);
static const PLAVec2s kPLAVec2sUndefined = PLAVec2s(kPLASizeUndefined);

using PLAVec3s = GRAVec3<PLASize>;
static const PLAVec3s kPLAVec3sNone = PLAVec3s(0);
static const PLAVec3s kPLAVec3sNorm = PLAVec3s(1);
static const PLAVec3s kPLAVec3sUndefined = PLAVec3s(kPLASizeUndefined);

using PLAVec4s = GRAVec4<PLAUInt>;
static const PLAVec4s kPLAVec4sNone = PLAVec4s(0);
static const PLAVec4s kPLAVec4sNorm = PLAVec4s(1);
static const PLAVec4s kPLAVec4sUndefined = PLAVec4s(kPLASizeUndefined);


#endif //PLAIN_PLAVECTOR_HPP
