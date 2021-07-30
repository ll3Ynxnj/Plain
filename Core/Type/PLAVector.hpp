#ifndef PLAIN_PLAVECTOR_HPP
#define PLAIN_PLAVECTOR_HPP

#include "Type/PLAType.hpp"
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


//-- Integer --/////////////////////////////////////////////////////////////////

using PLAVec2i = GRAVec2<PLAInt>;
static const PLAVec2i kPLAVec2iNone = PLAVec2i(0);
static const PLAVec2i kPLAVec2iNorm = PLAVec2i(1);

using PLAVec3i = GRAVec3<PLAInt>;
static const PLAVec3i kPLAVec3iNone = PLAVec3i(0);
static const PLAVec3i kPLAVec3iNorm = PLAVec3i(1);

using PLAVec4i = GRAVec4<PLAInt>;
static const PLAVec4i kPLAVec4iNone = PLAVec4i(0);
static const PLAVec4i kPLAVec4iNorm = PLAVec4i(1);


//-- Unsigned --////////////////////////////////////////////////////////////////

using PLAVec2ui = GRAVec2<PLAUInt>;
static const PLAVec2ui kPLAVec2uiNone = PLAVec2ui(0);
static const PLAVec2ui kPLAVec2uiNorm = PLAVec2ui(1);

using PLAVec3ui = GRAVec3<PLAUInt>;
static const PLAVec3ui kPLAVec3uiNone = PLAVec3ui(0);
static const PLAVec3ui kPLAVec3uiNorm = PLAVec3ui(1);

using PLAVec4ui = GRAVec4<PLAUInt>;
static const PLAVec4ui kPLAVec4uiNone = PLAVec4ui(0);
static const PLAVec4ui kPLAVec4uiNorm = PLAVec4ui(1);


//-- Size --////////////////////////////////////////////////////////////////////

using PLAVec2s = GRAVec2<PLASize>;
static const PLAVec2s kPLAVec2sNone = PLAVec2s(0);
static const PLAVec2s kPLAVec2sNorm = PLAVec2s(1);

using PLAVec3s = GRAVec3<PLASize>;
static const PLAVec3s kPLAVec3sNone = PLAVec3s(0);
static const PLAVec3s kPLAVec3sNorm = PLAVec3s(1);

using PLAVec4s = GRAVec4<PLAUInt>;
static const PLAVec4ui kPLAVec4sNone = PLAVec4s(0);
static const PLAVec4ui kPLAVec4sNorm = PLAVec4s(1);


//-- Float --///////////////////////////////////////////////////////////////////

using PLAVec2f = GRAVec2<PLAFloat>;
static const PLAVec2f kPLAVec2fNone = PLAVec2f(0);
static const PLAVec2f kPLAVec2fNorm = PLAVec2f(1);

using PLAVec3f = GRAVec3<PLAFloat>;
static const PLAVec3f kPLAVec3fNone = PLAVec3f(0);
static const PLAVec3f kPLAVec3fNorm = PLAVec3f(1);

using PLAVec4f = GRAVec4<PLAFloat>;
static const PLAVec4f kPLAVec4fNone = PLAVec4f(0);
static const PLAVec4f kPLAVec4fNorm = PLAVec4f(1);

#endif //PLAIN_PLAVECTOR_HPP
