#include "PLAStyle.hpp"

PLAStyle::Item::Type PLAStyle::kValidationTable[unsigned(PLAStyleType::kNumberOfItems)]
{
  PLAStyle::Item::Type::Color, // FillColor
  PLAStyle::Item::Type::Color, // StrokeColor
  PLAStyle::Item::Type::Float, // StrokeWidth
};

PLAStyle::PLAStyle() :
PLAObject(PLAObjectType::Style)
{

}

PLAStyle::~PLAStyle()
{

}
