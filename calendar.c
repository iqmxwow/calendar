#include <stdio.h>
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

typedef struct {
    int month;
    int day;
    int year;

} Today;


Today get_today() {
    int m, d, y;

    time_t currTime;
    struct tm *localTime;
    
    time(&currTime);
    localTime = localtime(&currTime);
    
    m = localTime->tm_mon;
    d = localTime->tm_mday;
    y = localTime->tm_year + 1900;


    Today return_day = {
        .month = m,
        .day = d,
        .year = y
    };

    return return_day;
}


int get_first_wday_of_month(int month, int year){
    struct tm time = {0};

    time.tm_year = year - 1900;
    time.tm_mon = month;
    time.tm_mday = 1;

    mktime(&time);


    return time.tm_wday == 0 ? 0 : (7 - time.tm_wday);
}

// storing wdays for all months in year
int wday_array[12];

int* get_first_wday_of_months(int year){
    for (int i = 0; i < 12; i++){
        wday_array[i] = get_first_wday_of_month(i, year);
    }

    return wday_array;
}


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

void make_indent(int wday){
    int indent = 6 - wday;
    char space = ' ';
    for (int i = 0; i < indent; i++){
        printf("%-3c", space);
    }
}


void render_numbers(int days, int counter, int today) {
    int new_line_counter = 7 - counter;
    for (int j = 1; j <= days; j++) {
        if (j == today){
            render_colored_number(new_line_counter, j, days);
        } else {
            render_number(new_line_counter, j, days); 
        }
        new_line_counter++;
    }
    printf("\n");
}


void render_month(int days, int counter, int month, Today today) {
    printf("%s\n", months[month]);
    printf("MN TS WD TH FR ST SN\n");
    if (today.month == month) {
        make_indent(counter);
        render_numbers(days, counter, today.day);
    } else {
        make_indent(counter);
        render_numbers(days, counter, -1);
    }

}


void render_months(Today today, int* wday_array) {
    bool IsLeapYear;
    if (today.year % 4 == 0) {
        IsLeapYear = true;
    } else {
        IsLeapYear = false;
    }

    for (int i = 0; i < 12; i++) {
        int counter = wday_array[i]; // counter is actually just first wday of month i'm sorry about that
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
    Today day = get_today();
    int *day_wdays = get_first_wday_of_months(day.year);
    render_months(day, day_wdays);
}
