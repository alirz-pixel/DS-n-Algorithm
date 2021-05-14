#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    printf("[----- [최문형] [2020039004] -----]\n");

	char command;
	int key;

    do{
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                     Graph Searches\n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertex        = v          Insert Edge           = e    \n");
        printf(" Depth First Search   = d          Breath First Search   = b    \n");
        printf(" Print Graph          = p          Quit                  = q    \n");
        printf("----------------------------------------------------------------\n");
        
        printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
            case 'z': case 'Z':
                break;

            case 'v': case 'V':
                break;
                
            case 'e': case 'E':
                break;

            case 'd': case 'D':
                break;

            case 'b': case 'B':
                break;

            case 'p': case 'P':
                break;

            case 'q': case 'Q':
                break;

            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    }while(command != 'q' && command != 'Q');
}