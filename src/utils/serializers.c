#include "includes/serializers.h"


adj_list_serialize_t *adj_list_serializer(adj_list_t *a){

	/** 
	 * Since this structure uses linked lists, we'll want to
	 * create a serializer that allocates the memory into an array
	 * This is to avoid the use of NULL pointers on the python interface
	*/

	adj_list_serialize_t *l; 
	l = (adj_list_serialize_t*)malloc(sizeof(adj_list_serialize_t));
	l->items = malloc(a->v * sizeof(node_list_serialize_t)); 	
	l->vertice_count = a->v;
	printf("Do you work\n"); 

	for(int i = 0; i < l->vertice_count; i++){

		printf("Vertice: %d\n", i); 
		l->items[i] = malloc(sizeof(node_list_serialize_t));
		l->items[i]->items = malloc(a->v * sizeof(char*)); 

		int counter = 0;  
		node_t *head = a->items[i].head; 

		while(head != NULL){

			/* copy node value into serializer */
			char *label = head->label; 
			size_t label_size = strlen(label) + 1; 
			l->items[i]->items[counter] = malloc(label_size * sizeof(char)); 
			strcpy(l->items[i]->items[counter], label); 

			printf(" -> %s ", head->label); 
			head = head->next; 
			counter += 1; 
		}
		printf("\n"); 
		
	}

	return l; 
}

