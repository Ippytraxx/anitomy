#include "anitomyc.h"
#include <check.h>
#include <stdlib.h>

#define TEST_FNAME "[Ouroboros]_Fullmetal_Alchemist_Brotherhood_-_01.mkv"

START_TEST(test_anitomy_new)
{
    Anitomy* anitomy;

    anitomy = anitomy_new();

    ck_assert_ptr_ne(anitomy, NULL);
}
END_TEST

START_TEST(test_anitomy_parse)
{
    Anitomy* anitomy;
    int ret;

    anitomy = anitomy_new();
    ret = anitomy_parse(anitomy, TEST_FNAME);

    ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_anitomy_elements)
{
    Anitomy* anitomy;
    AnitomyElements* elements;

    anitomy = anitomy_new();
    anitomy_parse(anitomy, TEST_FNAME);

    elements = anitomy_elements(anitomy);

    ck_assert_ptr_ne(elements, NULL);
}
END_TEST

Suite* anitomy_suite()
{
    Suite* s;
    TCase* core;
    TCase* parser;

    s = suite_create("anitomy");

    core = tcase_create("core");
    parser = tcase_create("parser");

    tcase_add_test(core, test_anitomy_new);
    tcase_add_test(core, test_anitomy_parse);
    tcase_add_test(core, test_anitomy_elements);
    suite_add_tcase(s, core);
    suite_add_tcase(s, parser);

    return s;
}

int main()
{
    Suite* s;
    SRunner* r;
    int ret;

    s = anitomy_suite();
    r = srunner_create(s);

    srunner_run_all(r, CK_NORMAL);
    ret = srunner_ntests_failed(r);
    srunner_free(r);

    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
