/* Nesrin Þimþek 150119664 */

#include <stdio.h>  
#include <string.h>
#include <stdlib.h>

// a struct that holds the strings and their lengths
typedef struct strings {
	char str[50];
	int length;
}String;
String strBeforeColon, strAfterComma, *concatenatedStr, strOfInputFile; // the instances of struct
 
// finds the char at the index and returns the ASCII value of that char
// returns -1 if the given index is negative or out of the size of the string 
int charAt(String *s, int index) {
	(*s).length = strlen((*s).str);
	
	if(index >= (*s).length || index < 0)
		return -1;
	else
		return (*s).str[index];
}

// adds s2 to the end of the s1 and returns the concatenated string
String *concat(String *s1, String *s2) {
	int i = 0;
	
	(*s1).length = strlen((*s1).str);
	(*s2).length = strlen((*s2).str);
	(*s1).str[(*s1).length] = ' ';  // adds a space between s1 and s2
	++((*s1).length);
	
	for (i = 0; i < (*s2).length; ++i) {
    	(*s1).str[(*s1).length] = (*s2).str[i];
    	++((*s1).length);
	}

  return s1;
	
}

/* checks by tokenizing the string before colon whether that string includes the string given after comma.
if it includes then returns the length of the including string. if it does not include returns zero */
unsigned int strSearch(String *s1, String *s2) {
		int i = 0, j = 0;
		char *tokenPtr, *arr[100]; // arr is an array that includes all tokenPtr strings 	 
		tokenPtr = strtok((*s1).str, " ");
		
		while( tokenPtr != NULL ) {
    	  arr[i] = tokenPtr;
      	  i++;    
      	  tokenPtr = strtok(NULL, " ");
		}
		
		int s2_is_in_s1 = 0; // means s2 is not in any words in s1		
		(*s2).length = strlen((*s2).str);		
		for(j; j < i; ++j) {
			int result = strncmp(arr[j], (*s2).str, (*s2).length-1); // compares first (*s2).length-1 char of strings.
																	// the reason of -1 is to get rid of '\n' at the end of s2		
			if (result == 0) {
				s2_is_in_s1 = 1; // means s2 is in a word in s1
				return strlen(arr[j]);
				break;			
			}						
		}	
		if (s2_is_in_s1 == 0)
			return 0;	
}


/* calculates the score of the string according to the letter values which is given in the homework 
and returns the score */
unsigned int findScore(String *s1) {
	char ch;
	int i = 0, score = 0;
	
	(*s1).length = strlen((*s1).str);
	
	// checks the whole string to assign the value to each letter and adds that value to the score
	for(i; i < (*s1).length; ++i) {
		ch = (*s1).str[i];
		if(ch >= 'a') // if the letter is lowercase converts it to uppercase
			ch += 'A'-'a'; 
		if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='L' || ch=='N' || ch=='R' || ch=='S' || ch=='T')
			score += 1;
		else if(ch=='D' || ch=='G')
			score += 2;
		else if(ch=='B' || ch=='C' || ch=='M' || ch=='P')
			score += 3;
		else if(ch=='F'||ch=='H'||ch=='V'||ch=='W'||ch=='Y')
			score += 4;
		else if(ch=='K')
			score += 5;
		else if(ch=='J' || ch=='X')
			score += 8;
		else if(ch=='Q' || ch=='Z')
			score += 10;		
	}
	return score;
	
}

// tokenizes the string by colon and comma and adds the tokenPtr strings to the given array
void tokenforColonandComma(char *arr[]) {
		int i = 0;
		char *tokenPtr = strtok(strOfInputFile.str, ":");
		while( tokenPtr != NULL ) {
			arr[i] = tokenPtr;
			i++;    
			tokenPtr = strtok(NULL, ",");
		}	
}

// tokenizes the string by one space and returns the number of words in that string
int find_number_of_words(String *s1) {
		int numberOfWords=0;
	    char *tokenPtr= strtok((*s1).str, " ");
		while( tokenPtr != NULL ) {   	  
			numberOfWords++;    
			tokenPtr = strtok(NULL, " ");
		}
		return numberOfWords;	
}

// checks whether the character in the string is a letter and increases numberOfLetters by one if it is a letter
// returns the number of letters in the string
int find_number_of_letters(String *s1) {	
	char ch;
	int i = 0, numberOfLetters = 0;
	
	(*s1).length = strlen((*s1).str);
	
	for(i; i < (*s1).length; ++i) {
		ch = (*s1).str[i];		
		if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
			numberOfLetters += 1;		
	}	
	return numberOfLetters;	
}

