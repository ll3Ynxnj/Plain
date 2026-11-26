// Copyright (c) 2026. CLAYWORK Inc. All rights reserved.

#include <malloc.h>

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/object/layer/PLALYRLabel.hpp"

namespace
{
long MallocInUse()
{
  struct mallinfo2 info = mallinfo2();
  return static_cast<long>(info.uordblks + info.hblkhd);
}
}

TEST(PLAOBJImageTest, UpdateDataReplacesPixelsInPlace)
{
  std::vector<PLAUInt8> red(2 * 1 * 4, 0);
  red[0] = 255;
  red[4] = 255;
  PLAOBJImage *image = PLAOBJImage::CreateFromMemory("image_test_update", red.data(),
                                                     PLAOBJImageSize(2, 1), PLAImageType::Raw);
  const uint64_t revision = image->GetRevision();

  std::vector<PLAUInt8> blue(3 * 2 * 4, 0);
  for (size_t i = 2; i < blue.size(); i += 4)
  {
    blue[i] = 255;
  }
  image->UpdateData(blue.data(), PLAOBJImageSize(3, 2));

  EXPECT_EQ(image->GetSize().x, 3u);
  EXPECT_EQ(image->GetSize().y, 2u);
  EXPECT_NE(image->GetRevision(), revision);
  EXPECT_EQ(image->GetResourceData()[0], 0);
  EXPECT_EQ(image->GetResourceData()[2], 255);
  EXPECT_EQ(image->GetResourceData()[blue.size() - 2], 255);
}

// A label that shows a changing number (a count, an amount) rebuilds its text image on every change.
// The memory it holds must stay the same however often the text changes.
TEST(PLALYRLabelTest, ChangingTextKeepsMemoryFlat)
{
  PLALYRLabel *label = PLALYRLabel::Create("0", 96.0f, kPLAColorWhite);
  label->Update();
  const PLAOBJImage *image = label->GetTextureImage();
  ASSERT_NE(image, nullptr);

  for (int i = 1; i <= 20; ++i)
  {
    label->SetText(std::to_string(i));
    label->Update();
  }
  const long before = MallocInUse();
  for (int i = 1000; i < 1300; ++i)
  {
    label->SetText(std::to_string(i));
    label->Update();
  }
  const long grown = MallocInUse() - before;

  EXPECT_EQ(label->GetTextureImage(), image);
  EXPECT_LT(grown, 256 * 1024) << "300 text changes grew " << grown << " bytes";
}
