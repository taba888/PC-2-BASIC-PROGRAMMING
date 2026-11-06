
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(b, a);
}

// Helper function to count distinct characters in a string
int get_distinct_count(const char* s) {
    int freq[26] = {0};
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (freq[s[i] - 'a'] == 0) {
            count++;
        }
        freq[s[i] - 'a']++;
    }
    return count;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int distinct_a = get_distinct_count(a);
    int distinct_b = get_distinct_count(b);
    
    if (distinct_a != distinct_b) {
        return distinct_a - distinct_b;
    }
    return strcmp(a, b);
}

int sort_by_length(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    if (len_a != len_b) {
        return len_a - len_b;
    }
    return strcmp(a, b);
}

void string_sort(char** arr, const int count, int (*cmp_func)(const char*, const char*)) {
    // Bubble sort implementation using the given comparison function pointer
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (cmp_func(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}