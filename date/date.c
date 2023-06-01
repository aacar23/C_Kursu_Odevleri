#include "date.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


#define malloc(size) (checked_malloc(size))
#define access_date(p) ((struct struct_date *)((p) -> address))
#define const_access_date(p) ((const struct  struct_date *)((p) -> address))
#define asize(array) (sizeof((array)) / sizeof(*(array)))

static int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char *month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char *weekday_names[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
static char shared_date_string[37] = {0};

struct struct_date{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
    int weekday;
    int utc_offset;
    int nth_day_of_the_year;
};

typedef enum WEEKDAYS{MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY} WEEKDAY_OFFSET;

static struct struct_date utc_date;

static struct struct_date time_date_struct;
static date time_date = {.address = &time_date_struct};


static void swap(void *vp1, void *vp2, size_t size)
{
    char *p1 = (char *)vp1;
    char *p2 = (char *)vp2;
    while (size--){
        int temp = *p1;
        *p1++ = *p2;
        *p2++ = temp;
    }
}

static int isleap(int year)
{
    return (!((year) % 4) && (((year) % 100) || !((year) % 400)));
}

static void *checked_malloc(size_t bytes)
{
    void *vp;

    if (!(vp = (malloc)(bytes))){
        fprintf(stderr, "heap is out of memory");
        exit(EXIT_FAILURE);
    }

    return vp;
}










//activation functions

extern date *allocate_date(void)
{
    date *new_date = malloc(sizeof(date));
    struct struct_date *anonymous_date_object = malloc(sizeof(struct struct_date));
    new_date -> address = anonymous_date_object;
    return new_date;
}

extern void activate_date(date *inactive_date_p, int utc_offset_value)
{
    inactive_date_p -> address = malloc(sizeof(struct struct_date));
    access_date(inactive_date_p) -> utc_offset = utc_offset_value;
}








//deactivation functions

extern void free_date(date *dynamic_date_p)
{
    free(dynamic_date_p -> address);
    free(dynamic_date_p);
}

extern void deactivate_date(date *p)
{
    free(p -> address);
}








//setter functions

static void normalize_date(date *p)
{
    set_date_from_time_t(p, convert_date_to_gmt_time(p));
}

static int calculate_nth_day_of_the_year(const date *p)
{
    int nth_day_of_the_year = 0;
    const struct struct_date *p_accessed = const_access_date(p);
    if (isleap(p_accessed -> year))
        month_days[1] = 29;
    else
        month_days[1] = 28;
    for (int i = 0; i < p_accessed -> month; i++)
        nth_day_of_the_year += month_days[i];
    nth_day_of_the_year += p_accessed -> day + 1;
    return nth_day_of_the_year;
}

static int calculate_weekday(time_t unsigned_seconds, WEEKDAY_OFFSET offset)
{
    return (int)((unsigned_seconds + offset * SECONDS_IN_A_DAY) % (7 * SECONDS_IN_A_DAY)) / (SECONDS_IN_A_DAY);
}

static int recalculate_weekday(date *p)
{
    return calculate_weekday(convert_date_to_gmt_time(p) - STARTING_TIME_POINT + access_date(p) -> utc_offset * 60 * 60, MONDAY);
}

static int check_date(int day_value, int month_value, int year_value, int hour_value, int minute_value, int second_value)
{
    if (month_value < 0 || month_value > 11)
        return 0;
    if (day_value < 0 || day_value > month_days[month_value] - 1)
        return 0;
    if (year_value < 1902 || year_value > 2037)
        return 0;
    if (hour_value > 59 || hour_value < 0)
        return 0;
    if (minute_value < 0 || minute_value > 59)
        return 0;
    if (second_value < 0 || second_value > 59)
        return 0;
    return 1;
}

extern date *set_date(date *p, int day_value, int month_value, int year_value, int hour_value, int minute_value, int second_value, int utc)
{
    if (year_value > 2037 || year_value < 1902)
        return NULL;
    if (month_value > 12 || month_value < 1)
        return NULL;

    if (isleap(year_value))
        month_days[1] = 29;
    else
        month_days[1] = 28;

    if (day_value > month_days[month_value - 1] || day_value < 1)
        return NULL;
    if (hour_value > 23 || hour_value < 0)
        return NULL;
    if (minute_value > 59 || minute_value < 0)
        return NULL;
    if (second_value > 59 || second_value < 0)
        return NULL;

    struct struct_date *p_accessed = access_date(p);
    p_accessed -> day = day_value - 1;
    p_accessed -> month = month_value - 1;
    p_accessed -> year = year_value;
    p_accessed -> hour = hour_value;
    p_accessed -> minute = minute_value;
    p_accessed -> second = second_value;
    p_accessed -> weekday = calculate_weekday(convert_date_to_gmt_time(p) - STARTING_TIME_POINT, MONDAY);
    p_accessed -> utc_offset = utc;
    return p;
}

extern date *set_date_from_time_t(date *p, time_t seconds_far_from_epoch)
{
    if (seconds_far_from_epoch > ENDING_TIME_POINT || seconds_far_from_epoch < STARTING_TIME_POINT)
        return NULL;

    struct struct_date *p_accessed = access_date(p);
    seconds_far_from_epoch += -STARTING_TIME_POINT + p_accessed -> utc_offset * 60 * 60;
    p_accessed -> weekday = calculate_weekday(seconds_far_from_epoch, MONDAY);
    p_accessed -> hour = (int)(seconds_far_from_epoch % SECONDS_IN_A_DAY / SECONDS_IN_AN_HOUR);
    p_accessed -> minute = (int)(seconds_far_from_epoch % SECONDS_IN_AN_HOUR / SECONDS_IN_A_MINUTE);
    p_accessed -> second = (int)(seconds_far_from_epoch % SECONDS_IN_A_MINUTE);

    int years = 1900;
    int minus;
    for (;seconds_far_from_epoch - ((isleap(years) ? (minus = SECONDS_IN_A_LEAP_YEAR) : (minus = SECONDS_IN_A_COMMON_YEAR))) > 0;years++)
        seconds_far_from_epoch -= minus;
    month_days[1] = isleap(years) ? 29 : 28;

    int i = 0;
    for (; seconds_far_from_epoch - month_days[i] * SECONDS_IN_A_DAY > 0;i++)
        seconds_far_from_epoch -= month_days[i] * SECONDS_IN_A_DAY;
    p_accessed -> year = years;
    p_accessed -> month = i;
    p_accessed -> day = (int)(seconds_far_from_epoch / SECONDS_IN_A_DAY);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);

    return p;
}

