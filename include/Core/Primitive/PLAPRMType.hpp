#ifndef PLAIN_ENGINE_PLAOBJTYPE_HPP
#define PLAIN_ENGINE_PLAOBJTYPE_HPP

#include <cstdio>
#include <cstdint>
#include <cmath>
#include <string>

#include "Primitive/GRAPRMType.hpp"

//-- Boolean value --///////////////////////////////////////////////////////////
using PLABool = GRABool;

//-- Signed integer value --////////////////////////////////////////////////////
using PLAByte = GRAByte;
static const PLAByte kPLAByteMin = kGRAByteMin;
static const PLAByte kPLAByteMax = kGRAByteMax;
static const PLAByte kPLAByteUndefined = kGRAByteUndefined;

using PLAInt = GRAInt;

static const PLAInt kPLAIntMin = kGRAIntMin;
static const PLAInt kPLAIntMax = kGRAIntMax;
static const PLAInt kPLAIntUndefined = kGRAIntUndefined;

using PLAInt8 = GRAInt8;
static const PLAInt8 kPLAInt8Min = kGRAInt8Min;
static const PLAInt8 kPLAInt8Max = kGRAInt8Max;
static const PLAInt8 kPLAInt8Undefined = kGRAInt8Undefined;

using PLAInt16 = GRAInt16;
static const PLAInt16 kPLAInt16Min = kGRAInt16Min;
static const PLAInt16 kPLAInt16Max = kGRAInt16Max;
static const PLAInt16 kPLAInt16Undefined = kGRAInt16Undefined;

using PLAInt32 = GRAInt32;
static const PLAInt32 kPLAInt32Min = kGRAInt32Min;
static const PLAInt32 kPLAInt32Max = kGRAInt32Max;
static const PLAInt32 kPLAInt32Undefined = kGRAInt32Undefined;

using PLAInt64 = GRAInt64;
static const PLAInt64 kPLAInt64Min = kGRAInt64Min;
static const PLAInt64 kPLAInt64Max = kGRAInt64Max;
static const PLAInt64 kPLAInt64Undefined = kGRAInt64Undefined;

//-- Unsigned integer value --//////////////////////////////////////////////////
using PLAUByte = GRAUByte;
static const PLAUByte kPLAUByteMax = kGRAUByteMax;
static const PLAUByte kPLAUByteUndefined = kGRAUByteUndefined;

using PLAUInt = GRAUInt;
static const PLAUInt kPLAUIntMax =  kPLAUIntMax;
static const PLAUInt kPLAUIntUndefined = kGRAUIntUndefined;

using PLAUInt8 = GRAUInt8;
static const PLAUInt8 kPLAUInt8Max = kGRAUInt8Max;
static const PLAUInt8 kPLAUInt8Undefined = kGRAUInt8Undefined;

using PLAUInt16 = GRAUInt16;
static const PLAUInt16 kPLAUInt16Max = kGRAUInt16Max;
static const PLAUInt16 kPLAUInt16Undefined = kGRAUInt16Undefined;

using PLAUInt32 = GRAUInt32;
static const PLAUInt32 kPLAUInt32Max = kGRAUInt32Max;
static const PLAUInt32 kPLAUInt32Undefined = kGRAUInt32Undefined;

using PLAUInt64 = GRAUInt64;
static const PLAUInt64 kPLAUInt64Max = kGRAUInt64Max;
static const PLAUInt64 kPLAUInt64Undefined = kGRAUInt64Undefined;

//-- Floating point value --////////////////////////////////////////////////////
using PLAFloat = GRAFloat;
static const PLAFloat kPLAFloatMax = kGRAFloatMax;
static const PLAFloat kPLAFloatUndefined = kGRAFloatUndefined;

//-- Size value --//////////////////////////////////////////////////////////////
using PLASize = GRASize;
static const PLASize kPLASizeMax = kGRASizeMax;
static const PLASize kPLASizeUndefined = kGRASizeUndefined;

//-- Character value --/////////////////////////////////////////////////////////
using PLAChar = GRAChar;
static const PLAChar kPLACharMax = kGRACharMax;
static const PLAChar kPLACharUndefined = kGRACharUndefined;

//-- String value --////////////////////////////////////////////////////////////
using PLAString = GRAString;
static const char *kPLAStrUndefined = kGRAStrUndefined;

//-- OtherValue --//////////////////////////////////////////////////////////////
using PLATimeInterval = GRATimeInterval;
static const PLATimeInterval kPLATimeIntervalMax = kGRATimeIntervalMax;
static const PLATimeInterval kPLATimeIntervalUndefined = kGRATimeIntervalUndefined;

//-- Identifier --//////////////////////////////////////////////////////////////
using PLAId = GRAId;
static const PLAId kPLAIdMax = kGRAIdMax;
static const PLAId kPLAIdUndefined = kGRAIdUndefined;

#endif // PLAIN_ENGINE_PLAOBJTYPE_HPP
