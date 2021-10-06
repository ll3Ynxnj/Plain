//
// Created by Kentaro Kawai on 2021/09/08.
//

#include "PLAProperty.hpp"

class PLAPropertyTest : public ::testing::Test
{
protected:
  std::map<PLAString, PLAProperty>_properties = std::map<PLAString, PLAProperty>();

  virtual void SetUp()
  {
    _properties["Bool"] = PLAProperty(PLAPropertyType::Bool);
    _properties["Int"] = PLAProperty(PLAPropertyType::Int);
    _properties["Float"] = PLAProperty(PLAPropertyType::Float);
    _properties["Color"] = PLAProperty(PLAPropertyType::Color);
    _properties["Vec2"] = PLAProperty(PLAPropertyType::Vec2);
    _properties["Vec3"] = PLAProperty(PLAPropertyType::Vec3);
    _properties["Vec4"] = PLAProperty(PLAPropertyType::Vec4);
  }

  virtual void TearDown()
  {

  }

};

TEST_F(PLAPropertyTest, SettingAndGettingValue)
{
  _properties.at("Bool").SetBool(true);
  ASSERT_EQ(PLABool(true), _properties.at("Bool").GetBool());
  _properties.at("Int").SetInt(1984);
  ASSERT_EQ(PLAInt(1984), _properties.at("Int").GetInt());
  _properties.at("Float").SetFloat(1.618);
  ASSERT_EQ(PLAFloat(1.618), _properties.at("Float").GetFloat());
  PLAFloat r(1.00), g(0.62), b(0.38), a(0.50);
  PLAColor color = PLAColor(r, g, b, a);
  _properties.at("Color").SetColor(color);
  ASSERT_EQ(color.r, _properties.at("Color").GetColor().r);
  ASSERT_EQ(color.g, _properties.at("Color").GetColor().g);
  ASSERT_EQ(color.b, _properties.at("Color").GetColor().b);
  ASSERT_EQ(color.a, _properties.at("Color").GetColor().a);
  PLAFloat x(1.414), y(1.618);
  PLAVec2 vec2 = PLAVec2(x, y);
  _properties.at("Vec2").SetVec2(vec2);
  ASSERT_EQ(vec2.x, _properties.at("Vec2").GetVec2().x);
  ASSERT_EQ(vec2.y, _properties.at("Vec2").GetVec2().y);
  PLAFloat z(3.141);
  PLAVec3 vec3 = PLAVec3(x, y, z);
  _properties.at("Vec3").SetVec3(vec3);
  ASSERT_EQ(vec3.x, _properties.at("Vec3").GetVec3().x);
  ASSERT_EQ(vec3.y, _properties.at("Vec3").GetVec3().y);
  ASSERT_EQ(vec3.z, _properties.at("Vec3").GetVec3().z);
  PLAFloat w(0.382);
  PLAVec4 vec4(x, y, z, w);
  _properties.at("Vec4").SetVec4(vec4);
  ASSERT_EQ(vec4.x, _properties.at("Vec4").GetVec4().x);
  ASSERT_EQ(vec4.y, _properties.at("Vec4").GetVec4().y);
  ASSERT_EQ(vec4.z, _properties.at("Vec4").GetVec4().z);
  ASSERT_EQ(vec4.w, _properties.at("Vec4").GetVec4().w);
}

