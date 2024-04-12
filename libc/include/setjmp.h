/*
 * GameFU Station libc setjmp.h
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GFULIBC_STDLIB_H_INCLUDED
#define GFULIBC_STDLIB_H_INCLUDED

#include <stdint.h>

struct __gamefu_jump_buffer {
    int dummy;
};

typedef struct __gamefu_jump_buffer jmp_buf[1];

#ifdef __cplusplus
extern "C" {
#endif

int setjmp(jmp_buf buf);
void longjmp(jmp_buf buf, int value);

#ifdef __cplusplus
}
#endif

#endif // GFULIBC_STDLIB_H_INCLUDED
