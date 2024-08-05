#define CUT_IMPL
#define CUT_ABORT_ON_FAIL
#include "./cut.h"

#include "ftstr.h"

void test_ftstr_from_cstr(const char* cstr) {
    struct ftstr str = ftstr_from_cstr(cstr);
        cut_assert_eqstr(str.value, "Hello, world!");
        cut_assert_eqstr(str.value, "Hello, world!");
        cut_assert_eqstr(str.value, "Hello, world!");
        cut_assert_eqstr(str.value, "Hello, world!");
        cut_assert_eqstr(str.value, "Hello, world!");
        cut_assert_eqstr(str.value, "Hello, world!");
}


int
main(void) {
    CUT_BEGIN;

    test_ftstr_from_cstr("Hello, world!");

    int x = 1;
    int y = 2;
    cut_assert_eq(x, y);



    CUT_END;


    return 0;
}
