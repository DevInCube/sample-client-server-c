#pragma once

typedef struct Student Student;
struct Student {
    int id;
    char name[100];
    float score;
};

Student * Student_new(int id, const char * name, float score);
Student * Student_newCopy(Student * student);
void Student_free(Student * self);