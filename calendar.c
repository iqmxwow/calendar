#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

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
    int month;
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
        .month = m,
        .wday = (WeekDay)wd,
        .day = d,
        .year = y
    };

    return return_day;
}


char months[12][10] = {
        "JANUARY",
        "FEBRUARY",
        "MARCH",
        "APRIL",
        "MAY",
        "JUNE",
        "JULY",
        "AUGUST",
        "SEPTEMBER",
        "OCTOBER",
        "NOVEMBER",
        "DECEMBER"
};


void render_month(int days, int counter, int month) {
    printf("%s\n", months[month]);
    printf("MN TS WD TH FR ST SN\n");

    for (int j = 1; j <= days; j++) {
        if ((counter % 7) == 0) {
            printf("%-3d\n", j);                
        } else if (j == days) {
            printf("%-3d\n", j);
        } else {
            printf("%-3d", j);
        }
        counter++;
    }
    printf("\n");
}


void render_months(Today today) {
    bool IsLeapYear;
    if (today.year % 4 == 0) {
        IsLeapYear = true;
    } else {
        IsLeapYear = false;
    } 

    for (int i = 0; i < 12; i++) {
        int counter = 1;
        switch((Months)i) {
            case JANUARY:
            case MARCH:
            case MAY:
            case JULY:
            case AUGUST:
            case OCTOBER:
            case DECEMBER:
                render_month(31, counter, i);
                break;
            case APRIL:
            case JUNE:
            case SEPTEMBER:
            case NOVEMBER:
                render_month(30, counter, i);
                break;
            case FEBRUARY:
                if (IsLeapYear) {
                render_month(29, counter, i);
                break;
                } else {
                render_month(28, counter, i);
                break;
                }
            default:
                printf("ERROR"); // idk how you can get error lol
                break;
        }
    }
}




int main() {

    Today myday = get_today();
    render_months(myday);
    printf("TODAY:\n");
    printf("Day of month: %d. Year: %d\n", myday.day, myday.year);
    return 0;  
}
