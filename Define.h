#ifndef PLAIN_DEFINE_H
#define PLAIN_DEFINE_H

#define SAFE_DELETE(p)\
{\
    delete (p); (p) = 0;\
}\

#define SAFE_DELETE_ARRAY(p)\
{\
    delete[] (p); (p) = 0;\
}\

#define DISALLOW_COPY_AND_ASSIGN(TypeName)\
TypeName(const TypeName&);\
void operator=(const TypeName&)\

#endif // PLAIN_DEFINE_H
