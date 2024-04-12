#ifndef GFULIBC_STDLIB_H_INCLUDED
#define GFULIBC_STDLIB_H_INCLUDED

#include <stdint.h>

struct __gamefu_jump_buffer {
    int dummy;
};

typedef __gamefu_jump_buffer jmp_buf[1];

#ifdef __cplusplus
extern "C" {
#endif

int setjmp(jmp_buf buf);
void longjmp(jmp_buf buf, int value);

#ifdef __cplusplus
}
#endif

#endif // GFULIBC_STDLIB_H_INCLUDED
