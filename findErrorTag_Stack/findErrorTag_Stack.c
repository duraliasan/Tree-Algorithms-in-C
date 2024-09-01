#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
    char tag[50];
    struct stack *next;
};

struct stack *push(struct stack *top, char *val)
{
    struct stack *ptr = (struct stack *)malloc(sizeof(struct stack));
    strcpy(ptr->tag, val);
    ptr->next = top;
    top = ptr;
    return top;
}

struct stack *pop(struct stack *top)
{
    struct stack *ptr;
    ptr = top;
    top = top->next;
    free(ptr);
    return top;
}

void checkHTMLTags(char *html)
{
    struct stack *top = NULL;
    char tag[50];
    int i = 0, j;

    while (html[i] != 0)
    {
        if (html[i] == '<')
        {
            j = 0;
            i++;

            if (html[i] == '/')
            {
                i++;
                while (html[i] != '>' && html[i] != 0) tag[j++] = html[i++];
                tag[j] = 0;

                if (top == NULL)
                {
                    printf("error </%s>", tag);
                    return;
                }
                else
                {
                    char *topTag = top->tag;

                    if (strcmp(tag, topTag) == 0) top = pop(top);
                    else
                    {
                        printf("error <%s>", topTag);
                        return;
                    }
                }
            }
            else
            {
                while (html[i] != '>' && html[i] != 0) tag[j++] = html[i++];
                tag[j] = 0;
                top = push(top, tag);
            }
        }
        i++;
    }

    if (top == NULL) printf("correct");
    else
    {
        while (top != NULL)
        {
            printf("error <%s>", top->tag);
            top = pop(top);
        }
    }
}

int main()
{
    char html[500];
    fgets(html, sizeof(html), stdin);
    checkHTMLTags(html);
    return 0;
}