extern date *set_date_today(date *p)
{
    return set_date_from_time_t(p, time(NULL));
}

extern date *set_date_random(date *p)
{
    int a;
    FILE *f = fopen("/dev/urandom", "r");
    fread(&a, sizeof(a), 1, f);
    return set_date_from_time_t(p, a);
}

static int member_assigner(int *member, const char *str)
{
    char *conv_end;
    int end_to_num = (int)strtol(str, &conv_end, 10);
    if (conv_end == str)
        return 1;
    *member = end_to_num;
    return 0;
}

static int weekday_and_month_assigner(int *weekday_or_month_member, const char *str, const char **name_array, size_t number_of_elements)
{
    size_t cnt = 0;
    for (;cnt < number_of_elements;cnt++){
        if (memcmp(str, name_array[cnt], 3) == 0) {
            *weekday_or_month_member = (int)cnt;
            return 0;
        }
    }
    return 1;
}

extern date *set_date_from_str(date *p, const char *str)
{
    char str_copy[DATE_STR_SIZE] = {0};
    memcpy(str_copy, str, strlen(str) + 1);
    struct struct_date *p_accessed = access_date(p);


    char *end = strtok(str_copy, " ");
    if(weekday_and_month_assigner(&p_accessed -> weekday, end, weekday_names, asize(weekday_names)))
        return NULL;

    end = strtok(NULL, " ");
    if(weekday_and_month_assigner(&p_accessed -> month, end, month_names, asize(month_names)))
        return NULL;

    end = strtok(NULL, " ");
    if (!end || member_assigner(&p_accessed -> day, end))
        return NULL;

    end = strtok(NULL, " ");
    if (!end || member_assigner(&p_accessed -> hour, end))
        return NULL;

    end = (strtok(end, ":"), strtok(NULL, ":"));
    if (!end || member_assigner(&p_accessed -> minute, end))
        return NULL;

    end = strtok(NULL, ":");
    if (!end || member_assigner(&p_accessed -> second, end))
        return NULL;

    end = strtok(end + strlen(end) + 1, " ");
    if (!end || member_assigner(&p_accessed -> year, end))
        return NULL;

    if (!check_date(p_accessed -> day, p_accessed -> month, p_accessed -> year, p_accessed -> hour, p_accessed -> minute, p_accessed -> second))
        return NULL;


    return p;
}

