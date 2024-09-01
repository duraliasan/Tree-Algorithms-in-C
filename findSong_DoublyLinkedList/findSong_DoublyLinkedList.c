#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char songName[50];
    int songNumber;
    struct node *prev;
    struct node *next;
};

struct node *createAndInsert(struct node *start)
{
    struct node *newNode, *ptr;
    char songName[50];

    fgets(songName, sizeof(songName), stdin); // this line and next line get the song name. scanf isn't working.
    if (songName[strlen(songName) - 1] == '\n') songName[strlen(songName) - 1] = '\0';

    while (strcmp(songName,"-1"))
    {
        if(start == NULL) //if node is empty, create link list
        {
            newNode = (struct node*)malloc(sizeof(struct node));

            strcpy(newNode->songName, songName);
            newNode->songNumber = 1;

            newNode->prev = NULL;
            newNode->next = NULL;
            start = newNode;
        }
        else //if node isn't empty, actually insert end
        {
            ptr = start;
            newNode = (struct node*)malloc(sizeof(struct node));

            while (ptr->next != NULL) ptr = ptr->next;

            newNode->songNumber = ptr->songNumber + 1;
            strcpy(newNode->songName, songName);

            ptr->next = newNode;
            newNode->prev = ptr;
            newNode->next = NULL;
        }

        fgets(songName, sizeof(songName), stdin);   //this line and next line get the song name. scanf isn't working.
        if (songName[strlen(songName) - 1] == '\n') songName[strlen(songName) - 1] = '\0';
    }
    return start;
}

struct node *FDisplay(struct node *start, int count)
{
    struct node *ptr;
    ptr = start;
    while (ptr != NULL)
    {
        if(ptr->songNumber % count == 1) printf("%s\n", ptr->songName);
        ptr = ptr->next;
    }
    return start; 
}

struct node *LDisplay(struct node *start, int count)
{
    struct node *ptr;
    ptr = start;

    while(ptr->next != NULL) ptr = ptr->next; //go to last node
    int counter = ptr->songNumber % count;

    while (ptr != NULL)
    {
        if (ptr->songNumber % count == counter) printf("%s\n", ptr->songName);
        ptr = ptr->prev;
    }
    return start;
}

int main()
{
    struct node *head = NULL;

    head = createAndInsert(head);

    char start;
    int count;
    scanf(" %c %d", &start, &count);

    if(start == 'L') head = LDisplay(head, count);
    if(start == 'F') head = FDisplay(head, count);
    
    return 0;
}