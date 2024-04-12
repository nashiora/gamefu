#ifndef GFULIBC_STDARG_H_INCLUDED
#define GFULIBC_STDARG_H_INCLUDED

struct __gamefu_va_list {
    int dummy;
};

typedef struct __gamefu_va_list va_list;

#define va_start(VAList, LastParam) do { } while (0)
#define va_end(VAList) do { } while (0)
#define va_arg(VAList, ArgType) do { } while (0)
#define va_copy(DestVAList, SourceVAList) do { } while (0)

#endif // GFULIBC_STDARG_H_INCLUDED
