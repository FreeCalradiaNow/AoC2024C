#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 1200

// int compare(const void *a, const void *b) {
//     return (*(int *)a - *(int *)b);
// }

int main() {
    FILE *file = fopen("d1.txt", "r");
    if (file == NULL) {
        // printf("not here\n");
        return 1;
    }

    int left_list[MAX_LINES];
    int right_list[MAX_LINES];
    int count = 0;

    while (fscanf(file, "%d %d", &left_list[count], &right_list[count]) != EOF) {
        count++;
    }

    fclose(file);

    // qsort(left_list, count, sizeof(int), compare);
    // qsort(right_list, count, sizeof(int), compare);

    int similarity_score = 0; 
    for (int i = 0; i < count; i++) { 
        int left_value = left_list[i]; 
        int occurrence = 0; 

        for (int j = 0; j < count; j++) { 
            if (right_list[j] == left_value) { 
                occurrence++; 
            } 
        } 
        
        similarity_score += left_value * occurrence; 
    } 
    
    printf("similarity score: %d\n", similarity_score); 
    
    return 0;
}