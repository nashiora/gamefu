#include <stdarg.h>
#include <gfuasm.h>

gfa_translation_unit* gfa_translation_unit_create(lca_allocator allocator) {
    gfa_translation_unit* tu = lca_allocate(allocator, sizeof *tu);
    assert(tu != NULL);
    tu->allocator = allocator;
    tu->string_arena = lca_arena_create(allocator, 64 * 1024 * 1024);
    assert(tu->string_arena != NULL);
    return tu;
}

void gfa_translation_unit_destroy(gfa_translation_unit* tu) {
    if (tu == NULL) {
        return;
    }

    lca_allocator allocator = tu->allocator;

    for (int64_t i = 0, count = lca_da_count(tu->sources); i < count; i++) {
        lca_deallocate(allocator, tu->sources[i]);
    }
    lca_da_free(tu->sources);

    for (int64_t i = 0, count = lca_da_count(tu->diagnostics); i < count; i++) {
        lca_deallocate(allocator, tu->diagnostics[i]);
    }
    lca_da_free(tu->diagnostics);

    lca_arena_destroy(tu->string_arena);
    lca_da_free(tu->interned_strings);

    memset(tu, 0, sizeof *tu);
    lca_deallocate(allocator, tu);
}

lca_string_view gfa_intern(gfa_translation_unit* tu, lca_string_view sv) {
    assert(tu != NULL);
    assert(tu->string_arena != NULL);

    for (int64_t i = 0, count = lca_da_count(tu->interned_strings); i < count; i++) {
        if (lca_string_view_equals(sv, tu->interned_strings[i]))
            return tu->interned_strings[i];
    }

    char* interned_string = lca_arena_push(tu->string_arena, sv.count + 1);
    assert(interned_string != NULL);
    memcpy(interned_string, sv.data, (size_t)sv.count);

    lca_string_view interned_view = {
        .data = interned_string,
        .count = sv.count,
    };

    lca_da_push(tu->interned_strings, interned_view);
    return interned_view;
}

gfa_source* gfa_read_source_from_file(gfa_translation_unit* tu, lca_string_view file_name) {
    assert(tu != NULL);
    assert(tu->string_arena != NULL);

    char* file_name_cstring = lca_string_view_to_cstring(tu->allocator, file_name);
    lca_string file_text_string = lca_file_read(tu->allocator, file_name_cstring);
    lca_deallocate(tu->allocator, file_name_cstring);
    lca_string_view file_text = gfa_intern(tu, lca_string_as_view(file_text_string));
    lca_string_destroy(&file_text_string);

    gfa_source* source = lca_allocate(tu->allocator, sizeof *source);
    assert(source != NULL);
    source->name = gfa_intern(tu, file_name);
    source->text = file_text;
    lca_da_push(tu->sources, source);

    return source;
}

gfa_source* gfa_create_source_from_text(gfa_translation_unit* tu, lca_string_view name, lca_string_view text) {
    assert(tu != NULL);
    assert(tu->string_arena != NULL);

    gfa_source* source = lca_allocate(tu->allocator, sizeof *source);
    assert(source != NULL);
    source->name = gfa_intern(tu, name);
    source->text = gfa_intern(tu, text);
    lca_da_push(tu->sources, source);

    return source;
}

gfa_diagnostic* gfa_issue(gfa_translation_unit* tu, gfa_diagnostic_kind kind, gfa_location location, const char* message) {
    assert(tu != NULL);
    assert(tu->string_arena != NULL);

    gfa_diagnostic* diag = lca_allocate(tu->allocator, sizeof *diag);
    assert(diag != NULL);
    lca_da_push(tu->diagnostics, diag);
    tu->contains_errors |= kind >= GFA_ERROR;

    diag->kind = kind;
    diag->location = location;
    diag->message = gfa_intern(tu, lca_string_view_from_cstring(message));

    return diag;
}

gfa_diagnostic* gfa_issue_format(gfa_translation_unit* tu, gfa_diagnostic_kind kind, gfa_location location, const char* format, ...) {
    assert(tu != NULL);
    assert(tu->string_arena != NULL);

    gfa_diagnostic* diag = lca_allocate(tu->allocator, sizeof *diag);
    assert(diag != NULL);
    lca_da_push(tu->diagnostics, diag);
    tu->contains_errors |= kind >= GFA_ERROR;

    diag->kind = kind;
    diag->location = location;

    va_list v;
    va_start(v, format);
    diag->message = lca_string_as_view(lca_string_vformat(format, v));
    va_end(v);

    return diag;
}

void gfa_diagnostics_fprint(gfa_translation_unit* tu, FILE* stream) {
    assert(tu != NULL);

    for (int64_t i = 0, count = lca_da_count(tu->diagnostics); i < count; i++) {
        if (i > 0) {
            fprintf(stream, "\n");
        }

        gfa_diagnostic* diag = tu->diagnostics[i];
        assert(diag != NULL);

        assert(diag->location.source != NULL);

        fprintf(stream, ANSI_COLOR_BRIGHT_BLACK "%.*s", LCA_STR_EXPAND(diag->location.source->name));
        fprintf(stream, ":[%ld]", diag->location.offset);

        switch (diag->kind) {
            default: assert(false && "unreachable"); break;
            case GFA_TRACE: fprintf(stream, ": " ANSI_COLOR_YELLOW "Trace"); break;
            case GFA_DEBUG: fprintf(stream, ": " ANSI_COLOR_CYAN "Debug"); break;
            case GFA_INFO: fprintf(stream, ": " ANSI_COLOR_WHITE "Trace"); break;
            case GFA_WARNING: fprintf(stream, ": " ANSI_COLOR_MAGENTA "Warning"); break;
            case GFA_ERROR: fprintf(stream, ": " ANSI_COLOR_RED "Error"); break;
            case GFA_FATAL: fprintf(stream, ": " ANSI_COLOR_YELLOW "Fatal"); break;
        }

        fprintf(stream, ANSI_COLOR_RESET ": ");
        fprintf(stream, "%.*s\n", LCA_STR_EXPAND(diag->message));
    }
}
