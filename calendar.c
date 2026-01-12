#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    UNKNOWN_ARGUMENT = 101
} ErrorCode;

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
    int month; // 0-11 (jan-dec)
    int day;
    int year; // counting from 1900

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


    return time.tm_wday == 0 ? 0 : (7 - time.tm_wday); // from 0-6 (sn,mn-st) to 0-6 (sn-mn)
}

// storing wdays for all months in year
int wday_array[12];

int* get_first_wday_of_months(int year){
    for (int i = 0; i < 12; i++){
        wday_array[i] = get_first_wday_of_month(i, year);
    }

    return wday_array;
}


void render_number(int new_line_counter, int j, int days){
    if ((new_line_counter % 7) == 0 || j == days) {
        printf("%-3d\n", j);
    } else {
        printf("%-3d", j);
    }
}

void render_colored_number(int new_line_counter, int j, int days){
    if ((new_line_counter % 7) == 0 || j == days) {  
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


void render_numbers(int days, int wday, int today) {
    int new_line_counter = 7 - wday;
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


void render_month(int days, int wday, int month, Today today) {
    printf("%s\n", months[month]);
    printf("MN TS WD TH FR ST SN\n");
    if (today.month == month) {
        make_indent(wday);
        render_numbers(days, wday, today.day);
    } else {
        make_indent(wday);
        render_numbers(days, wday, -1);
    }

}

void choose_render_month(Months month, int wday, Today today) {
    bool IsLeapYear;
    if (today.year % 4 == 0) {
        IsLeapYear = true;
    } else {
        IsLeapYear = false;
    }

    switch(month) {
            case JANUARY:
            case MARCH:
            case MAY:
            case JULY:
            case AUGUST:
            case OCTOBER:
            case DECEMBER:
                render_month(31, wday, (int)(month), today);
                break;
            case APRIL:
            case JUNE:
            case SEPTEMBER:
            case NOVEMBER:
                render_month(30, wday,  (int)(month), today);
                break;
            case FEBRUARY:
                if (IsLeapYear) {
                render_month(29, wday, (int)(month), today);
                break;
                } else {
                render_month(28, wday, (int)(month), today);
                break;
                }
            default:
                printf("ERROR"); // idk how you can get error lol
                break;
        }

}

void render_months(Today today, int* wday_array) {

    for (int i = 0; i < 12; i++) {
        int wday = wday_array[i];   
        choose_render_month((Months)(i), wday, today);
    }
}




int main(int argc, char *argv[]) {
    Today day = get_today();
    int *day_wdays = get_first_wday_of_months(day.year);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-y") == 0) {
            render_months(day, day_wdays);
            
        } else if (strcmp(argv[i], "-m") == 0) {
            choose_render_month((Months)(day.month), wday_array[day.month], day);
        } else {
            ErrorCode err = UNKNOWN_ARGUMENT;
            fprintf(stderr, "Error unknown argument, error code: %d\n", (int)(err));
            fprintf(stderr, "Error -> %s\n", argv[i]);
            exit((int)(err));
        }
    }
    return 0;
}
