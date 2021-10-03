#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_tests.h"
#include "btlv_test_setups.h"

DEFINE_STANDALONE_TEST_FUNC(listGetBeginNullPtr) {
    // Testing all combinations off null pointer passed to parameter
    munit_assert_long(listGetBegin(NULL, NULL), ==, LIST_FAIL);
    munit_assert_long(listGetBegin(NULL, (ListIterator**)1UL), ==, LIST_FAIL);
    munit_assert_long(listGetBegin((List*)1UL, NULL), ==, LIST_FAIL);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetBeginEmptyList, listEmpty) {
    List *list = (List*)user_data_or_fixture;
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 0UL);

    munit_assert_long(listGetBegin(list, &iterator), ==, LIST_FIND_NOT_FOUND);
    munit_assert_null(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetBeginSingleElementList, listSingleElement) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    int singleValue = *(int*)FIXTURE_INDEX(user_data_or_fixture, 1);
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 1UL);

    munit_assert_long(listGetBegin(list, &iterator), ==, LIST_OK);
    munit_assert_not_null(iterator);
    munit_assert_int(*(int*)(iterator->data), ==, singleValue);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetBegin, listFewElements) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    int expectedValue = ((int*)FIXTURE_INDEX(user_data_or_fixture, 1))[0];
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, >, 1UL);

    munit_assert_long(listGetBegin(list, &iterator), ==, LIST_OK);
    munit_assert_not_null(iterator);
    munit_assert_int(*(int*)(iterator->data), ==, expectedValue);

    return MUNIT_OK;
}

// ============

DEFINE_STANDALONE_TEST_FUNC(listGetEndNullPtr) {
    // Testing all combinations off null pointer passed to parameter
    munit_assert_long(listGetEnd(NULL, NULL), ==, LIST_FAIL);
    munit_assert_long(listGetEnd(NULL, (ListIterator**)1UL), ==, LIST_FAIL);
    munit_assert_long(listGetEnd((List*)1UL, NULL), ==, LIST_FAIL);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetEndEmptyList, listEmpty) {
    List *list = (List*)user_data_or_fixture;
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 0UL);

    munit_assert_long(listGetEnd(list, &iterator), ==, LIST_FIND_NOT_FOUND);
    munit_assert_null(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetEndSingleElementList, listSingleElement) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    const int singleValue = *(int*)FIXTURE_INDEX(user_data_or_fixture, 1);
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 1UL);

    munit_assert_long(listGetEnd(list, &iterator), ==, LIST_OK);
    munit_assert_not_null(iterator);
    munit_assert_int(*(int*)(iterator->data), ==, singleValue);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listGetEnd, listFewElements) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    const size_t setupArraySize = *(size_t*)FIXTURE_INDEX(user_data_or_fixture, 2);
    const int expectedValue = ((int*)FIXTURE_INDEX(user_data_or_fixture, 1))[setupArraySize - 1];
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, >, 1UL);

    munit_assert_long(listGetEnd(list, &iterator), ==, LIST_OK);
    munit_assert_not_null(iterator);
    munit_assert_int(*(int*)(iterator->data), ==, expectedValue);

    return MUNIT_OK;
}

// ============

DEFINE_STANDALONE_TEST_FUNC(listFindElementNullPtr) {
    // Testing all combinations off null pointer passed to parameter
    munit_assert_long(listFindElement(NULL, 0UL, NULL), ==, LIST_FAIL);
    munit_assert_long(listFindElement(NULL, 0UL, (ListIterator**)1UL), ==, LIST_FAIL);
    munit_assert_long(listFindElement((List*)1UL, 0UL, NULL), ==, LIST_FAIL);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listFindElementEmptyList, listEmpty) {
    List *list = (List*)user_data_or_fixture;
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 0UL);

    munit_assert_long(listFindElement(list, 0UL, &iterator), ==, LIST_OUT_OF_BOUNDS);
    munit_assert_null(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listFindElementOutOfBounds, listSingleElement) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, 1UL);

    munit_assert_long(listFindElement(list, 1UL, &iterator), ==, LIST_OUT_OF_BOUNDS);
    munit_assert_null(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listFindElement, listFewElements) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    const int *setupArray = (int*)FIXTURE_INDEX(user_data_or_fixture, 1);
    const size_t setupArraySize = *(size_t*)FIXTURE_INDEX(user_data_or_fixture, 2);
    ListIterator *iterator = NULL;

    munit_assert_not_null(list);
    munit_assert_ulong(list->elementsCount, ==, setupArraySize);

    for(size_t i = 0; i < setupArraySize; ++i) {
        munit_assert_long(listFindElement(list, i, &iterator), ==, LIST_OK);
        munit_assert_not_null(iterator);
        munit_assert_int(*((int*)iterator->data), ==, setupArray[i]);

        free(iterator);
    }

    return MUNIT_OK;
}

// ============

