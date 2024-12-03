#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char line[128];

    char *token;
    int total_safe = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove \n
        char lf = line[strlen(line) - 1];
        if (lf == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        if ((token = strtok(line, " ")) != NULL) {
            int num_1 = -1;
            int num_2 = -1;
            int counter = 0;
            bool overall_increasing = false;
            bool is_first_time = true;
            bool is_second_time = false;
            bool is_safe = true;
            do {
                counter++;

                if (counter == 1 && num_1 == -1) {
                    num_1 = atoi(token);
                } else if (counter == 2 && num_2 == -1) {
                    num_2 = atoi(token);
                } else {
                    num_1 = num_2;
                    num_2 = atoi(token);
                }

                if(is_first_time) {
                    is_first_time = false;
                    is_second_time = true;
                    continue;
                }

                int diff = num_2 - num_1;
                if (!(abs(diff) >= 1 && abs(diff) <= 3)) {
                    is_safe = false;
                    break;
                }

                bool currently_increasing = (diff > 0) ? true : false;
                counter = 0;

                if (is_second_time) {
                    is_second_time = false;
                    overall_increasing = currently_increasing;
                    continue;
                }

                if (currently_increasing != overall_increasing) {
                    is_safe = false;
                    break;
                }
            } while ((token = strtok(NULL, " ")) != NULL);

            if (is_safe) {
                total_safe++;
            }
        }
    }

    fclose(file);

    printf("Total Safe: %d\n", total_safe);
    return 0;
}
