#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	char strData[50];
	struct _Node* next;
} Node;

int countFileLines(char filename[]) {
	FILE *fin;
	int count = 0; //counter of /n
	char countLines; //countLines will store characters from file here
	fin = fopen(filename, "r");
	if (filename == NULL) {
		printf("FILE DOES NOT EXIST\n");
		exit(1);
	} else {
		while (1) {
			countLines = fgetc(fin); //function to store characters
			if (countLines == EOF) //ends infinite loop when it comes to the end of file
			{
				break;
			} else if (countLines == '\n') //here is where actually \n is found and counted
					{
				count++;
			}
		}
	}
	return count;
}

void writeFile2(char fileName[], char ssData[], Node **oLinkedList) {
	FILE* fin;
	fin = fopen(fileName, "a"); //append is used beside of write because it does not delete data, but controversely adds second loop result to the first
	if (fin == NULL) {
		printf("CAN NOT OPEN FILE");
		exit(1);
	} else {
		fprintf(fin, "%s\n", ssData); //fprintfs substring to the beggining of the oString.txt
		do {
			fprintf(fin, "%s", (*oLinkedList)->strData);
			*oLinkedList = (*oLinkedList)->next;

		} while (*oLinkedList != NULL);
		fprintf(fin, "\n"); //adds extra new line character as in template
		fclose(fin);
	}
}

int isPalindrome(char str[]) {
	int length = strlen(str); //measuring length of the first line string from the str
	int i;
	for (i = 0; i < length; i++) {
		if (str[length - 1 - i] != str[i]) //increments and decrements position of the letter in the string to compare if they are equal or not; substituion of 1 is important because position of the last letter is located in [length-1]
				{
			return 0; //returns number 0 if they are not equal
		}
	}
	return 1; //returns 1 if each letter equal to its opposite
}

char *getPalindrome(char str[]) {
	if (isPalindrome(str) == 0) //calls isPalindrome function and checks its return to return string saying if string in Istring.txt is palindrome or not
			{
		return "Not_Palindrome\n";
	} else {
		return "Is_Palindrome\n";
	}
}

int howManySubstrings(char subStr[], char str[]) {
	int i;
	int repetitions = 0; // counter of /n occurence
	for (i = 0; i < strlen(str); i++) {
		if (subStr[0] == str[i] && subStr[1] == str[i + 1]
				&& subStr[2] == str[i + 2]) //checks first 3 letters of substring with whole 3 letters in the string of iString.txt
						{
			i = i + 2; // stops overlapping; after if function is run it jumps to the next character from where substr was not checked with str
			repetitions++; //counter
		}
	}
	return repetitions;
}

void readFile2(char filename[], char *ArrayPtr[]) {
	FILE *fin;
	int i;
	fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("FILE DOES NOT EXIST\n");
		exit(1);
	} else {
		int numberLines = countFileLines(filename);
		for (i = 0; i < numberLines; i++) {
			char *str = malloc(sizeof(char) * 50), ch;  //dynamically allocating memory
			int j = 0;
			while ((ch = fgetc(fin)) != '\n') {   	//takes each letter until \n
				str[j++] = ch;
			}
			str[j] = '\0';
			ArrayPtr[i] = str;
		}
	}

	fclose(fin);
}

void freeLinkedlist(Node *head) {

	if (head != NULL) {
		freeLinkedlist(head->next);  //Free the memory after allocation
		free(head);
	}

}

void printLinkedlist(Node *head) {
	if (head != NULL) {
		printf("%s", head->strData);  //Print the result to the console
		printLinkedlist(head->next);
	}
}
void appendNode(Node **oLinkedList, char outputLine[]) {
	Node* newnode = (Node*) malloc(sizeof(Node));		//Create node
	newnode->next = NULL;								//Save the output string line to the node
	strcpy(newnode->strData, outputLine);				//Append the node to the output linked list
	*oLinkedList = newnode;
}

void checkSubstringPalindrome2(char ssData[], char *iStringData[],
		Node **oLinkedList, int nrIOfileLines) {

	char oStringData[nrIOfileLines][50];  //2D array to collect all elements
	Node* first = NULL;
	Node* prev = NULL;
	Node* newnode;
	for (int i = 0; i < nrIOfileLines; i++) {
		{
			strcpy(oStringData[i], iStringData[i]);
			strcat(oStringData[i], "\t");
			char x[10];
			sprintf(x, "%i", howManySubstrings(ssData, iStringData[i]));
			strcat(oStringData[i], x);
			strcat(oStringData[i], "\t");
			strcat(oStringData[i], getPalindrome(iStringData[i]));   //Writes each formated line into oStringData
			appendNode(&newnode, oStringData[i]);	//Append to the list from the oStringData
			if (first == NULL) {
				first = newnode;
				(*oLinkedList) = first;
			} else {
				prev->next = newnode;
			}
			prev = newnode;
		}
	}
}

int main() {
	Node* head;
	char*inPtr[50], *subPtr[50];
	int i;
	int fileLines = countFileLines("iStrings.txt");
	int subFileLines = countFileLines("subStrings.txt");
	readFile2("subStrings.txt", subPtr);
	readFile2("iStrings.txt", inPtr);
	for (i = 0; i < subFileLines; i++) {    	 //Iterates substring lines times
		checkSubstringPalindrome2(subPtr[i], inPtr, &head, fileLines);
		printLinkedlist(head);
		writeFile2("oStrings.txt", subPtr[i], &head);
	}
	freeLinkedlist(head);

	return 0;
}