extern date *set_year(date *p, int year_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (!check_date(p_accessed -> day, p_accessed -> month, year_value, p_accessed -> hour, p_accessed -> minute, p_accessed -> second))
        return NULL;
    p_accessed -> year = year_value;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_month(date *p, int month_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (!check_date(p_accessed -> day, month_value - 1, p_accessed -> year, p_accessed -> hour, p_accessed -> minute, p_accessed -> second))
        return NULL;
    p_accessed -> month = month_value - 1;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_day(date *p, int day_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (isleap(p_accessed -> year))
        month_days[1] = 29;
    else
        month_days[1] = 28;
    if (!check_date(day_value - 1, p_accessed -> month, p_accessed -> year, p_accessed -> hour, p_accessed -> minute, p_accessed -> second))
        return NULL;
    p_accessed -> day = day_value - 1;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_hour(date *p, int hour_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (!check_date(p_accessed -> day, p_accessed -> month, p_accessed -> year, hour_value, p_accessed -> minute, p_accessed -> second))
        return NULL;
    p_accessed -> hour = hour_value;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_minute(date *p, int minute_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (!check_date(p_accessed -> day, p_accessed -> month, p_accessed -> year, p_accessed -> hour, minute_value, p_accessed -> second))
        return NULL;
    p_accessed -> minute = minute_value;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_second(date *p, int second_value)
{
    struct struct_date *p_accessed = access_date(p);
    if (!check_date(p_accessed -> day, p_accessed -> month, p_accessed -> year, p_accessed -> hour, p_accessed -> minute, second_value))
        return NULL;
    p_accessed-> second = second_value;
    p_accessed -> weekday = recalculate_weekday(p);
    p_accessed -> nth_day_of_the_year = calculate_nth_day_of_the_year(p);
    return p;
}

extern date *set_n_days_after_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) + n * SECONDS_IN_A_DAY);
}

extern date *set_n_days_before_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) - n * SECONDS_IN_A_DAY);
}

extern date *set_n_months_after_date(date *dest, const date *source, int n)
{
    const struct struct_date *source_accessed = const_access_date(source);
    time_t timer = convert_date_to_gmt_time(source);
    for (int i = 0;i < n;i++)
        timer += month_days[(source_accessed -> month + i) % 12] * SECONDS_IN_A_DAY;
    return set_date_from_time_t(dest, timer);
}

extern date *set_n_months_before_date(date *dest, const date *source, int n)
{
    const struct struct_date *source_accessed = const_access_date(source);
    time_t timer = convert_date_to_gmt_time(source);
    for (int i = 0;i < n;i++)
        timer -= month_days[12 + (source_accessed -> month - i) % 12] * SECONDS_IN_A_DAY;
    return set_date_from_time_t(dest, timer);
}

extern date *set_n_years_after_date(date *dest, const date *source, int n)
{
    const int *source_year_accessed = &const_access_date(source) -> year;
    time_t timer = convert_date_to_gmt_time(source);
    for (int i = 0;i < n;i++)
        timer += isleap(*source_year_accessed + i) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR;
    return set_date_from_time_t(dest, timer);
}

extern date *set_n_years_before_date(date *dest, const date *source, int n)
{
    const int *source_year_accessed = &const_access_date(source) -> year;
    time_t timer = convert_date_to_gmt_time(source);
    for (int i = 0;i < n;i++)
        timer -= isleap(*source_year_accessed - i) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR;
    return set_date_from_time_t(dest, timer);
}

extern date *set_n_hours_after_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) + n * SECONDS_IN_AN_HOUR);
}

