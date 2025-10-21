#include <stdio.h>
#include <stdlib.h>
#include "RouteRecords.h"
#include <string.h>

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st ){

  int i;
  int j;
  int total;
  int match = 0;
  int passTotal[6] = {0, 0, 0, 0, 0, 0};
  
  switch (st) {
  case ROUTE:
    printf("Searching by route...\n");
    for (i = 0; i < length; i++) {
      if ((strcmp(r[i].originAirportCode, key1)) == 0 && (strcmp(r[i].destinationAirportcode, key2) == 0)) {
        match++;
        printf("%s (%s-%s) ", r[i].airlineCode, r[i].originAirportCode,r[i].destinationAirportcode);
        for (j = 0; j < 6; j++) {
          (passTotal[j]) += r[i].passengerCount[j];
					}
      }
    }
    break;

  case ORIGIN:
    printf("Searching by origin...\n");
    for (i = 0; i < length; i++) {
      if (strcmp(r[i].originAirportCode, key1) == 0) {
        match++;
        printf("%s (%s-%s) ", r[i].airlineCode, r[i].originAirportCode,r[i].destinationAirportcode);
        for (j = 0; j < 6; j++) {
          (passTotal[j]) += r[i].passengerCount[j];
        }
      }
    }
    break;

  case DESTINATION:
    printf("Searching by destination...\n");
    for (i = 0; i < length; i++) {
      if (strcmp(r[i].destinationAirportcode, key2) == 0) {
        match++;
        printf("%s (%s-%s)", r[i].airlineCode, r[i].originAirportCode,r[i].destinationAirportcode);
        for (j = 0; j < 6; j++) {
          passTotal[j] += r[i].passengerCount[j];
        }
      }
    }
    break;
    

  case AIRLINE:
    printf("lol y");
    printf("Searching by airline...\n");
    for (i = 0; i < length; i++) {
      if (strcmp(r[i].airlineCode, key1) == 0){
        match++;
        printf("%s (%s-%s)", r[i].airlineCode, r[i].originAirportCode,r[i].destinationAirportcode);
        for (j = 0; j < 6; j++) {
          passTotal[j] += r[i].passengerCount[j];
        }
      
      }
    }

    break;
  default:
    break;
  }
  printf("\n%d matches were found.\n", match);
  printf("\n");
  printf("Statistics:\n");
  total = passTotal[0] + passTotal[1] + passTotal[2] + passTotal[3] + passTotal[4] + passTotal[5];
  printf("Total Passengers: %d\n", total);
  for (i = 0; i < 6; i++) {
    printf("Total Passengers in Month %d: %d\n", i + 1, passTotal[i]);
  }
  
  printf("Average Passengers per month: %d\n", total / 6);
  
}

int findAirlineRoutes( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx ){

  

  if(curIdx == length){
    return -1;
  } 
  else if((strcmp(r[curIdx].originAirportCode, origin) == 0)&&(strcmp(r[curIdx].destinationAirportcode, destination) == 0)&&(strcmp(r[curIdx].airlineCode, airline) == 0)){
    return (curIdx);
  } 
  else{
    return findAirlineRoutes(r, (length), origin, destination, airline, (curIdx+1));
  }
}

RouteRecord* createRecords( FILE* fileIn ){

  char line[50];
  int lines;
  RouteRecord* arr;
  int j;

  while(!feof(fileIn)){
    fgets(line, 50, fileIn);
    if(strchr(line,'\n') != NULL){
      ++lines;
    }
  }

  arr = (RouteRecord*)malloc(lines*sizeof(RouteRecord));

  for (int j = 0; j<lines; j++){
    arr[j].passengerCount[0] = 0;
    arr[j].passengerCount[1] = 0;
    arr[j].passengerCount[2] = 0;
    arr[j].passengerCount[3] = 0;
    arr[j].passengerCount[4] = 0;
    arr[j].passengerCount[5] = 0;
  }

  rewind(fileIn);
  return arr;
}

int fillRecords(RouteRecord* r, FILE* fileIn){

  char buffer[1000];
  char headerLine[100]; //throw away variable
  int month;
  char origin[4];
  char destination[4];
  char airline[3];
  char trashVar[11];
  int passCount;
  int returnNum;
  int i = 0;
  int index = 0;

  fgets(headerLine, 100, fileIn);

  while(!feof(fileIn)){

    fgets(buffer,1000,fileIn);
    sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, trashVar, 
      &passCount);

    
    returnNum = findAirlineRoutes(r, index, origin, destination, airline, i);

    if(returnNum == -1){
        
      strcpy(r[index].originAirportCode, origin);
      strcpy(r[index].destinationAirportcode, destination);
      strcpy(r[index].airlineCode, airline);

      r[index].passengerCount[month - 1] = r[index].passengerCount[month - 1] + passCount;
      index++;

    }
    else{

      r[returnNum].passengerCount[month - 1] = r[returnNum].passengerCount[month - 1] + passCount;
    }
    
    
  } 
  return index;
}