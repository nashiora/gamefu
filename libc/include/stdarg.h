/*
 * GameFU Station libc stdarg.h
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

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
