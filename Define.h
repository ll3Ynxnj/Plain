#ifndef PLAIN_DEFINE_H
#define PLAIN_DEFINE_H

#define PLA_DELETE(aPtr)\
{\
    delete (aPtr); (aPtr) = 0;\
}\

#define PLA_DELETE_ARRAY(aPtr)\
{\
    delete[] (aPtr); (aPtr) = 0;\
}\

#define PLA_PRINT(...)\
PLADebug::Print(__VA_ARGS__)\

#define PLA_TRACE(...)\
PLADebug::Trace(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define PLA_ASSERT(...)\
PLADebug::Assert(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)\

#define PLA_DISALLOW_COPY_AND_ASSIGN(aTypeName)\
aTypeName(const aTypeName&);\
void operator=(const aTypeName&)\

#endif // PLAIN_DEFINE_H
