#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_safe_report(int levels[], int size) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 0; i < size - 1; i++) {
        int diff = levels[i + 1] - levels[i];
        if (!(diff >= 1 && diff <= 3)) {
            increasing = false;
        }
        if (!(diff <= -1 && diff >= -3)) {
            decreasing = false;
        }
    }
    return increasing || decreasing;
}

bool is_safe_with_dampener(int levels[], int size) {
    if (is_safe_report(levels, size)) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        int temp[100];
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (j != i) {
                temp[k++] = levels[j];
            }
        }
        if (is_safe_report(temp, size - 1)) {
            return true;
        }
    }
    return false;
}

int calculate_total_safereports(char *reports[], int report_count) {
    int safe_count = 0;

    for (int i = 0; i < report_count; i++) {
        char *report = reports[i];
        int levels[100];
        int level_count = 0;
        char *token = strtok(report, " ");
        
        while (token != NULL) {
            levels[level_count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (is_safe_with_dampener(levels, level_count)) {
            safe_count++;
        }
    }
    return safe_count;
}

char** read_lists_from_file(const char *filename, int *report_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char **reports = malloc(1000 * sizeof(char*));
    char line[256];
    *report_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        reports[*report_count] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(reports[*report_count], line);
        (*report_count)++;
    }

    fclose(file);
    return reports;
}

int main() {
    const char *filename = "d2.txt";
    int report_count;
    char **reports = read_lists_from_file(filename, &report_count);

    int total_safereports = calculate_total_safereports(reports, report_count);
    printf("total number of safe reports after dampener: %d\n", total_safereports);

    for (int i = 0; i < report_count; i++) {
        free(reports[i]);
    }
    free(reports);

    return 0;
}