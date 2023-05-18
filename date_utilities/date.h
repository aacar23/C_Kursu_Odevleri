#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <time.h>

typedef struct{
    void *address;
}date;

//activation functions

extern date *create_date(void);
extern date *activate_date(date *p);

//get functions

extern time_t get_day(const date *p);
extern time_t get_month(const date *p);
extern time_t get_year(const date *p);
extern time_t get_weekday(const date *p);

//set functions

extern date *set_date_from_str(date *p, const char *pstr);
extern date* set_date(date *p, time_t day_value, time_t month_value, time_t year_value);
extern date *set_date_from_time_t(date *p, time_t sec);
extern date *set_date_today(date *p);
extern date *set_year(date *p, time_t year);
extern date *set_month(date *p, time_t month);
extern date *set_month_day(date *p, time_t day);
extern date *set_date_random(date *p);

//utility functions

extern date *copy_date(date *dest, date *src);
extern time_t nth_day_of_the_year(date *p);
extern time_t convert_date_to_seconds(const date *p);
extern int compare_dates(const date *p1, const date *p2);
extern int date_difference(const date *p1, const date *p2);
extern date *n_days_after_date(date *dest, const date *source, int n);
extern date *n_days_before_date(date *dest, const date *sources, int n);

//input output functions

extern void print_date(const date *p);
extern void scan_date(date *p);

#endif
