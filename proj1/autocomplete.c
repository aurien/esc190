#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct term {
  char term[200]; // assume terms are not longer than 200
  double weight;
} term;

int compare(const void *a, const void *b) {
  return strcmp((*(const term *)a).term, (*(const term *)b).term);
}

void read_in_terms(term **terms, int *pnterms, char *filename) {
  char line[200];
  if (fopen(filename, "r") == NULL)
    printf("Error opening file %s\n", filename);
  else {

    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);
    *terms = malloc(sizeof(struct term) * (*pnterms));
    for (int i = 0; i < *pnterms; i++) {
      fgets(line, sizeof(line), fp);
      char *store = strtok(line, "\t");
      (*terms)[i].weight = atof(store);
      strcpy((*terms)[i].term, strtok(NULL, "\r\n"));
    }
    qsort(*terms, *pnterms, sizeof(struct term), compare);
  }
}

int lowest_match(term *terms, int nterms, char *substr) {
  int min = -1;
  int l = 0;
  int r = nterms - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (strcmp(terms[m].term, substr) >= 0 &&
        strncmp(substr, (terms)[m].term, strlen(substr)) == 0) {
      min = m;
      r = m - 1;
    } else if (strncmp(substr, (terms)[m].term, strlen(substr)) < 0) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return min;
}

int highest_match(struct term *terms, int nterms, char *substr) {
  int max = -2;
  int l = 0;
  int r = nterms - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (strcmp(terms[m].term, substr) >= 0 &&
        strncmp(substr, (terms)[m].term, strlen(substr)) == 0) {
      max = m;
      l = m + 1;
    } else if (strncmp(substr, (terms)[m].term, strlen(substr)) < 0) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return max;
}

int wcmp(const void *a, const void *b) {
  if ((*(const term *)b).weight == (*(const term *)a).weight) {
    return strcmp((*(const term *)a).term, (*(const term *)b).term);
  }
  return ((*(const term *)b).weight - (*(const term *)a).weight);
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms,
                  char *substr) {
  int lex_low = lowest_match(terms, nterms, substr);
  int lex_high = highest_match(terms, nterms, substr);

  if (lex_high == -1 && lex_low == -1) {
    *n_answer = 0;
  } else {
    *n_answer = lex_high - lex_low + 1;
  }
  *answer = malloc(sizeof(struct term) * (*n_answer));

  for (int i = 0; i < *n_answer; i++) {
    strcpy((*answer)[i].term, (terms)[i + lex_low].term);
    (*answer)[i].weight = (terms)[i + lex_low].weight;
  }
  qsort(*answer, *n_answer, sizeof(struct term), wcmp);
}
