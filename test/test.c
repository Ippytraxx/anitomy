#include "anitomyc.h"
#include "test.h"
#include <json-glib/json-glib.h>
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_FNAME "Ghost_in_the_Shell_Stand_Alone_Complex_2nd_GIG_Ep05v2_EXCAVATION_[720p,HDTV,x264,AAC_5.1]_-_THORA.mkv"

static Anitomy* anitomy;
static Anitomy* anitomy_core;
static JsonParser* parse;
static JsonArray* sample_array;

static void
setup_core()
{
    anitomy = anitomy_new();
}

static void
cleanup_core()
{
    anitomy_free(anitomy);
}

static void
setup_parser()
{
    JsonParser* parse;
    JsonNode* root;

    anitomy = anitomy_new();

    parse = json_parser_new();
    json_parser_load_from_data(parse, JSON_SAMPLE_DATA, -1, NULL);

    root = json_parser_get_root(parse);
    sample_array = json_node_get_array(root);
}

static void
cleanup_parser()
{
    anitomy_free(anitomy);
    /* g_object_unref(parse); */
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

START_TEST(test_anitomy_elements_size)
{
    AnitomyElements* elements;

    anitomy_parse(anitomy, TEST_FNAME);

    elements = anitomy_elements(anitomy);

    ck_assert_int_eq(anitomy_elements_size(elements), 12);
}
END_TEST

START_TEST(test_anitomy_elements_get_all)
{
    AnitomyElements* elements;
    char** names;

    anitomy_parse(anitomy, TEST_FNAME);

    elements = anitomy_elements(anitomy);
    
    names = anitomy_elements_get_all(elements, ANITOMY_ELEMENT_AUDIO_TERM);

    ck_assert_str_eq(names[0], "AAC");
    ck_assert_str_eq(names[1], "5.1");
    ck_assert_ptr_eq(names[2], NULL);
}
END_TEST

START_TEST(test_anitomy_parser_sample_data)
{
    AnitomyElements* elements;

    JsonObject* data = json_array_get_object_element(sample_array, _i);
    const char* fname;

    fname = json_object_get_string_member(data, "file_name");

    anitomy_parse(anitomy, fname);
    elements = anitomy_elements(anitomy);
    
    //TODO: Handle arrays

    if (json_object_has_member(data, "anime_title"))
    {
        const char* actual = json_object_get_string_member(data, "anime_title");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_ANIME_TITLE);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed anime title: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "file_checksum"))
    {
        const char* actual = json_object_get_string_member(data, "file_checksum");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_FILE_CHECKSUM);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed file checksum: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "file_extension"))
    {
        const char* actual = json_object_get_string_member(data, "file_extension");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_FILE_EXTENSION);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed file extension: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "release_group") && 
        !JSON_NODE_HOLDS_ARRAY(json_object_get_member(data, "release_group")))
    {
        const char* actual = json_object_get_string_member(data, "release_group");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_RELEASE_GROUP);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed release group: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "anime_year"))
    {
        const char* actual = json_object_get_string_member(data, "anime_year");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_ANIME_YEAR);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed anime year: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "episode_title"))
    {
        const char* actual = json_object_get_string_member(data, "episode_title");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_EPISODE_TITLE);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed episode title: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "video_resolution"))
    {
        const char* actual = json_object_get_string_member(data, "video_resolution");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_VIDEO_RESOLUTION);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed video resolution: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "source"))
    {
        const char* actual = json_object_get_string_member(data, "source");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_SOURCE);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed source: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "audio_term") && 
        !JSON_NODE_HOLDS_ARRAY(json_object_get_member(data, "audio_term")))
    {
        const char* actual = json_object_get_string_member(data, "audio_term");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_AUDIO_TERM);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed audio term: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
    if (json_object_has_member(data, "video_term") && 
        !JSON_NODE_HOLDS_ARRAY(json_object_get_member(data, "video_term")))
    {
        const char* actual = json_object_get_string_member(data, "video_term");
        char* parsed = anitomy_elements_get(elements, ANITOMY_ELEMENT_VIDEO_TERM);
        ck_assert_msg(strcmp(actual, parsed) == 0, 
                      "Failed video term: actual = %s, parsed = %s, filename = %s", actual, parsed, fname);
        free(parsed);
    }
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

    tcase_add_checked_fixture(core, setup_core, cleanup_core);
    tcase_add_unchecked_fixture(parser, setup_parser, cleanup_parser);
    tcase_add_test(core, test_anitomy_new);
    tcase_add_test(core, test_anitomy_parse);
    tcase_add_test(core, test_anitomy_elements);
    tcase_add_test(core, test_anitomy_elements_size);
    tcase_add_test(core, test_anitomy_elements_get_all);
    tcase_add_loop_test(parser, test_anitomy_parser_sample_data, 0, 162);
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
