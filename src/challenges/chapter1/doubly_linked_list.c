#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_S_LEN 100

typedef struct node
{
   char *s;
   struct node *next;
   struct node *prev;
} node_t;

void print(node_t *head, node_t *tail)
{
   printf("In order:\n");
   for (node_t *current = head->next; current != tail; current = current->next)
   {
      printf("\tElement %s\n", current->s);
   }

   printf("\nReversed\n");
   for (node_t *current = tail->prev; current != head; current = current->prev)
   {
      printf("Element %s\n", current->s);
   }
}

int insert(node_t *head, node_t *tail, const char *input)
{
   node_t *current = head;
   while (current->next != tail)
   {
      current = current->next;
   }

   node_t *new_node = (node_t *)malloc(sizeof(node_t));
   new_node->s = strdup(input);

   current->next = new_node;
   new_node->prev = current;

   new_node->next = tail;
   tail->prev = new_node;

   printf("Inserted %s\n", input);

   return 0;
}

void find(node_t *head, node_t *tail, const char *input)
{
   int i = 0;
   for (node_t *current = head->next; current != tail; current = current->next, i++)
   {
      if (strcmp(current->s, input) == 0)
      {
         printf("\tFound element at index %d\n", i);
         return;
      }
   }

   printf("Did not find %s\n", input);
}

void delete(node_t *head, node_t *tail, const char *input)
{
   int i = 0;
   for (node_t *current = head->next; current != tail; current = current->next, i++)
   {
      if (strcmp(current->s, input) == 0)
      {
         current->prev->next = current->next;
         current->next->prev = current->prev;

         free(current->s);
         free(current);

         printf("\tDeleted element at index %d\n", i);
         return;
      }
   }

   printf("Did not find %s\n", input);
}

void free_all(node_t *head, node_t *tail)
{
   node_t *current = head->next;
   while (current != tail)
   {
      node_t *next = current->next;
      free(current->s);
      free(current);
      current = next;
   }

   free(head);
   free(tail);
}

int main()
{
   node_t *head = (node_t *)malloc(sizeof(node_t));
   node_t *tail = (node_t *)malloc(sizeof(node_t));

   head->s = NULL;
   head->prev = NULL;
   head->next = tail;

   tail->s = NULL;
   tail->prev = head;
   tail->next = NULL;

   for (;;)
   {
      printf("Choose an option\n");
      printf("0 - Exit\n");
      printf("1 - Insert at the end\n");
      printf("2 - Find an element\n");
      printf("3 - Delete an item\n");
      printf("4 - Print the list\n");

      int i;
      char buffer[MAX_S_LEN];

      if (fgets(buffer, sizeof(buffer), stdin) == NULL)
         break;

      if (sscanf(buffer, "%d", &i) != 1)
      {
         printf("Invalid format, try again.");
         continue;
      }

      switch (i)
      {
      case 0:
         printf("Exiting!\n");
         free_all(head, tail);
         return 0;

      case 1:
         printf("Insert a string: ");
         if (fgets(buffer, sizeof(buffer), stdin) != NULL)
         {
            buffer[strcspn(buffer, "\n")] = 0;
            insert(head, tail, buffer);
         }
         break;

      case 2:
         printf("Find string: ");
         if (fgets(buffer, sizeof(buffer), stdin) != NULL)
         {
            buffer[strcspn(buffer, "\n")] = 0;
            find(head, tail, buffer);
         }
         break;

      case 3:
         printf("Delete element: ");
         if (fgets(buffer, sizeof(buffer), stdin) != NULL)
         {
            buffer[strcspn(buffer, "\n")] = 0;
            delete (head, tail, buffer);
         }
         break;

      case 4:
         print(head, tail);
         sleep(1);
         break;

      default:
         printf("Invalid option, try again.");
         break;
      }

      system("clear");
   }

   return 0;
}
