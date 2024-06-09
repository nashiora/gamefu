/*
 * GameFU Station assembler entry point
 * Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>

#define LCA_IMPLEMENTATION
#include <lca.h>

#include <gfuasm.h>

int main(int argc, char** argv) {
    int exit_code = 0;

    lca_temp_allocator_init(lca_default_allocator, 1024 * 1024);

    gfa_translation_unit* tu = gfa_translation_unit_create(lca_default_allocator);
    assert(tu != NULL);

    gfa_source* source = gfa_read_source_from_file(tu, LCA_SV_CONSTANT("../examples/helloasm/hello.gfuasm"));
    assert(source != NULL);

    gfa_location temploc = {
        .source = source,
        .offset = 0,
        .length = 1,
    };

    (void)gfa_issue(tu, GFA_DEBUG, temploc, "gfuasm");
    (void)gfa_issue(tu, GFA_INFO, temploc, "gfuasm");
    (void)gfa_issue(tu, GFA_WARNING, temploc, "gfuasm");
    (void)gfa_issue(tu, GFA_ERROR, temploc, "gfuasm");

defer:;
    gfa_diagnostics_fprint(tu, stderr);

    gfa_translation_unit_destroy(tu);
    tu = NULL;

    lca_temp_allocator_clear();

    return exit_code;
}
