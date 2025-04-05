#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S_LEN 20

typedef struct node
{
   // char *s;
   int i;
   struct node *next;
   struct node *prev;
} node_t;

void print(node_t *head, node_t *tail)
{
   printf("In order:\n");
   for (node_t *current = head->next; current != tail; current = current->next)
   {
      printf("\tElement %d\n", current->i);
   }

   printf("\nReversed\n");
   for (node_t *current = tail->prev; current != head; current = current->prev)
   {
      printf("Element %d\n", current->i);
   }
}

int insert(node_t *head, node_t *tail, int i)
{
   // Go to penultimate element
   node_t *current = head;
   while (current->next != NULL)
   {
      current = current->next;
   }

   node_t *new_node = (node_t *)malloc(sizeof(node_t));
   new_node->i = i;

   current->next = new_node;
   new_node->prev = current;

   new_node->next = tail;
   tail->prev = new_node;

   printf("Inserted %i\n", i);
   print(head, tail);

   return 0;
}

void find(char *s, char *s2)
{
}

void delete(char *s)
{
}

int main()
{
   node_t *head = (node_t *)malloc(sizeof(node_t));
   head->i = 0;
   head->prev = NULL;
   head->next = NULL;

   node_t *tail = (node_t *)malloc(sizeof(node_t));
   tail->i = 0;
   tail->prev = NULL;
   tail->next = NULL;

   int i;
   for (;;)
   {
      printf("Choose an option\n");
      printf("1 - Insert at the end\n");
      printf("2 - Find an element\n");
      printf("3 - Delete an item\n");
      printf("4 - Print the list\n");
      scanf("%d", &i);
      switch (i)
      {
      case 1:
         printf("Insert a number: ");
         scanf("%d", &i);
         insert(head, tail, i);
         break;

      case 4:
         print(head, tail);
         break;

      default:
         printf("Invalid option, try again.");
         break;
      }
      printf("\n");
   }

   print(head, tail);

   return 0;
}
