/*
 * GameFU Station libc stdlib.h
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GFULIBC_STDLIB_H_INCLUDED
#define GFULIBC_STDLIB_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int atoi(const char* string);

void* malloc(size_t size);
void* calloc(size_t count, size_t element_size);
void* realloc(void* memory, size_t size);
void free(void* memory);

#ifdef __cplusplus
}
#endif

#endif // GFULIBC_STDLIB_H_INCLUDED
