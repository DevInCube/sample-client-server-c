#include <student.h>
#include <string.h>
#include <stdlib.h>

Student * Student_new(int id, const char * name, float score) {
    Student * self = malloc(sizeof(Student));
    self->id = id;
    strcpy(self->name, name);
    self->score = score;
    return self;
}
Student * Student_newCopy(Student * student) {
    return Student_new(student->id, student->name, student->score);
}
void Student_free(Student * self) {
    free(self);
}