#include <string.h>
#include <stdlib.h>


void get_day_month_and_year(const char *date, int *day, int *month, int *year, const char *format_characters)
{
    char *string_copy = malloc((strlen(date) + 1) * sizeof(char));
    strcpy(string_copy, date);
    int *const date_elements[3] = {day, month, year};
    char *p = strtok(string_copy, format_characters);


    for (int i = 0;p && i < 3;i++){
        *date_elements[i] = atoi(p);
        p = strtok(NULL, format_characters);
    }
    free(string_copy);
}