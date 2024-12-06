#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 1000

int print_word(char *array,char *pattern, int index, int is_color, int counter2);
int count_char(char* array);
int compare_word(char *pattern,char* array, int counter,int counter2, int is_color);
char* read_input(int *count);

int main(int argc, char *argv[]) {
    int ret = EXIT_SUCCESS;
    char *pattern = NULL;
    char *filename = NULL;
    int counter2=0;
    int is_file = 0;
    int counter = 0;
    int is_color = 0;
    unsigned long capacity = INIT_SIZE;
    char* arr_first = (char*)malloc(capacity*sizeof(char));
    if (argc <3 ) {
        free(arr_first);
        arr_first = read_input(&counter);
        pattern = argv[1];
        is_file = 1;
    }
    if(argc == 4) {
        is_color = 1;
        pattern = argv[2];
        filename = argv[3];
        is_file = 0;
    }
    else {
        pattern = argv[1];
        filename = argv[2];
    }


    if (is_file == 0) {
        FILE *file;
        file = fopen (filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        // char *temp = (char*)malloc(capacity*sizeof(char));
        int i =0;
        char c;
        while((c = fgetc(file)) != EOF) {
            if(i >= capacity) {
                char *temp = realloc(arr_first, capacity*sizeof(char) * 2);
                if (temp== NULL) {
                    free(arr_first);
                    fclose(file);
                    return EXIT_FAILURE;
                }
                arr_first = temp;
                capacity *=2;
            }
            arr_first[i] = c;
            counter ++;//counter for amount of chars
            i++;
        }
        arr_first[i] = '\n'; //added whitespace to the end of array
        fclose(file);
        // for (int j = 0; j < 25; j++) {
        //     printf("%c",arr_first[j]);
        // }
        // counter2 = count_char(pattern);
    }


    counter2 = count_char(pattern);
    // if (!is_file ) {
    //     char* arr_first = (char*)malloc(capacity*sizeof(char));
    // }
    char *temp = (char*)realloc(arr_first, sizeof(char) * (counter+1));
    arr_first = temp;
    arr_first[counter] = '\0';
    // for (int j = 0; j < counter; j++) {
    //     printf("%c ",arr_first[j]);
    // }
    // printf("%s ",pattern);
    ret = compare_word( pattern, arr_first, counter, counter2, is_color);


    if (argc <3 ) {
        free(filename);
    }
    free(arr_first);
    return ret;
}


int print_word(char *array,char *pattern, int index, int is_color, int counter2) {
    int ret = 0;
    // printf("%d ", is_color);
    // printf("%d ", index_for_color);
    while (index > 0 && array[index-1] != '\n' ) {//&& array[index-1] != ' '
        // putchar(array[index]);
        // putchar('\n');
        index--;
    }
    int i = 0;
    while (  array[index ] != '\n' && array[index ] != '\0') {
        for(int j =0; j <counter2;j++) {
            if(is_color == 1 && array[index ] == pattern[i] ){
                printf(("\033[01;31m%c\033[0m"),array[index ]);
                // printf(("\033[01;31m%c\033[0m"),array[index +1]);
                i++;
                index++;
            }
        }
        // index +=counter2;

        // if( is_color == 1 && index == index_for_color) {
        //     for(int i =0; i < counter2; i ++) {
        //         printf(("\033[01;31m%c\033[0m"),array[index + i]);
        //     }
        //     index +=counter2;
        //
        // }
            i=0;
            putchar(array[index]);
            index++;

    }
    putchar('\n');

    return ret;
}
int count_char(char* array) {
    int  k = 0;
    int counter = 0;
    while(array[k] != '\0') { // counter for pattern
        counter ++;
        k++;
    }
    return counter;
}

int  compare_word(char *pattern,char* array, int counter,int counter2, int is_color) {
    int k = 0;
    int ret = -1;
    // int color = is_color;
    // printf()
    // printf("C%d ", counter2);
    // printf("K%d ", k);
    // printf("%s ",pattern);
    // printf("%s ",array);
    for(int j =0; j < counter ; j ++) {
        if(pattern[k] == array[j]) {
            k++;
            // printf("C%d ", counter2);
            // printf("K%d ", k);
            if (k == counter2 ) {
                // printf("%d ", is_color);
                // printf("C%d ", counter2);

                // printf("%s ",pattern);
                ret = print_word(array,pattern,j, is_color, counter2);
                k =0;
                // if(is_color ==1 )
                //     ret = print_word(array,j, is_color, counter2);
                while (j < counter && array[j] != '\n' && array[j] != '\0') {
                    j++;
                }
            }
        }else {
            k = 0;
        }
    }
    if (k==0 && ret == -1) {
        ret = 1;
    }
    // free(array);
    return ret;
}

char* read_input(int * count) {
    char c;
    int i =0;
    int capacity = 1000;
    char* array = (char*)malloc(capacity*sizeof(char));
    while((c = getchar()) !=EOF) {
        array [i] = c;
        i ++;
    }
    char *temp = (char*)realloc(array, sizeof(char) * (i+1));

    array = temp;
    array[i] = '\0';
    *count = i;
    // for (int j = 0; j <= i; j++) {
    //    printf("%c\n",array[j]);
    // }
    return array;

}


/*for (int j = 0; j < counter; j++) {
if (pattern[k] == array[j]) {
k++;
if (k == counter2) {
ret = print_word(array, j);
k = 0;

// Skip to the next word after a match
while (j < counter && array[j] != ' ' && array[j] != '\n' && array[j] != '\0') {
j++;
}
}
} else {
k = 0;
}
}
*/



