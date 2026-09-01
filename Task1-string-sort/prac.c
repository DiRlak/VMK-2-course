// empty strings wouldn't be printed

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max_len = 50; // maximum length of strings

char *str_in();                       // string input
void str_out(const char **mas, int size);   // string output
int str_cmp(const void *a, const void *b); // sorting array of strings

int main() {
    char *str;         // reserved string
    char **mas = NULL; // array of strings
    int size = 0;      // amount of strings in array
    
    str = str_in();
    while (!feof(stdin)) { // feof = 0, if file complete
    	if (str != NULL) {
    	        size++;
    	        mas = (char**) realloc(mas, size*sizeof(char*));
    	        mas[size-1] = str;
    	}
    	str = str_in();
    }
    
    qsort(mas, size, sizeof(char*), *str_cmp); //!!!!!!!
    str_out((const char **)mas, size); // why?
    
    for (int i = 0; i < size; ++i)
        free(mas[i]);
    free(mas);

    return 0;
}

char *str_in() {
    char *str = NULL;
    int i = 0;
    
    char c = getchar();
    if (c == '\n' || c == EOF)
        return NULL;
    
    str = (char*) malloc(max_len);
    str[i] = c;
    
    c = getchar();
    while (c != '\n' && (c != EOF)) {
        i++;
        if (i >= max_len) {
            max_len += max_len/2;
            str = (char*) realloc(str, max_len);
        }
        str[i] = c;
        c = getchar();
    }
    
    if (i+1 != max_len)
        str[i+1] = '\0';
    return str;
}

int str_cmp(const void *a, const void *b) {
    return strcmp((char *) a, (char *) b);
}

void str_out(const char **mas, int size) {
    for (int i = 0; i < size; ++i)
    	printf("%s\n", mas[i]);
}
