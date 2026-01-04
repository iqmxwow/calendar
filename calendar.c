#include <stdio.h>
#include <stdint.h>
#include <time.h>

typedef enum {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} Months;

typedef enum {
    SUNDAY,
    SATURDAY,
    FRIDAY,
    THURSDAY,
    WEDNESDAY,
    TUESDAY,
    MONDAY

} WeekDay;


typedef struct {
    Months month;
    WeekDay wday;
    int day;
    int year;

} Today;


Today get_today() {
    int m, d, wd, y;

    time_t currTime;
    struct tm *localTime;
    
    time(&currTime);
    localTime = localtime(&currTime);
    
    m = localTime->tm_mon;
    d = localTime->tm_mday;
    wd = localTime->tm_wday;
    y = localTime->tm_year + 1900;


    Today return_day = {
        .month = (Months)m,
        .wday = (WeekDay)wd,
        .day = d,
        .year = y
    };

    return return_day;
}

int main() {

    Today myday = get_today();
    printf("Day of month: %d. Year: %d\n", myday.day, myday.year);
    return 0;  
}
