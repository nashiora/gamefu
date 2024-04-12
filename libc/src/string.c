/*
 * GameFU Station libc string.c
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* destination, const void* source, size_t count);
void* memmove(void* destination, const void* source, size_t count);
int memcmp(const void* ptr1, const void* ptr2, size_t count);

void* memchr(const void* ptr, int value, size_t count) {
    const char* readable = (const char*)ptr;

    for (size_t i = 0; i < count; i++) {
        if (readable[i] == value) {
            return ptr + i;
        }
    }

    return NULL;
}

void memset(void* ptr, int value, size_t count) {
    char* writable = (char*)ptr;
    char char_value = (char)value;

    for (size_t i = 0; i < count; i++) {
        writable[i] = char_value;
    }
}

char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t count);
char* strcat(char* destination, const char* source);
char* strncat(char* destination, const char* source, size_t count);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t count);
char* strchr(const char* source, int character);
char* strrchr(const char* source, int character);
size_t strspn(const char* str1, const char* str2);
size_t strcspn(const char* str1, const char* str2);
char* strpbrk(const char* str1, const char* str2);
char* strstr(const char* str1, const char* str2);
char* strtok(char* str, const char* delimiters);
size_t strlen(const char* str);

char* strerror(int errorno_value);

#ifdef __cplusplus
}
#endif
