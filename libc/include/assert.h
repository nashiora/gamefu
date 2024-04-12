/*
 * GameFU Station libc assert.h
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GFULIBC_ASSERT_H_INCLUDED
#define GFULIBC_ASSERT_H_INCLUDED

#ifndef NDEBUG
#    define assert(Expression) ((Expression) ? ((void)0) : __gamefu_assert_abort(__FILE__, __LINE__, #Expression))
#else
#    define assert(Expression) \
        do {                   \
        } while (0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void __gamefu_assert_abort(const char* file_name, int line, const char* expression);

#ifdef __cplusplus
}
#endif

#endif // GFULIBC_ASSERT_H_INCLUDED
