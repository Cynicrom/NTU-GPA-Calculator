// Accurate as of 13 July 2022

/**
    Semester GPA Calculator for National Taiwan University
    Grading scheme:
    A+=4.3 A=4.0 A-=3.7 B+=3.3 B=3.0 B-=2.7 C+=2.3 C=2.0 C-=1.7 F=0 X=0
**/

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

float toFloat(char *str);
float getGrade(char *letter_grade);

int main(int argc, char **argv) {
    // argv contains the grades and credits
    // format: <grade> <credits> <grade> <credits> <grade> ...
    // e.g., ./gpa-calc A+ 1 B+ 2 A 3 C+ 2
    // each <grade> <credits> pair represents one course
    assert(argc > 1);
    int num_of_courses = (argc - 1) / 2;
    float sum = 0.0;
    float credits = 0.0;
    for(int i = 0; i < num_of_courses; i++) {
        float curr_credits = toFloat(argv[i * 2 + 2]);
        credits += curr_credits;
        sum += curr_credits * getGrade(argv[i * 2 + 1]);
    }
    fprintf(stdout, "GPA: %.2f\n", sum / credits);
    return 0;
}

float toFloat(char *str) {
    int length = strlen(str);
    assert(length >= 1);
    float num = 0.0;
    bool negative = (str[0] == '-') ? true : false;
    int i = negative ? 1 : 0;
    float decimal = 1.0;
    for(; i < length; i++) {
        if(str[i] == '.') {
            decimal = 0.1;
        } else if(decimal == 1.0) {
            num = num * 10 + (float)(str[i] - '0');
        } else {
            num += (float)(str[i] - '0') * decimal;
            decimal *= 0.1;
        }
    }
    return negative ? -num : num;
}

float getGrade(char *letter_grade) {
    int length = strlen(letter_grade);
    assert(length > 0);
    float grade = 2.0 - (float)(letter_grade[0] - 'C');
    if(length > 1) {
        grade += letter_grade[1] == '+' ? 0.3 : -0.3;
    }
    return grade;
}
