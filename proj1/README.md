# Unit Tests

## Preflight Info

When weights are equal the test cases have the terms sorted in ascending lexicographic order. (on piazza it says you can do whatever you want)

## How to use:

Copy your own autocomplete.c into this directory.

Compile the unit tests with:

```ps
gcc -o test.exe .\case_tester.c .\autocomplete.c .\cases\cities_sorted.c .\cases\cities_cases.c .\cases\wiktionary_sorted.c .\cases\wiktionary_cases.c
```

run test.exe to run unit tests.

## Error message diagnoses

```
  Case NAME:
    case_tester.c:64: Check strcmp(answer[j].term, tests[j].term) == 0... failed
      LINE NAME Expected: WHAT MY CODE DOES
      LINE NAME Produced: WHAT YOUR CODE DOES
```

`NAME` The name of the case that failed

`LINE` What case number failed (or line in TESTCASEFILE.c that failed relative to where it actually is in the file)

## FAQ

Q: i got an error
A: either i am wrong or you are

Q: i think you are wrong
A: tell me why and i will check

Q: i think i am wrong
A: relatable

Q: make more tests
A: submit test ideas, or try to read my code to add more

Q: your code is bad
A: yes

Q: i could make it better
A: please