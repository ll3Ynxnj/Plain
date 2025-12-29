#ifndef PLAIN_PLAOBJVIDEOCLIP_H
#define PLAIN_PLAOBJVIDEOCLIP_H

#include "plain/core/object/PLAOBJImageClip.hpp"
#include "plain/core/object/PLAOBJVideo.hpp"
#include "plain/core/agent/PLAAGTVideoClip.hpp"
#include "plain/core/primitive/PLAPRMRange.hpp"

class PLAOBJVideoClip: public PLAOBJImageClip
{
  /**
   * 動画データ
   */
  PLAOBJVideo *_video = nullptr;

  /**
   * 時間軸の切り抜き範囲
   *
   * TODO: 時間軸の管理はVideoClipではなくVideoで行う方が適切な可能性がある
   *       - VideoClipは空間軸の切り抜き（ImageClip継承）のみを担当
   *       - Videoが再生位置・フレーム範囲を管理
   *       - 複数のVideoClipが同じVideoを参照する場合、テクスチャを共有できる
   *
   * TODO: Time axis management may be more appropriate in Video rather than VideoClip
   *       - VideoClip handles only spatial clipping (inherited from ImageClip)
   *       - Video manages playback position and frame range
   *       - Multiple VideoClips referencing the same Video can share textures
   */
  PLARange _clip = kPLARangeNone;

  /**
   * 時間軸の切り抜き範囲（正規化座標）
   */
  PLARange _normalizedClip = kPLARangeNone;

protected:
  PLAOBJVideoClip(PLAOBJVideo *aVideo,
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

  void Update();

  PLAAGTVideoClip AssignAgent();

  PLAOBJVideo *GetVideo() const { return _video; }
  //const PLARange &GetFrameClip() const { return _clip; }
  //const PLARange &GetNormalizedPixelClip() const { return _normalizedClip; }

  void SetFrameClip(const PLARange &aClip);
  void SetNormalizedFrameClip(const PLARange &aClip);

private:
  void UpdateFrameClip(const PLARange &aClip);
  void UpdateNormalizedFrameClip(const PLARange &aClip);
};

#endif //PLAIN_PLAOBJVIDEOCLIP_H
