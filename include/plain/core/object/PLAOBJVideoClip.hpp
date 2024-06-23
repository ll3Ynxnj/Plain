//
// Created by ll3ynxnj on 6/19/24.
//

#ifndef PLAIN_PLAOBJVIDEOCLIP_H
#define PLAIN_PLAOBJVIDEOCLIP_H

#include "plain/core/object/PLAOBJImageClip.hpp"
#include "plain/core/object/PLAOBJVideo.hpp"
#include "plain/core/agent/PLAAGTVideoClip.hpp"
#include "plain/core/primitive/PLAPRMRange.hpp"

class PLAOBJVideoClip: public PLAOBJImageClip
{
  const PLAOBJVideo *_video = nullptr;
  PLARange _clip = kPLARangeNone;
  PLARange _normalizedClip = kPLARangeNone;

protected:
  PLAOBJVideoClip(const PLAOBJVideo *aVideo,
                  const PLARange &aFrameClip, const PLARect &aPixelClip,
                  PLAObjectType aType = PLAObjectType::VideoClip);

public:
  PLAOBJVideoClip() = delete;
  static PLAOBJVideoClip *Create(const PLAString &aVideoName);
  static PLAOBJVideoClip *Create(const PLAString &aVideoName,
                                 const PLARange &aFrameClip,
                                 const PLARect &aPixelClip = kPLARectNorm);
  static PLAOBJVideoClip *Object(const PLAString &aObjectName);
  static PLAOBJVideoClip *Object(PLAId aObjectId);

  ~PLAOBJVideoClip();

  PLAAGTVideoClip AssignAgent();

  const PLAOBJVideo *GetVideo() const { return _video; }
  //const PLARange &GetFrameClip() const { return _clip; }
  //const PLARange &GetNormalizedPixelClip() const { return _normalizedClip; }

  void SetFrameClip(const PLARange &aClip);
  void SetNormalizedFrameClip(const PLARange &aClip);

private:
  void UpdateFrameClip(const PLARange &aClip);
  void UpdateNormalizedFrameClip(const PLARange &aClip);
};

#endif //PLAIN_PLAOBJVIDEOCLIP_H