/* according to the option, executes the corresponding functions and 
writes to the output file whatever the result is associated with the user inputs in the input file */
/* takes txt files as command line arguments */
int main(int argc, char *argv[] ) {  
	int ch, option;
	FILE *input_file = fopen(argv[1],"r");
	FILE *output_file = fopen(argv[2],"w");
	char *tokenArray[100]; // this array holds strings after tokenizing
  
	while(fgets(strOfInputFile.str, 100, input_file)) // reads the input file string by string and assigns the string to the strOfInputFile
	{
		int wordNumbers;
		int letterNumbers;
		tokenforColonandComma(tokenArray); // fills tokenArray with strings that are in the tokenized string on the relevant line 
   		
   		// the option value is updated as zero because there is no option for stat, exit and quit
		if(strncmp(strOfInputFile.str,"stat",4) == 0 || strncmp(strOfInputFile.str,"exit",4) == 0 
			|| strncmp(strOfInputFile.str, "quit", 4) == 0)
			option = 0;		 	
		else 
			option = atoi(tokenArray[1]); // assigns the string after colon to the option as an integer by converting that string to an integer
		
		// finds the char at the index, converts it to uppercase if there is a need and writes it to the output file
		// if ASCII value of char is -1 then writes -1 to the output file	
		// also calculates the letter and word numbers of the string on the current line	
		if (option == 1) {
			strcpy(strBeforeColon.str, tokenArray[0]); // assigns the string before colon to strBeforeColon
			int index = atoi(tokenArray[2]);  // assigns the string after comma to the index as an integer by converting that string to an integer	
			ch = charAt(&strBeforeColon, index); 
			
			if (ch == -1)
				fprintf(output_file, "%d\n", ch);					
			else if(ch >= 'a')
				ch += 'A'-'a';			  
			
			fprintf(output_file, "%c\n", ch);
			letterNumbers += find_number_of_letters(&strBeforeColon);
			wordNumbers += find_number_of_words(&strBeforeColon);		
		}
		
		// finds the concatenated string by executing concat function and writes it to the output file
		// also calculates the letter and word numbers of the string on the current line
		if(option == 2){
			strcpy(strBeforeColon.str, tokenArray[0]);
			strcpy(strAfterComma.str, tokenArray[2]); // assigns the string after comma to strAfterComma
			concatenatedStr = concat(&strBeforeColon, &strAfterComma);
			fprintf(output_file, "%s", (*concatenatedStr).str);	
			letterNumbers += find_number_of_letters(concatenatedStr);
			wordNumbers += find_number_of_words(concatenatedStr);				
		}
		
		// writes the length of the string before colon which includes the given string after comma to the output file
		// also calculates the letter and word numbers of the string on the current line
		if(option == 3){
			strcpy(strBeforeColon.str, tokenArray[0]);
			strcpy(strAfterComma.str, tokenArray[2]);
			String a;
			a = strBeforeColon;
			fprintf(output_file,"%u\n",strSearch(&a, &strAfterComma));
			letterNumbers += find_number_of_letters(&strBeforeColon) + find_number_of_letters(&strAfterComma);
			wordNumbers += find_number_of_words(&strBeforeColon) + find_number_of_words(&strAfterComma);					
		}			
		
		// writes the score of the string on the current line to the output file
		// also calculates the letter and word numbers of the string on the current line
		if(option == 4){
			strcpy(strBeforeColon.str, tokenArray[0]);
			fprintf(output_file, "%u\n", findScore(&strBeforeColon));
			letterNumbers += find_number_of_letters(&strBeforeColon);
			wordNumbers += find_number_of_words(&strBeforeColon);		
		}
		
		// if the string on the line is stat, writes the total number of words and letters to the output file
		if(strncmp(strOfInputFile.str, "stat", 4) == 0){			
			fprintf(output_file, "The number of words: %d\n", wordNumbers);			
			fprintf(output_file, "The number of alphabetic letters: %d\n", letterNumbers);
		}
		
		// if the string on the line is exit or quit, writes a relevant message to the output file and ends the while loop
		if(strncmp(strOfInputFile.str, "exit", 4) == 0 || strncmp(strOfInputFile.str, "quit", 4) == 0){
			fprintf(output_file, "Program ends. Bye\n");
			break;
		}
                                  
    }
    
    //closes the files
    fclose(input_file);
    fclose(output_file);
    return 0;
    
}  