extern date *set_n_hours_before_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) - n * SECONDS_IN_AN_HOUR);
}

extern date *set_n_minutes_after_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) + n * SECONDS_IN_A_MINUTE);
}

extern date *set_n_minutes_before_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) - n * SECONDS_IN_A_MINUTE);
}

extern date *set_n_seconds_after_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) + n);
}

extern date *set_n_seconds_before_date(date *dest, const date *source, int n)
{
    return set_date_from_time_t(dest, convert_date_to_gmt_time(source) + n);
}

extern int set_utc(date *date_p, int utc_zone_value)
{
    if (utc_zone_value > 12 || utc_zone_value < -12)
        return 1;
    access_date(date_p) -> utc_offset = utc_zone_value;
    normalize_date(date_p);
    return 0;
}








//getter functions

extern int get_year_gmt(const date *p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    return const_access_date(&new) -> year;
}

extern const char *get_month_gmt(const date *p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    return month_names[const_access_date(&new) -> month];
}

extern int get_day_gmt(const date *p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    return const_access_date(&new) -> day + 1;
}

extern int get_hour_gmt(const date *p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    return const_access_date(&new) -> hour;
}

extern int get_minute_gmt(const date *p)
{
    return const_access_date(p) -> minute;
}

extern int get_second_gmt(const date *p)
{
    return const_access_date(p) -> second;
}

extern const char *get_weekday_gmt(const date *date_p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(date_p));
    return weekday_names[const_access_date(&new) -> weekday];
}

extern int get_nth_day_of_the_year_gmt(const date *date_p)
{
    date new;
    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(date_p));
    return const_access_date(&new) -> nth_day_of_the_year;
}

extern int get_year_local(const date *p)
{
    return access_date(p) -> year;
}

extern const char *get_month_local(const date *p)
{
    return month_names[const_access_date(p) -> month];
}

extern int get_day_local(const date *p)
{
    return const_access_date(p) -> day + 1;
}

extern int get_hour_local(const date *p)
{
    return const_access_date(p) -> hour;
}

extern int get_minute_local(const date *p)
{
    return const_access_date(p) -> minute;
}

extern int get_second_local(const date *p)
{
    return const_access_date(p) -> second;
}

extern const char *get_weekday_local(const date *p)
{
    return weekday_names[const_access_date(p) -> weekday];
}

extern int get_nth_day_of_the_year_local(const date *p)
{
    return const_access_date(p) -> nth_day_of_the_year;
}








//utility functions

extern char *date_to_str_local(const date *p)
{
    const struct struct_date *p_accessed = const_access_date(p);
    sprintf(shared_date_string, "%.3s %.3s %02d %02d:%02d:%02d %04d", weekday_names[p_accessed -> weekday], month_names[p_accessed -> month], p_accessed -> day + 1, p_accessed -> hour, p_accessed -> minute, p_accessed -> second, p_accessed -> year);
    return shared_date_string;
}

extern char *date_to_str_gmt(const date *p)
{
    date new;

    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    const struct struct_date *new_accessed = const_access_date(&new);
    sprintf(shared_date_string, "%.3s %.3s %02d %02d:%02d:%02d %04d", weekday_names[new_accessed -> weekday], month_names[new_accessed -> month], new_accessed -> day + 1, new_accessed -> hour, new_accessed -> minute, new_accessed -> second, new_accessed -> year);
    return shared_date_string;
}

extern char *write_date_to_str_gmt(char *dest, const date *p)
{
    date new;

    new . address = &utc_date;
    set_date_from_time_t(&new, convert_date_to_gmt_time(p));
    const struct struct_date *new_accessed = const_access_date(&new);

    sprintf(dest, "%.3s %.3s %02d %02d:%02d:%02d %04d", weekday_names[new_accessed->weekday],
            month_names[new_accessed->month], new_accessed->day + 1, new_accessed->hour, new_accessed->minute,
            new_accessed->second, new_accessed->year);
    return dest;
}

extern char *write_date_to_str_local(char *dest, const date *p)
{
    const struct struct_date *p_accessed = const_access_date(p);
    sprintf(dest, "%.3s %.3s %02d %02d:%02d:%02d %04d", weekday_names[p_accessed -> weekday],
            month_names[p_accessed -> month], p_accessed -> day + 1, p_accessed -> hour, p_accessed -> minute,
            p_accessed -> second, p_accessed -> year);
    return dest;
}

