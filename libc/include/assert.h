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
