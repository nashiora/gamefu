/*
 * GameFU Station assembler APIs
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GFUASM_GFUASM_H_INCLUDED
#define GFUASM_GFUASM_H_INCLUDED

#include <assert.h>
#include <lca.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum gfa_instruction_kind {
    GFA_INST_ILLEGAL = 0,
    GFA_INST_HALT,
    GFA_INST_INT,
    GFA_INST_MOV,
    GFA_INST_ADD,
    GFA_INST_SUB,
    GFA_INST_PUSH,
    GFA_INST_POP,
} gfa_instruction_kind;

typedef enum gfa_register {
    GFA_REG_A,
    GFA_REG_B,
    GFA_REG_C,
    GFA_REG_D,
} gfa_register;

typedef enum gfa_instruction_parameter_kind {
    GFA_INSTPARAM_REG8HI,
    GFA_INSTPARAM_REG8LO,
    GFA_INSTPARAM_REG16HI,
    GFA_INSTPARAM_REG16LO,
    GFA_INSTPARAM_REG32,
    GFA_INSTPARAM_IMMEDIATE,
    GFA_INSTPARAM_ADDRESS,
} gfa_instruction_parameter_kind;

typedef struct gfa_instruction_parameter {
    gfa_instruction_parameter_kind kind;
    union {
        gfa_register reg;
    };
} gfa_instruction_parameter;

typedef struct gfa_instruction {
    gfa_instruction_kind kind;
} gfa_instruction;

typedef struct gfa_source {
    lca_string_view name;
    lca_string_view text;
} gfa_source;

typedef struct gfa_location {
    gfa_source* source;
    int64_t offset;
    int64_t length;
} gfa_location;

typedef enum gfa_diagnostic_kind {
    GFA_TRACE,
    GFA_DEBUG,
    GFA_INFO,
    GFA_WARNING,
    GFA_ERROR,
    GFA_FATAL,
} gfa_diagnostic_kind;

typedef struct gfa_diagnostic {
    gfa_diagnostic_kind kind;
    gfa_location location;
    lca_string_view message;
} gfa_diagnostic;

typedef struct gfa_translation_unit {
    lca_allocator allocator;

    gfa_source* primary_source;
    lca_da(gfa_source*) sources;

    bool contains_errors;
    lca_da(gfa_diagnostic*) diagnostics;

    lca_arena* string_arena;
    lca_da(lca_string_view) interned_strings;
} gfa_translation_unit;

#ifdef __cplusplus
extern "C" {
#endif

gfa_translation_unit* gfa_translation_unit_create(lca_allocator allocator);
void gfa_translation_unit_destroy(gfa_translation_unit* tu);

lca_string_view gfa_intern(gfa_translation_unit* tu, lca_string_view sv);

gfa_source* gfa_read_source_from_file(gfa_translation_unit* tu, lca_string_view file_name);
gfa_source* gfa_create_source_from_text(gfa_translation_unit* tu, lca_string_view name, lca_string_view text);

gfa_diagnostic* gfa_issue(gfa_translation_unit* tu, gfa_diagnostic_kind kind, gfa_location location, const char* message);
gfa_diagnostic* gfa_issue_format(gfa_translation_unit* tu, gfa_diagnostic_kind kind, gfa_location location, const char* format, ...);
void gfa_diagnostics_fprint(gfa_translation_unit* tu, FILE* stream);

/// @brief Parse the given source file into this translation unit. The source must already
/// be associated with this translation unit.
/// @return True if the translation unit has no errors after parsing, false otherwise.
bool gfa_parse(gfa_translation_unit* tu, gfa_source* source);

#ifdef __cplusplus
}
#endif

#endif // GFUASM_GFUASM_H_INCLUDED
