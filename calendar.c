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

// it's cursed ngl
void render_months() {
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
    // holy loops
    // TODO: make function for loop in switch
    for (int i = 0; i < 12; i++) {
        printf("%s\n", months[i]);
        printf("MN TS WD TH FR ST SN\n");
        int counter = 1;
        switch((Months)i) {
            case JANUARY:
            case MARCH:
            case MAY:
            case JULY:
            case AUGUST:
            case OCTOBER:
            case DECEMBER:
                for (int j = 1; j <= 31; j++) {
                    if ((counter % 7) == 0) {
                        printf("%-3d\n", j);
                        
                    } else if (j == 31) {
                        printf("%-3d\n", j);
                    } else {
                        printf("%-3d", j);
                    }
                    counter++;
                }
                break;

            case APRIL:
            case JUNE:
            case SEPTEMBER:
            case NOVEMBER:
                for (int j = 1; j <= 30; j++) {
                    if ((counter % 7) == 0) {
                        printf("%-3d\n", j);

                    }  else if (j == 30) {
                        printf("%-3d\n", j);
                    } else {
                        printf("%-3d", j);
                    }
                    counter++;
                }
                break;

            case FEBRUARY:
                for (int j = 1; j <= 28; j++) {
                    if ((counter % 7) == 0) {
                        printf("%-3d\n", j);

                    }  else if (j == 28) {
                        printf("%-3d\n", j);
                    } else {
                        printf("%-3d", j);
                    }
                    counter++;
                }
                break;
            
            default:
                printf("ERROR");
                break;
        }
        printf("\n");
    }
}



int main() {

    Today myday = get_today();
    render_months();
    printf("TODAY:\n");
    printf("Day of month: %d. Year: %d\n", myday.day, myday.year);
    return 0;  
}
