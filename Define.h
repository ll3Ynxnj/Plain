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

#define PLA_PRINT_STR(...) PLADebug::PrintStr(__VA_ARGS__)

#define PLA_PRINT_LOG(...)\
PLADebug::PrintLog("LOG", __FILE__, __LINE__, __VA_ARGS__);

#define PLA_ASSERT(...)\
PLADebug::PrintLog("ASSERT", __FILE__, __LINE__, __VA_ARGS__);\
exit(1);\

#define PLA_DISALLOW_COPY_AND_ASSIGN(aTypeName)\
aTypeName(const aTypeName&);\
void operator=(const aTypeName&)\

#endif // PLAIN_DEFINE_H
