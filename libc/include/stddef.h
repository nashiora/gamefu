/*
 * GameFU Station libc stddef.h
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GFULIBC_STDDEF_H_INCLUDED
#define GFULIBC_STDDEF_H_INCLUDED

typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int max_align_t;

#define NULL ((void*)0)

#define offsetof(Type, Field) ((size_t)((Type*)NULL)->Field)

#endif // GFULIBC_STDDEF_H_INCLUDED