extern const date *time_to_date(const time_t *timer, int utc)
{
    access_date(&time_date) -> utc_offset = utc;
    return set_date_from_time_t(&time_date, *timer);
}

extern date *copy_date(date *dest, const date *source)
{
    return memcpy(dest -> address, source -> address, sizeof(struct struct_date));
}

extern time_t convert_date_to_gmt_time(const date *p)
{
    const struct struct_date *p_accessed = const_access_date(p);
    time_t ret = STARTING_TIME_POINT - p_accessed-> utc_offset * SECONDS_IN_AN_HOUR;
    ret += p_accessed -> hour * SECONDS_IN_AN_HOUR;
    ret += p_accessed -> minute * SECONDS_IN_A_MINUTE;
    ret += p_accessed -> second;
    ret += p_accessed -> day * SECONDS_IN_A_DAY;
    int years = p_accessed -> year;
    month_days[1] = isleap(years) ? 29 : 28;
    for (;years - 1900;){
        if (isleap(--years))
            ret += SECONDS_IN_A_LEAP_YEAR;
        else
            ret += SECONDS_IN_A_COMMON_YEAR;
    }

    int months = p_accessed -> month;
    for (int i = 0;i < months;i++)
        ret += month_days[i] * SECONDS_IN_A_DAY;
    return ret;
}

extern time_t convert_date_to_local_time(const date *p)
{
    time_t timer = convert_date_to_gmt_time(p) + const_access_date(p) -> utc_offset * SECONDS_IN_AN_HOUR;
    if (timer > ENDING_TIME_POINT || timer < STARTING_TIME_POINT)
        return CONV_FAILURE;
    return timer;
}


extern int compare_dates_universal_time(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE|| date2_converted == CONV_FAILURE)
        return CMP_FAILURE;
    time_t diff = date1_converted - date2_converted;
    return !diff ? 0 : diff > 0 ? 1 : -1;
}

extern int compare_dates_local_time(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_local_time(p1);
    time_t date2_converted = convert_date_to_local_time(p2);
    if (date1_converted == CONV_FAILURE|| date2_converted == CONV_FAILURE)
        return CMP_FAILURE;
    time_t diff = date1_converted - date2_converted;
    return !diff ? 0: diff > 0 ? 1 : -1;
}

static long date_day_difference(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE|| date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    time_t diff = date1_converted - date2_converted;
    return (int)(diff / SECONDS_IN_A_DAY);
}

static long date_month_difference(const date *p1, const date *p2)
{
    const struct struct_date *p1_accessed = const_access_date(p1);
    const struct struct_date *p2_accessed = const_access_date(p2);

    if (!memcmp(p1_accessed, p2_accessed, sizeof(struct struct_date)))
        return 0;

    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE || date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    time_t ret = date1_converted - date2_converted;

    int sign = 1;
    if (ret < 0){
        swap(&p1_accessed, &p2_accessed, sizeof(struct struct_date *));
        ret -= 2 * ret;
        sign = -1;
    }

    int i;
    int year_value = p1_accessed -> year;
    for (i = p1_accessed -> month;ret - month_days[i % 12] * SECONDS_IN_A_DAY >= 0;(ret -= month_days[i++ % 12] * SECONDS_IN_A_DAY))
        if (!((i + 1) % 12))
            month_days[1] = isleap(year_value++) ? 29 : 28;
    return sign * (i + 1 - p1_accessed -> month);
}

