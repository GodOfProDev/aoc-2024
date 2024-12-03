#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int values[1024];
  int len;
} int_arr;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

int main(void) {
  FILE *file;
  char s[1024];

  int_arr first_arr = {0};
  int_arr second_arr = {0};

  file = fopen("input.txt", "r");

  bool isFirst = false;
  while (fgets(s, sizeof s, file) != NULL) {
    // Remove \n
    if (s[strlen(s) - 1] == '\n') {
      s[strlen(s) - 1] = '\0';
    }
    char *token;
    if ((token = strtok(s, " ")) != NULL) {
      do {
        isFirst = !isFirst;
        if (isFirst) {
          first_arr.values[first_arr.len] = atoi(token);
          first_arr.len++;
        } else {
          second_arr.values[second_arr.len] = atoi(token);
          second_arr.len++;
        }
      } while ((token = strtok(NULL, " ")) != NULL);
    }
  }

  fclose(file);

  bubbleSort(first_arr.values, first_arr.len);
  bubbleSort(second_arr.values, second_arr.len);

  int total_dist = 0;
  for (int i = 0; i < first_arr.len; i++) {
    int a = first_arr.values[i];
    int b = second_arr.values[i];

    int distance = abs(a - b);
    total_dist += distance;
  }

  printf("Total Distance: %d", total_dist);
  return 0;
}
