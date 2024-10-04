#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
    //strcmp function: The strcmp() function is used here to compare the two strings lexicographically.
    /* if result < 0
       "a" comes before "b" 

       if result > 0
       "a" comes after "b" 

        if result = 0
       "a" equal to "b" 
    */
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(b, a);
    // Reverse the order of comparison

    /* if result < 0
       "a" comes before "b" in descending order

       if result > 0
       "a" comes after "b" in descending order

        if result = 0
       "a" equal to "b" 
    */
}

int get_number_of_char(const char* a){
    int char_seen[256] = {0};  // ASCII table size (for all characters)
    int count = 0;

    for (int i=0; a[i] != '\0'; i++){
        if (!char_seen[a[i]]){ // If the character hasn't been counted yet
            char_seen[a[i]] = 1; //mark its position as one
            count++;
        } 
    }
    return count;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int num_a = get_number_of_char(a);
    int num_b = get_number_of_char(b);

    if (num_a > num_b)
        return 1; //a > b
    else if (num_b > num_a)
        return -1; //b > a
    else 
        return lexicographic_sort(a, b); //a == b

}

int sort_by_length(const char* a, const char* b) {

    if (strlen(a) > strlen(b))
        return 1; //a > b
    else if (strlen(b) > strlen(a))
        return -1; //b > a
    else 
        return lexicographic_sort(a, b); //a == b
}

void string_sort(char** arr,const int len,
int (*cmp_func)(const char* a, const char* b)) //send pointer to function
{

    for (int i=0; i<len-1; i++){
        for (int j=i+1; j< len; j++){
            if ( cmp_func(arr[i], arr[j]) >= 0){ //a<b
                char* temp = strdup(arr[i]);
                arr[i] = strdup(arr[j]);
                arr[j] = strdup(temp);
                
                free(temp);
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
