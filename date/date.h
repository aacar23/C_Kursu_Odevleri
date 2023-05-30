#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <time.h>

#define GM (0)

#define STARTING_TIME_POINT (-2208988800)
#define ENDING_TIME_POINT (21459167999)

#define CONV_FAILURE (LLONG_MIN)
#define CMP_FAILURE (-2)
#define DIFF_FAILURE (LLONG_MAX)

#define SECONDS_IN_A_COMMON_YEAR (365 * 24 * 60 * 60)
#define SECONDS_IN_A_LEAP_YEAR (366 * 24 * 60 * 60)
#define SECONDS_IN_A_DAY (24 * 60 * 60)
#define SECONDS_IN_AN_HOUR (60 * 60)
#define SECONDS_IN_A_MINUTE (60)

#define DATE_STR_SIZE (37)

typedef struct{
    void *address;
}date;

typedef enum DIFF_OF_MEMBER{DAY, MONTH, YEAR, HOUR, MINUTE, SECOND}DIFF_OF_MEMBER;

typedef char date_string[DATE_STR_SIZE];

//activation functions

extern date *allocate_date(void);
extern void activate_date(date *p, int utc_offset_value);

//deactivation functions

extern void free_date(date *p);
extern void deactivate_date(date *p);

//setter functions

extern date* set_date(date *p, int day_value, int month_value, int year_value, int hour_value, int minute_value, int second_value, int utc);
extern date *set_date_from_time_t(date *p, time_t sec);
extern date *set_date_from_str(date *date_p, const char *str);
extern date *set_date_today(date *p);
extern date *set_date_random(date *p);

extern date *set_year(date *p, int year_value);
extern date *set_month(date *p, int month_value);
extern date *set_day(date *p, int day_value);
extern date *set_hour(date *p, int hour_value);
extern date *set_minute(date *p, int minute_value);
extern date *set_second(date *p, int second_value);

extern int set_utc(date *p, int utc_zone_value);

extern date *set_n_days_after_date(date *dest, const date *source, int n);
extern date *set_n_days_before_date(date *dest, const date *source, int n);
extern date *set_n_months_after_date(date *dest, const date *source, int n);
extern date *set_n_months_before_date(date *dest, const date *source, int n);
extern date *set_n_years_after_date(date *dest, const date *source, int n);
extern date *set_n_years_before_date(date *dest, const date *source, int n);

//getter functions

extern int get_day_gmt(const date *p);
extern const char *get_month_gmt(const date *p);
extern int get_year_gmt(const date *p);
extern int get_hour_gmt(const date *p);
extern int get_minute_gmt(const date *p);
extern int get_second_gmt(const date *p);
extern const char *get_weekday_gmt(const date *date_p);
extern int get_nth_day_of_the_year_gmt(const date *p);

extern int get_day_local(const date *p);
extern const char *get_month_local(const date *p);
extern int get_year_local(const date *p);
extern int get_hour_local(const date *p);
extern int get_minute_local(const date *p);
extern int get_second_local(const date *p);
extern const char *get_weekday_local(const date *p);
extern int get_nth_day_of_the_year_local(const date *p);

//utility functions

extern char *date_to_str_gmt(const date *p);
extern char *date_to_str_local(const date *p);
extern char *write_date_to_str_gmt(char *dest, const date *p);
extern char *write_date_to_str_local(char *dest, const date *p);
extern const date *time_to_date(const time_t *timer, int utc);
extern date *copy_date(date *dest, const date *src);
extern time_t convert_date_to_gmt_time(const date *p);
extern time_t convert_date_to_local_time(const date *p);
extern int compare_dates_universal_time(const date *p1, const date *p2);
extern int compare_dates_local_time(const date *p1, const date *p2);
extern long date_difference(const date *p1, const date *p2, DIFF_OF_MEMBER member);


//input output functions

extern void print_date_gmt(const date *p);
extern void print_date_local(const date *p);
extern int scan_date(date *p);
#endif

