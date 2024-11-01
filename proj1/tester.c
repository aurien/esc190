#include <stdio.h>
#include <string.h>

int main() {
  char str1[] = "Hella", str2[] = "Hello", str3[] = "Hell", str4[] = "Help";
  int result;

  // comparing strings str1 and str2
  result = strcmp(str1, str3);
  printf("strcmp(str1, str2) = %d\n", result);

  // comparing strings str1 and str3
  result = strcmp(str2, str3);
  printf("strcmp(str1, str3) = %d\n", result);

  // comparing strings str1 and str3
  result = strcmp(str4, str3);
  printf("strcmp(str1, str3) = %d\n", result);

  return 0;
}