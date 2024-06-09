/*
 * GameFU Station Emulator (GFUSX) APIs
 * Copyright (C) 2024 GFUSX Dev Team - GPLv3 Licensed
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GFUSX_GFUSX_H_INCLUDED
#define GFUSX_GFUSX_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define GFUSX_GENERAL_REGISTER_COUNT 8
#define GFUSX_STACK_SIZE_MAX 1024

typedef int gfusx_register_t;

typedef struct gfusx_stack_value {

} gfusx_stack_value;

typedef struct gfusx_stack {
    int count;
    gfusx_stack_value values[GFUSX_STACK_SIZE_MAX];
} gfusx_stack;

typedef struct gfusx_machine {
    gfusx_register_t r[GFUSX_GENERAL_REGISTER_COUNT];

    gfusx_stack stack;
    gfusx_stack os_stack;
} gfusx_machine;

#ifdef __cplusplus
}
#endif

#endif // GFUSX_GFUSX_H_INCLUDED
