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

void render_number(int counter, int j, int days){
    if ((counter % 7) == 0 || j == days) {
        printf("%-3d\n", j);
    } else {
        printf("%-3d", j);
    }
}

void render_colored_number(int counter, int j, int days){
    if ((counter % 7) == 0 || j == days) {  
        printf("\033[31m%-3d\033[0m\n", j);
    } else {
        printf("\033[31m%-3d\033[0m", j);
    }
}

void render_numbers(int days, int counter, int today) {
    for (int j = 1; j <= days; j++) {
        if (j == today){
            render_colored_number(counter, j, days);
        } else {
            render_number(counter, j, days); 
        }
        counter++;
    }
    printf("\n");
}


void render_month(int days, int counter, int month, Today today) {
    printf("%s\n", months[month]);
    printf("MN TS WD TH FR ST SN\n");
    if (today.month == month) {
        render_numbers(days, counter, today.day);
    } else {
        render_numbers(days, counter, -1);
    }

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
                render_month(31, counter, i, today);
                break;
            case APRIL:
            case JUNE:
            case SEPTEMBER:
            case NOVEMBER:
                render_month(30, counter, i, today);
                break;
            case FEBRUARY:
                if (IsLeapYear) {
                render_month(29, counter, i, today);
                break;
                } else {
                render_month(28, counter, i, today);
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
    printf("Day of month: %d. Month: %s Year: %d\n", myday.day, months[myday.month], myday.year);
    return 0;  
}
