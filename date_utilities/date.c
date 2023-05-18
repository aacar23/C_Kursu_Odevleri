#include "date.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>


#define isleap(year) ((!((year) % 4) && ((year) % 100)) || !((year) % 400))
#define access_struct_date(p) ((struct struct_date *)((p) -> address))
#define const_access_struct_date(p) ((const struct struct_date *)((p) -> address))
#define create_getter(member_type, name_of_member) member_type get_##name_of_member(const date *p) \
                                                    {                                                   \
                                                        return (const_access_struct_date(p)) -> name_of_member;\
                                                    }
#define malloc(bytes) (checked_malloc(bytes))





static void *checked_malloc(size_t bytes)
{
    void *vp_ret = (malloc)(bytes);


    if (!vp_ret){
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }


    return vp_ret;
}

static void clean_buffer()
{
    int c;


    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

struct struct_date{
    time_t day;
    time_t month;
    time_t year;
    time_t weekday;
};

static int days_of_months[12] = {31, 28, 31, 30, 31, 30, 31 , 31, 30, 31, 30, 31};

static void char_swap(char *c1, char *c2)
{
    int temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

static void reverse_str(char *str)
{
    size_t length = strlen(str);


    for (size_t i = 0;i < length / 2;i++)
        char_swap(str + i, str + length - 1 - i);
}

static size_t num_length_base_10(long long num)
{
    size_t ret = 0;


    while(num) {
        num /= 10;
        ret++;
    }


    return ret;
}

static long long reverse_num_long_long(long long num)
{
    long long reversed_num = 0;
    int power = (int)num_length_base_10(num) - 1;


    while (num) {
        reversed_num += num % 10 * (long long) pow(10, power);
        num /= 10;
        power--;
    }


    printf("%lld\n", reversed_num);


    return reversed_num;
}







//get functions

create_getter(time_t , day)
create_getter(time_t , month)
create_getter(time_t , year)
create_getter(time_t , weekday)







//activation functions

extern date *create_date(void)
{
    date *new = malloc(sizeof(date));
    new -> address = malloc(sizeof(struct struct_date));


    return new;
}

extern date *activate_date(date *p)
{
    p -> address = malloc(sizeof(struct struct_date));


    return p;
}






//set functions


extern date* set_date(date *p, time_t day_value, time_t month_value, time_t year_value)
{

    if (isleap(year_value) && month_value == 2 && day_value > 29)
        return NULL;
    else if (day_value > days_of_months[month_value - 1])
        return NULL;

    if (year_value < 1902){
        if (year_value != 1901 && month_value != 12 && !(day_value > 12 && day_value < 32))
            return NULL;
    }
    else if (year_value > 2038)
        return NULL;

    struct struct_date *p_accessed= access_struct_date(p);
    p_accessed -> month = month_value;
    p_accessed -> year = year_value;
    p_accessed -> day = day_value;
    p_accessed -> weekday = ((convert_date_to_seconds(p) - INT_MIN) / (24 * 60 * 60) + 6) % 7;


    if (p_accessed -> month > 12)
        p_accessed -> month %= 12;


    return p;
}

extern date *set_date_from_str(date *p, const char *pstr)
{
    size_t size;
    char pstr_copy[size = strlen(pstr) + 1];


    memcpy(pstr_copy, pstr, size);


    struct struct_date *p_accessed = access_struct_date(p);
    char *end = (char *)pstr_copy;
    time_t *members[3] = {&(p_accessed -> year), &(p_accessed -> month), &(p_accessed -> day)};


    reverse_str(pstr_copy);


    for (size_t i = 0;i < 3;i++){
        const char *prev = end;
        long long val = strtoll(end, &end, 10);


        if (num_length_base_10(val) == 1)
            *members[i] = val * 10;
        else {
            *members[i] = reverse_num_long_long(val);
        }


        if (prev == end && i < 2)
            return NULL;


        end++;
    }

    if (isleap(p_accessed -> year))
        days_of_months[1] = 29;


    if (p_accessed -> year > 2038)
        return NULL;
    if (p_accessed -> month > 12)
        return NULL;
    if (p_accessed -> day > days_of_months[p_accessed -> month])
        return NULL;



    if (p_accessed -> month > 12)
        p_accessed -> month %= 12;


    if (isleap(p_accessed -> year) && p_accessed -> month == 2 && p_accessed -> day > 29)
        p_accessed -> day %= 29;
    else if (p_accessed -> day > days_of_months[p_accessed -> month])
        p_accessed -> day %= days_of_months[p_accessed -> month - 1];


    p_accessed -> weekday = ((convert_date_to_seconds(p) - INT_MIN) / (24 * 60 * 60) + 6) % 7;


    return p;
}

extern date *set_date_from_time_t(date *p, time_t sec)
{
    sec -= INT_MIN;


    struct struct_date *p_accessed = access_struct_date(p);
    p_accessed -> weekday = (sec / (24 * 60 * 60) + 6) % 7 ;


    if (sec < 19 * 24 * 60 * 60){
        p_accessed -> year = 1901;
        p_accessed -> day = 13 + (sec / 24 * 60 * 60);
        p_accessed -> month = 12;
        p_accessed -> weekday = 5;
        return p;
    }


    time_t temp_sec = sec - 17 * 24 * 60 * 60;
    int s;
    int t;


    for (s = 1, t = 0;temp_sec - (isleap(1901 + s) ? (t = 366 * 24 * 60 * 60) : (t = 365 * 24 * 60 * 60)) > 0; s++)
        temp_sec -= t;
    p_accessed -> year = 1901 + s;


    if (isleap(p_accessed -> year))
        days_of_months[1] = 29;
    else
        days_of_months[1] = 28;


    temp_sec /= 24 * 60 * 60;


    int nth_month;


    for (nth_month = 1; temp_sec - days_of_months[nth_month - 1] > 0; nth_month++)
        temp_sec -= days_of_months[nth_month - 1];


    p_accessed -> day = temp_sec;
    p_accessed -> month = nth_month;


    return p;
}

extern date  *set_date_today(date *p)
{
    return set_date_from_time_t(p, time(NULL));
}

extern date *set_date_random(date *p)
{
    return set_date_from_time_t(p, rand() % 2 ? rand() : -rand());
}

extern date *set_year(date *p, time_t year_value)
{
    struct struct_date *p_accessed = access_struct_date(p);
    p_accessed -> year = year_value;
    p_accessed -> weekday = (convert_date_to_seconds(p) - INT_MIN / (24 * 60 * 60) + 6) % 7;

    return p;
}

extern date *set_month(date *p, time_t month_value)
{
    struct struct_date *p_accessed = access_struct_date(p);
    p_accessed -> month = month_value;
    p_accessed -> weekday = (convert_date_to_seconds(p) - INT_MIN / (24 * 60 * 60) + 6) % 7;

    return p;
}

extern date *set_month_day(date *p, time_t day_value)
{
    struct struct_date *p_accessed = access_struct_date(p);
    p_accessed -> day = day_value;
    p_accessed -> weekday = (convert_date_to_seconds(p) - INT_MIN / (24 * 60 * 60) + 6) % 7;


    return p;
}






//utility functions

extern time_t convert_date_to_seconds(const date *p)
{
    const struct struct_date *p_accessed = const_access_struct_date(p);


    if (p_accessed -> year == 1901 && p_accessed -> month == 12 && p_accessed -> day >= 14)
        return p_accessed -> day * 24 * 60 * 60 - 13 * 24 * 60 * 60 + INT_MIN -22 * 60 * 60 - 42 * 60 - 48;


    time_t seconds = p_accessed -> day * 24 * 60 * 60 + 18 * 24 * 60 * 60 - 22 * 60 * 60 - 42 * 60 - 48 - 184;
    time_t years = p_accessed -> year - 1;
    time_t months = p_accessed -> month;


    if (isleap(p_accessed -> year))
        days_of_months[1] = 29;
    else
        days_of_months[1] = 28;


    for (int i = 0;i < months - 1;i++)
        seconds += days_of_months[i] * 24 * 60 * 60;


    for (;years - 1901;years--) {
        if (isleap(years))
            seconds += 366 * 24 * 60 * 60;
        else
            seconds += 365 * 24 * 60 * 60;
    }

    time_t ret = seconds + INT_MIN;


    return ret;
}

extern date *copy_date(date *dest, date *src)
{
    struct struct_date *dest_accessed = access_struct_date(dest);
    struct struct_date *src_accessed = access_struct_date(src);


    memcpy(dest_accessed, src_accessed, sizeof(struct struct_date));


    return dest;
}

extern int compare_dates(const void *p1, const void *p2)
{
    time_t p1_converted_to_time = convert_date_to_seconds(p1);
    time_t p2_converted_to_time = convert_date_to_seconds(p2);


    return p1_converted_to_time > p2_converted_to_time ? 1 : p1_converted_to_time < p2_converted_to_time ? -1 : 0;
}

extern time_t date_difference(const date *p1, const date *p2)
{
    return ((convert_date_to_seconds(p1) - convert_date_to_seconds(p2)) / (24 * 60 * 60));
}

extern time_t nth_day_of_the_year(date *p)
{
    time_t n = 0;
    struct struct_date *p_accessed = access_struct_date(p);


    for (int i = 0; i < p_accessed -> month - 1; ++i) {
        n += days_of_months[i];
    }


    n += p_accessed -> day;
    if (isleap(p_accessed -> year) && p_accessed -> day > 1)
        n++;


    return n;
}

extern date *n_days_after_date(date *dest, const date *source, int n)
{
    time_t date_value = convert_date_to_seconds(source) + n * 24 * 60 * 60;


    if (date_value > INT_MAX)
        return NULL;


    set_date_from_time_t(dest, date_value);


    return dest;
}

extern date *n_days_before_date(date *dest, const date *sources, int n)
{
    time_t date_value = convert_date_to_seconds(sources) - n * 24 * 60 * 60;


    if (date_value < INT_MIN)
        return NULL;


    set_date_from_time_t(dest, date_value);


    return dest;
}






//input output functions

extern void print_date(const date *p)
{
    const struct struct_date *p_accessed = const_access_struct_date(p);
    static const char weekdays[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };


    printf("%02ld-%02ld-%04ld ",p_accessed -> day, p_accessed -> month, p_accessed -> year);
    puts(weekdays[p_accessed -> weekday]);
}

static int scan_date_member_scanner(time_t *member, size_t num_length)
{
    for (size_t i = 0, power = (size_t) pow(10, (double)num_length);i < num_length;i++){
        int c = getchar();


        if (isdigit(c))
            *member += (time_t)((c - 48) * (power /= 10));
        else
            return 1;
    }


    return 0;
}

static int scan_all(date *p)
{
    struct struct_date *p_accessed = access_struct_date(p);


    if (scan_date_member_scanner(&(p_accessed->day), 2))
        return 1;
    if (getchar() != '-')
        return 1;
    if (scan_date_member_scanner(&(p_accessed->month), 2))
        return 1;
    if (getchar() != '-')
        return 1;
    if (scan_date_member_scanner(&(p_accessed->year), 4))
        return 1;
    return 0;
}


extern void scan_date(date *p)
{
    clean_buffer();
    struct struct_date *p_accessed = access_struct_date(p);


    p_accessed -> day = 0;
    p_accessed -> month = 0;
    p_accessed -> year = 0;
    while (1) {
        printf("Please enter the date in dd-mm-yyyy format:");

        if (scan_all(p))
            goto out;


        if (p_accessed -> year == 1901) {
            if (!(p_accessed->day <= 31 && p_accessed->month == 12))
                goto out;
            else {
                p_accessed -> weekday = ((convert_date_to_seconds(p) - INT_MIN) / (24 * 60 * 60) + 5) % 7;
                break;
            }
        }
        if (p_accessed -> month > 12)
            goto out;
        if (p_accessed -> day > days_of_months[p_accessed -> month - 1])
            goto out;
        if (p_accessed -> year > 2038)
            goto out;


        p_accessed -> weekday = ((convert_date_to_seconds(p) - INT_MIN) / (24 * 60 * 60) + 6) % 7;
        return;


        out:
        clean_buffer();
        printf("mis-formatted or invalid input try again\n");
    }
}

