#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    char name[50];
    int priority;
    struct person *next;
};

int prioritysAsignment(char *name)
{
    if (strcmp(name, "Annem") == 0 || strcmp(name, "Babam") == 0 || strcmp(name, "Kardesim") == 0) return 1;
    else if (strcmp(name, "Amcam") == 0 || strcmp(name, "Teyzem") == 0 || strcmp(name, "Dayim") == 0 || strcmp(name, "Halam") == 0) return 2;
    else if (strcmp(name, "Isyeri") == 0 || strcmp(name, "Okul") == 0) return 3;
    else if (strcmp(name, "Arkadasim1") == 0 || strcmp(name, "Arkadasim2") == 0 || strcmp(name, "Arkadasim3") == 0 || strcmp(name, "Arkadasim4") == 0 || strcmp(name, "Arkadasim5") == 0) return 4;
    else if (strcmp(name, "Banka") == 0 || strcmp(name, "Kargo") == 0) return 5;
    else if (strcmp(name, "Reklam") == 0) return 6;
}

struct person *insert(struct person *start, char *name)
{
    int priority = priorityAssignment(name);
    struct person *ptr, *p;

    ptr = (struct person *)malloc(sizeof(struct person));

    ptr->priority = priority;
    strcpy(ptr->name, name);

    if (start == NULL || priority < start->priority)
    {
        ptr->next = start;
        start = ptr;
    }
    else
    {
        p = start;
        while (p->next != NULL && (p->next->priority < priority || (p->next->priority == priority && strcmp(p->next->name, name) < 0))) p = p->next;
        ptr->next = p->next;
        p->next = ptr;
    }
    return start;
}

void display(struct person *start)
{
    struct person *ptr;
    ptr = start;
    if (start == NULL) return;
    while (ptr != NULL)
    {
        printf("%s\n", ptr->name);
        ptr = ptr->next;
    }
}

int main()
{
    struct person *start = NULL;
    char name[50];

    while (1)
    {
        scanf("%s", name);
        if (strcmp(name, "-1") == 0) break;
        start = insert(start, name);
    }

    display(start);
    return 0;
}