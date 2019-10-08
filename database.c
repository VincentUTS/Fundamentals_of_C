/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, Christopher Wong ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Create a database file and some interfacing tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function saves all items in memory to the database file as plain text.
 * inputs:
 * - item_t* items: This is an array of size MAX_NUM_itemS which will be
 *                      saved to the database. 
 * - int items_size: This is the number of items currently in the array.
 * outputs:
 * - none
*******************************************************************************/
void save_database (item_node_t* item_list) {
	FILE* file_stream;

    char format_string[] = "%003d %l %s %s %s %s\n";

    /* Open/Create the file for writing text data */ 
    file_stream = fopen(DB_NAME, "w");

    /* Check if opening the file was successful */
    if (file_stream == NULL)
    	return;
    
    /*TO DO: SORT ITEMS [merge_sort(item_list);] */

    int i;
    for (i = 0; i < items_size; i++) {

        /* Print each item to the database in the same format that is used
        in the display function. */
    	fprintf(file_stream, format_string, item.ID, item.ISBN,
    	        item.title, item.author, item.type, item.category);
    }
    
    /* Always close the file after you have finished using it. */ 
    fclose(file_stream);
}

/*******************************************************************************
 * This function loads all items from the database file to memory.
 * inputs:
 * - item_node_t* item_list: This is a pointer directing to the linked list of 
 * 							 all items in the database
 * outputs:
 * - none
*******************************************************************************/
void load_database (item_node_t* item_list) {
	FILE* file_stream;
    char format_string[] = "%003d %l %s %s %s %s\n";

    /* Open the file for reading text data */
    file_stream = fopen(DB_NAME, "r");

    /* Check if opening the file was successful */
    if (file_stream == NULL) {
        printf("Read error\n");
    	return;
    }

    int i = 0;

    /* Keep reading records from the file until an invalid line is read
        or memory has been filled*/
    
    while (fscanf(file_stream, format_string, &item_list[i].ID, 
    		&item_list[i].ISBN, item_list[i].title, item_list[i].author, 
			item_list[i].type, item_list[i].category) == 6 &&
            i < MAX_NUM_itemS) {
            i++; /*TO DELETE COMMENT: what is MAX_NUM_itemS value?*/
    }

    /* Update the number of items currently in use as part of the array */
    *items_size = i; /*TO DELETE COMMENT: where are we saving that value?*/   
    
    /* Always close the file once you are no longer using it */
    fclose(file_stream);
}

void getNoOfRecords()
{
  int recordcount=0;
  for (i=0; i<sizeof(struct item),i++)
  {
    if (item[i]== NULL)
    {
      return;

    }
    else{
      recordcount++;
    }
    
  }
  return recordcount;
}



void deleteRecord()
{
  int ID;
  int count=0;
  
  FILE *ptr2 = fopen("c:\\database1.h","a");
  int records = getNoOfRecords();
  refresh();
  fflush(stdin);
  printf("Enter BookID:\n");
  scanf("%d",&ID);
  while(count!=records)
  {
    fread(&var,sizeof(struct item),1,ptr);
    if(var.ID==ID)
    {
    }
    else
    {
      fwrite(&var,sizeof(struct item),1,ptr2);
    }
    count++;
  }
  fcloseall();
  remove("c:\\database.h");
  rename("c:\\database1.h","c:\\database.h");
  printf("Press any key to continue..");
  getch();
}

/*******************************************************************************
 * This function sorts the linked lists based on desired variable.
 * inputs:
 * - item_node_t** start: This is the pointer to the address of the head node 
 * 						  for the linked list containing the data of items.
 * outputs:
 * - none
*******************************************************************************/
/* sorts the linked list by changing next pointers (not data) */
void merge_sort(struct item_node_t** start) 
{ 
    item_node_t* head = *start; 
    item_node_t* a, b; 
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    /* Split head into 'a' and 'b' sublists */
    split_lists(head, &a, &b); 
  
    /* Recursively sort the sublists */
    merge_sort(&a); 
    merge_sort(&b); 
  
    /* answer = merge the two sorted lists together */
    *head = sort_items(a, b); 
} 
  
/*******************************************************************************
 * This function sorts the linked lists based on desired variable.
 * inputs:
 * - item_node_t** start: This is the pointer to the address of the head node 
 * 						  for the linked list containing the data of items.
 * outputs:
 * - item_node_t*: returns the pointer
*******************************************************************************/
struct item_node_t* sort_items(struct item_node_t* a, struct item_node_t* b) {
	
    struct item_node_t* result = NULL; 
  
    /* Base cases */
    if (a == NULL) return b; 
    else if (b == NULL) return a; 
  
    /* Sort via ID */
    if (((item_t*)(a->item_data))->ID <= ((item_t*)(b->item_data))->ID) { 
        result = a; 
        result->next = sort_items(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = sort_items(a, b->next); 
    } 
    
    return result; 
} 
  
/*******************************************************************************
 * This function splits the nodes of the list into two evenly sized lists.
 * inputs:
 * - item_node_t* head: This is the pointer to the head of the full sized
 * 						linked list.
 * - item_node_t** front: This is the pointer to the address of the first half 
 * 						  of nodes of the split list
 * - item_node_t** back: This is the pointer to the address of the second half 
 * 						 of nodes of the split list
 * outputs:
 * - none
*******************************************************************************/
void split_lists(struct item_node_t* head, 
                 struct item_node_t** front, struct item_node_t** back) 
{ 
    struct item_node_t* first_list, second_list; 
    first_list = head; 
    second_list = head->next; 
  
    /* Position nodes to evenly split lists */
    while (second_list != NULL) { 
        second_list = second_list->next; 
        if (second_list != NULL) { 
            first_list = first_list->next; 
            second_list = second_list->next; 
        } 
    } 
  
    /* Splits the lists */
    *front = head; 
    *back = first_list->next; 
    first_list->next = NULL; 
} 
  
/* TO DO: Function to insert a node at the beginging of the linked list 
void add_item(struct item_node_t** head_ref) 
{ 
    struct item_node_t* new_node = 
    		(struct item_node_t*)malloc(sizeof(struct item_node_t)); 
  
    new_node->item_data = create_item(new_node); 
  
    new_node->next = (*head_ref); 
  
    (*head_ref) = new_node; 
} */
