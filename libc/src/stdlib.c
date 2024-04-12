#include <stdlib.h>
#include <gfuapi.h>

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