DEFINE_STANDALONE_TEST_FUNC(listMoveNextNullPtr) {
    munit_assert_long(listMoveNext(NULL), ==, LIST_FAIL);

    ListIterator *iterator = createIterator(NULL, NULL);
    munit_assert_long(listMoveNext(iterator), ==, LIST_FAIL);
    free(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listMoveNextReachEnd, listSingleElement) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    ListIterator *iterator = createIterator(list->lastNode->data, list->lastNode);

    if(iterator == NULL)
        return MUNIT_ERROR;

    munit_assert_long(listMoveNext(iterator), ==, LIST_ITERATOR_END_REACHED);
    munit_assert_not_null(iterator->data);
    munit_assert_ptr_equal(iterator->data, list->lastNode->data);
    munit_assert_not_null(iterator->currentNode);
    munit_assert_ptr_equal(iterator->currentNode, list->lastNode);
    free(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listMoveNext, listFewElements) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    const int *setupArray = (int*)FIXTURE_INDEX(user_data_or_fixture, 1);
    const size_t setupArraySize = *(size_t*)FIXTURE_INDEX(user_data_or_fixture, 2);
    ListIterator *iterator = createIterator(list->firstNode->data, list->firstNode);

    if(iterator == NULL)
        return MUNIT_ERROR;

    for(size_t i = 1; i < setupArraySize; ++i) {
        munit_assert_long(listMoveNext(iterator), ==, LIST_OK);
        munit_assert_not_null(iterator->data);
        munit_assert_not_null(iterator->currentNode);
        munit_assert_int(setupArray[i], ==, *(int*)(iterator->data));
    }

    free(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_STANDALONE_TEST_FUNC(listMoveBackNullPtr) {
    munit_assert_long(listMoveBack(NULL), ==, LIST_FAIL);

    ListIterator *iterator = createIterator(NULL, NULL);
    munit_assert_long(listMoveBack(iterator), ==, LIST_FAIL);
    free(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listMoveBackReachEnd, listSingleElement) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    ListIterator *iterator = createIterator(list->firstNode->data, list->firstNode);

    if(iterator == NULL)
        return MUNIT_ERROR;

    munit_assert_long(listMoveBack(iterator), ==, LIST_ITERATOR_BEGIN_REACHED);
    munit_assert_not_null(iterator->data);
    munit_assert_ptr_equal(iterator->data, list->firstNode->data);
    munit_assert_not_null(iterator->currentNode);
    munit_assert_ptr_equal(iterator->currentNode, list->firstNode);
    free(iterator);

    return MUNIT_OK;
}

// ============

DEFINE_FULL_TEST_FUNC(listMoveBack, listFewElements) {
    List *list = (List*)FIXTURE_INDEX(user_data_or_fixture, 0);
    const int *setupArray = (int*)FIXTURE_INDEX(user_data_or_fixture, 1);
    const size_t setupArraySize = *(size_t*)FIXTURE_INDEX(user_data_or_fixture, 2);
    ListIterator *iterator = createIterator(list->lastNode->data, list->lastNode);

    if(iterator == NULL)
        return MUNIT_ERROR;

    for(int i = setupArraySize - 2; i >= 0; --i) {
        munit_assert_long(listMoveBack(iterator), ==, LIST_OK);
        munit_assert_not_null(iterator->data);
        munit_assert_not_null(iterator->currentNode);
        munit_assert_int(setupArray[(size_t)i], ==, *(int*)(iterator->data));
    }

    free(iterator);

    return MUNIT_OK;
}

// =================
// == TEST ARRAYS ==
// =================

static MunitTest btlvTests[] = {
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetBegin-nullPtr", listGetBeginNullPtr),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetBegin-emptyList", listGetBeginEmptyList),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetBegin-singleElementList", listGetBeginSingleElementList),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetBegin-fewElementsList", listGetBegin),

    GET_TEST_FUNC_ARRAY_ENTRY("/listGetEnd-nullPtr", listGetEndNullPtr),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetEnd-emptyList", listGetEndEmptyList),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetEnd-singleElementList", listGetEndSingleElementList),
    GET_TEST_FUNC_ARRAY_ENTRY("/listGetEnd-fewElementsList", listGetEnd),

    GET_TEST_FUNC_ARRAY_ENTRY("/listFindElement-nullPtr", listFindElementNullPtr),
    GET_TEST_FUNC_ARRAY_ENTRY("/listFindElement-emptyList", listFindElementEmptyList),
    GET_TEST_FUNC_ARRAY_ENTRY("/listFindElement-outOfBounds", listFindElementOutOfBounds),
    GET_TEST_FUNC_ARRAY_ENTRY("/listFindElement-fewElementsList", listFindElement),

    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveNext-nullPtr", listMoveNextNullPtr),
    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveNext-endReached", listMoveNextReachEnd),
    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveNext-fewElementsList", listMoveNext),

    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveBack-nullPtr", listMoveBackNullPtr),
    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveBack-endReached", listMoveBackReachEnd),
    GET_TEST_FUNC_ARRAY_ENTRY("/listMoveBack-fewElementsList", listMoveBack),

    TEST_FUNC_ARRAY_END
};

static MunitSuite btlvTestsSuite = {
    "/nullptr",
    btlvTests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

MunitSuite btlvNullptrTestsGetSuite(void) {
    return btlvTestsSuite;
}