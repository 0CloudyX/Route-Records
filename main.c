#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RouteRecords.h"
void printMenu(){
  printf("\n\n######### Airline Route Records Database MENU #########\n" );
  printf("1. Search by Route\n");
  printf("2. Search by Origin Airport\n");
  printf("3. Search by Destination Airport\n");
  printf("4. Search by Airline\n");
  printf("5. Quit\n" );
  printf("Enter your selection: ");
}
int main(int argc, char*argv[]){
  FILE* inFile = NULL;
  RouteRecord* r;
  SearchType search;
  int optChoice;
  int uniqueRoutes;
  char origin[4];
  char dest[4];
  char line[3];

  
  if( argc != 2 ) {
    printf("ERROR: Missing file name\n");\
    return 1; // 1 indicates error                                              
  }
  printf("\nOpening data.csv\n");
	   printf("");
	inFile = fopen("data.csv", "r");
   
	if( inFile == NULL ) {
    printf("\nCould not open file %s.\n", argv[1]);
    return -1; // -1 indicates error                                            
  }

	r = createRecords(inFile);
	uniqueRoutes =fillRecords(r, inFile);
	printf("Unique routes operated by airlines: %d\n\n", uniqueRoutes);  
  fclose(inFile);
  
  while(optChoice != 5){
    printMenu();
    scanf("%d", &optChoice);
    
    if((optChoice == 0)||(!isalnum(optChoice))){
      printf("\nInvalid choice.");
			}
    if((optChoice < 1)||(optChoice > 5)){
      printf("\nThis is not a number, please enter a number 1-5");
      break; 
    }
    if(optChoice == 1){
      printf("\nEnter origin:");
      scanf("%s", origin);
      printf("\nEnter destination:");
      scanf("%s", dest);
      search = ROUTE;
      searchRecords(r, uniqueRoutes, origin, dest, search);
    }
    if(optChoice == 2){
      printf("Enter origin: ");
      scanf("%s", origin);
      search = ORIGIN;
      searchRecords(r, uniqueRoutes, origin, dest, search);
    }
    if(optChoice == 3){
      printf("Enter destination: ");
      scanf("%s", dest);
      search = DESTINATION;
      searchRecords(r, uniqueRoutes, origin, dest, search);
    }
    if(optChoice == 4){
      printf("Enter Airline: ");
      scanf("%s", line);
      search = AIRLINE;
      searchRecords(r, uniqueRoutes, line, dest, search);
    }
    if(optChoice == 5){
      printf("Quit");
    }
  }  
}