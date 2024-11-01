#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"
#include "./cases/cases.h"
#include "acutest.h"

#define CITIES "cities.txt"
#define CITIESNAME "Cities"
#define WIKI "wiktionary.txt"
#define WIKINAME "Wiki"

#define CITIES_OUT "cases/cities_sorted.c"
#define WIKI_OUT "cases/wiktionary_sorted.c"

#define CITIES_TEST_CASES "cases/cities_cases.c"
#define WIKI_TEST_CASES "cases/wiktionary_cases.c"

#define ENDCASE "i don't really know a better way to do this"
#define EMPTYCASE "{\"AUTOCOMPLETE RETURNS EMPTY 0 VALUES THIS IS NOT A VALUE\", 0.}"

void testSorted(char *file, struct term *tests, int length)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, file);

    TEST_CASE(file);
    TEST_CHECK(nterms == length);
    TEST_MSG("Sorted lists are not same length");

    if (nterms == length) {
        for (int i = 0; i < nterms; i++) {
            TEST_CASE(file);
            TEST_CHECK(strcmp(terms[i].term, tests[i].term) == 0);
            TEST_MSG("%d Expected term: %s", i, tests[i].term);
            TEST_MSG("%d Produced term: %s", i, terms[i].term);
            TEST_CHECK(terms[i].weight == tests[i].weight);
            TEST_MSG("%d Expected weight: %f : from %s", i, tests[i].weight, tests[i].term);
            TEST_MSG("%d Produced weight: %f : from %s", i, terms[i].weight, terms[i].term);
        }
    }

    free(terms);
}

void testAutocomplete(struct term *terms, int nterms, struct term *tests, int length, char *testCase)
{
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, testCase);

    TEST_CASE(testCase);
    TEST_CHECK((n_answer == length || (n_answer == 0) && (length == 1)));
    TEST_MSG("Autocomplete lists are not same length");


    if (n_answer == length) {
        for (int j = 0; j < n_answer; j++) {
            TEST_CASE(testCase);
            TEST_CHECK(strcmp(answer[j].term, tests[j].term) == 0);
            TEST_MSG("%d %s Expected term: %s", j, testCase, tests[j].term);
            TEST_MSG("%d %s Produced term: %s", j, testCase, answer[j].term);
        }
    }

    free(answer);
}

void testCitiesSorted()
{
    testSorted(CITIES, &CitiesSorted[0], (sizeof CitiesSorted) / (sizeof CitiesSorted[0]));
}

void testWiktionarySorted()
{
    testSorted(WIKI, &WikiSorted[0], (sizeof WikiSorted) / (sizeof WikiSorted[0]));
}

void testCitiesCases()
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, CITIES);

    testAutocomplete(terms, nterms, &TorCases[0], (sizeof TorCases) / (sizeof TorCases[0]), "Tor");
    testAutocomplete(terms, nterms, &CockCases[0], (sizeof CockCases) / (sizeof CockCases[0]), "Cock");
    testAutocomplete(terms, nterms, &noCityWithThisNameCases[0], (sizeof noCityWithThisNameCases) / (sizeof noCityWithThisNameCases[0]), "noCityWithThisName");
    testAutocomplete(terms, nterms, &BruCases[0], (sizeof BruCases) / (sizeof BruCases[0]), "Bru");
    testAutocomplete(terms, nterms, &PenCases[0], (sizeof PenCases) / (sizeof PenCases[0]), "Pen");
    testAutocomplete(terms, nterms, &DickCases[0], (sizeof DickCases) / (sizeof DickCases[0]), "Dick");
    testAutocomplete(terms, nterms, &LosCases[0], (sizeof LosCases) / (sizeof LosCases[0]), "Los");
    testAutocomplete(terms, nterms, &CamCases[0], (sizeof CamCases) / (sizeof CamCases[0]), "Cam");
    testAutocomplete(terms, nterms, &TabonCases[0], (sizeof TabonCases) / (sizeof TabonCases[0]), "Tabon");
    testAutocomplete(terms, nterms, &LigCases[0], (sizeof LigCases) / (sizeof LigCases[0]), "Lig");
    testAutocomplete(terms, nterms, &BallCases[0], (sizeof BallCases) / (sizeof BallCases[0]), "Ball");
    testAutocomplete(terms, nterms, &HiCases[0], (sizeof HiCases) / (sizeof HiCases[0]), "Hi");
    testAutocomplete(terms, nterms, &HellCases[0], (sizeof HellCases) / (sizeof HellCases[0]), "Hell");

    free(terms);
}

void testWiktionaryCases()
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, WIKI);

    testAutocomplete(terms, nterms, &susCases[0], (sizeof susCases) / (sizeof susCases[0]), "sus");
    testAutocomplete(terms, nterms, &impoCases[0], (sizeof impoCases) / (sizeof impoCases[0]), "impo");
    testAutocomplete(terms, nterms, &apCases[0], (sizeof apCases) / (sizeof apCases[0]), "ap");
    testAutocomplete(terms, nterms, &deCases[0], (sizeof deCases) / (sizeof deCases[0]), "de");
    testAutocomplete(terms, nterms, &beCases[0], (sizeof beCases) / (sizeof beCases[0]), "be");
    testAutocomplete(terms, nterms, &treCases[0], (sizeof treCases) / (sizeof treCases[0]), "tre");
    testAutocomplete(terms, nterms, &thCases[0], (sizeof thCases) / (sizeof thCases[0]), "th");
    testAutocomplete(terms, nterms, &canCases[0], (sizeof canCases) / (sizeof canCases[0]), "can");
    testAutocomplete(terms, nterms, &dickCases[0], (sizeof dickCases) / (sizeof dickCases[0]), "dick");
    testAutocomplete(terms, nterms, &ballsCases[0], (sizeof ballsCases) / (sizeof ballsCases[0]), "balls");
    testAutocomplete(terms, nterms, &neverCases[0], (sizeof neverCases) / (sizeof neverCases[0]), "never");
    testAutocomplete(terms, nterms, &goingCases[0], (sizeof goingCases) / (sizeof goingCases[0]), "going");
    testAutocomplete(terms, nterms, &toCases[0], (sizeof toCases) / (sizeof toCases[0]), "to");
    testAutocomplete(terms, nterms, &giveCases[0], (sizeof giveCases) / (sizeof giveCases[0]), "give");
    testAutocomplete(terms, nterms, &youCases[0], (sizeof youCases) / (sizeof youCases[0]), "you");
    testAutocomplete(terms, nterms, &upCases[0], (sizeof upCases) / (sizeof upCases[0]), "up");
    testAutocomplete(terms, nterms, &momCases[0], (sizeof momCases) / (sizeof momCases[0]), "mom");

    free(terms);
}

TEST_LIST = {
    {"Cities Sorted", testCitiesSorted},
    {"Wiktionary Sorted", testWiktionarySorted},
    {"Cities Cases", testCitiesCases},
    {"Wiktionary Cases", testWiktionaryCases},
    {NULL, NULL}
};