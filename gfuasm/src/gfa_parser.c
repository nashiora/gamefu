#include <gfuasm.h>

bool gfa_parse(gfa_translation_unit* tu, gfa_source* source) {
    assert(tu != NULL && "Must parse into a translation unit");
    assert(tu->primary_source == NULL && "Can only call `gfa_parse` once per translation unit");
    assert(source != NULL && "Can't parse a NULL source");

    bool tu_contains_source = false;
    for (int64_t i = 0, count = lca_da_count(tu->sources); i < count && !tu_contains_source; i++) {
        if (tu->sources[i] == source)
            tu_contains_source = true;
    }

    assert(tu_contains_source && "The translation unit must contain the given source file");

    tu->primary_source = source;

    return !tu->contains_errors;
}
