#ifndef GFULIBC_STDDEF_H_INCLUDED
#define GFULIBC_STDDEF_H_INCLUDED

typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int max_align_t;

#define NULL ((void*)0)

#define offsetof(Type, Field) ((size_t)((Type*)NULL)->Field)

#endif // GFULIBC_STDDEF_H_INCLUDED
