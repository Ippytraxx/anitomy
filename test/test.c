#include "anitomyc.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_FNAME "Ghost_in_the_Shell_Stand_Alone_Complex_2nd_GIG_Ep05v2_EXCAVATION_[720p,HDTV,x264,AAC_5.1]_-_THORA.mkv"

static Anitomy* anitomy;

static void
setup()
{
    anitomy = anitomy_new();
}

static void
cleanup()
{
    anitomy_free(anitomy);
}

START_TEST(test_anitomy_new)
{
    ck_assert_ptr_ne(anitomy, NULL);
}
END_TEST

START_TEST(test_anitomy_parse)
{
    int ret;

    anitomy = anitomy_new();
    ret = anitomy_parse(anitomy, TEST_FNAME);

    ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_anitomy_elements)
{
    AnitomyElements* elements;

    anitomy_parse(anitomy, TEST_FNAME);

    elements = anitomy_elements(anitomy);

    ck_assert_ptr_ne(elements, NULL);
}
END_TEST

START_TEST(test_anitomy_elements_get_all)
{
    AnitomyElements* elements;
    char** names;

    anitomy_parse(anitomy, TEST_FNAME);

    elements = anitomy_elements(anitomy);
    
    names = anitomy_elements_get_all(elements, AnitomyElementAudioTerm);

    ck_assert_str_eq(names[0], "AAC");
    ck_assert_str_eq(names[1], "5.1");
    ck_assert_ptr_eq(names[2], NULL);
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

    tcase_add_checked_fixture(core, setup, cleanup);
    tcase_add_test(core, test_anitomy_new);
    tcase_add_test(core, test_anitomy_parse);
    tcase_add_test(core, test_anitomy_elements);
    tcase_add_test(core, test_anitomy_elements_get_all);
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
