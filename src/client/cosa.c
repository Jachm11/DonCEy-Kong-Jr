#include<stdio.h>
#include <string.h>

int main() {
   char string[100] = "LIVES:2|POINTS:120|70,570|1,200,400:2,800,380|580,490";
   // Extract the first token
   char * token = strtok(string, "|");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, "|");
   }
   return 0;
}