static long date_year_difference(const date *p1, const date *p2)
{
    const struct struct_date *p1_accessed = const_access_date(p1);
    const struct struct_date *p2_accessed = const_access_date(p2);

    if (!memcmp(p1_accessed, p2_accessed, sizeof(struct struct_date)))
        return 0;

    time_t date1_converted = convert_date_to_gmt_time(p1) - p1_accessed -> hour * SECONDS_IN_AN_HOUR - p1_accessed -> minute * SECONDS_IN_A_MINUTE - p1_accessed -> second;
    time_t date2_converted = convert_date_to_gmt_time(p2) - p2_accessed -> hour * SECONDS_IN_AN_HOUR - p2_accessed -> minute * SECONDS_IN_A_MINUTE - p2_accessed -> second;
    if (date1_converted == CONV_FAILURE || date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    time_t ret = date1_converted - date2_converted;
    if (ret > 0) {
        int minus = isleap(p1_accessed -> year) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR;
        int i = 0;
        for (;ret - minus > 0;isleap(i++ + p1_accessed -> year) ? (ret -= minus = SECONDS_IN_A_LEAP_YEAR) : (ret -= minus = SECONDS_IN_A_COMMON_YEAR))
            ;
        return i;
    }
    else{
        int plus = isleap(p2_accessed -> year) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR;
        int i = 0;
        for (;ret + plus < 0;isleap(i++ + p2_accessed -> year) ? (ret += plus = SECONDS_IN_A_LEAP_YEAR) : (ret += plus = SECONDS_IN_A_COMMON_YEAR))
            ;
        return -i;
    }
}

static long date_hour_difference(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE || date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    return (int)((date1_converted - date2_converted) / (SECONDS_IN_AN_HOUR));
}

static long date_minute_difference(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE || date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    return (int)((date1_converted - date2_converted) / (SECONDS_IN_A_MINUTE));
}

static long date_second_difference(const date *p1, const date *p2)
{
    time_t date1_converted = convert_date_to_gmt_time(p1);
    time_t date2_converted = convert_date_to_gmt_time(p2);
    if (date1_converted == CONV_FAILURE || date2_converted == CONV_FAILURE)
        return DIFF_FAILURE;
    return (int)((date1_converted - date2_converted));
}

extern long date_difference(const date *p1, const date *p2, DATE_ASSOCIATED_VALUE member)
{
    switch (member) {
        case DAY : return date_day_difference(p1, p2);
        case MONTH : return date_month_difference(p1, p2);
        case YEAR : return date_year_difference(p1, p2);
        case HOUR : return date_hour_difference(p1, p2);
        case MINUTE : return date_minute_difference(p1, p2);
        case SECOND : return date_second_difference(p1, p2);
        default : return DIFF_FAILURE;
    }
}








//input output functions

void print_date_gmt(const date *p)
{
    puts(date_to_str_gmt(p));
}

void print_date_local(const date *p)
{
    puts(date_to_str_local(p));
}

static int check_input(int *dest, int start_edge, int end_edge)
{
    int temp;
    int check;
    if (!(check = scanf("%d", &temp)) || check == -1)
        return 1;
    if (temp > end_edge || temp < start_edge)
        return 1;
    *dest = temp;
    return 0;
}

int scan_date(date *dest)
{
    struct struct_date *dest_accessed = access_date(dest);

    printf("Enter day:");
    int check;
    int temp;
    if(!(check = scanf("%d", &temp)) || check == -1)
        return EOF;
    dest_accessed -> day = temp - 1;

    printf("Enter month:");
    char month[10];
    if(!(check = scanf("%s", month)) || check == - 1)
        return EOF;
    for (int i = 0;i < 12;i++) {
        if (!strcmp(month, month_names[i])) {
            dest_accessed->month = i;
            goto out;
        }
    }

    return EOF;

    out:
    if (dest_accessed -> month > 11 || dest_accessed -> month < 0)
        return EOF;
    if (dest_accessed -> day > month_days[dest_accessed -> month] - 1 || dest_accessed -> day < 0)
        return EOF;
    printf("Enter year:");
    if (check_input(&dest_accessed -> year, 1902, 2037))
        return EOF;
    printf("Enter hour:");
    if (check_input(&dest_accessed -> hour, 0, 23))
        return EOF;
    printf("Enter minute:");
    if (check_input(&dest_accessed -> minute, 0, 59))
        return EOF;
    printf("Enter second:");
    if (check_input(&dest_accessed -> second, 0, 59))
        return EOF;
    printf("Enter utc_offset:");
    if(check_input(&dest_accessed -> utc_offset, -12, 12))
        return EOF;

    dest_accessed -> weekday = calculate_weekday(convert_date_to_gmt_time(dest) - STARTING_TIME_POINT, MONDAY);

    return 0;

}



