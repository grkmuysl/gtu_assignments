#include <stdio.h>

	
void numberToChar(int charCount , int myKey){ /* turn numbers to char in the comment line. */
	char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?',
	'\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9'};
	
	int firstDigit = charCount % 10; /* take mod to find first digit. */
	int secondDigit = (charCount - firstDigit) / 10 ;  /* find second digit. */
	char firstDigitChar,secondDigitChar;
	firstDigitChar = firstDigit + '0'; /* convert number to char according to alphabet to compare  */
	secondDigitChar = secondDigit + '0';
	
	int i=0;
		for(i ; i <= 61 ; i++){
			int value = i + myKey;
			if(alphabet[i] == secondDigitChar){
				printf("%c" , alphabet[value % 61]);  /* print the matches digits to console*/
				secondDigitChar += '0';
			}
			if(alphabet[i] == firstDigitChar){
				printf("%c" , alphabet[value % 61]);
				firstDigitChar += '0';}
		}
}	
	
int main(){

	char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?',
	'\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9'};
		
	long long int studentId = 230104004174;
	int digitSums = 0;
	int myKey;
	
	while(1){ /* find key according to student ID.*/
		long long int tempStudentId = studentId;
		while (tempStudentId > 0){
		
			digitSums += tempStudentId % 10;
			tempStudentId /= 10;
		}
		if(digitSums < 10){ /* continue until find the one digit number. */
			break;
		}
		studentId = digitSums;
		digitSums = 0;
	}
	
	myKey = digitSums;
	char tempChar;
	int isCommentFlag = 0;
	int charCount = -1;     /* due to structre of the sentence , I started from -1. */
	       
	while(scanf("%c" , &tempChar) != EOF){
		if(tempChar == ' '){                 /* print spaces and end of the lines.*/
			printf("%c" ,' ');
		}else if(tempChar == '\n'){
			printf("%c" ,'\n');
		}
		
		if(tempChar == '/'){ /* check if comment line start or not */
			char commentCh;
			scanf("%c" , &commentCh);
			if(commentCh == '*'){
				isCommentFlag = 1;
			}
		}else if(tempChar == '*'){ /* check if comment line finish or not */
			char commentCh2;
			scanf("%c" , &commentCh2);
			if(commentCh2 == '/'){
				printf("@ ");
				numberToChar(charCount , myKey);
				isCommentFlag = 0;
			}
		}
		
		if(isCommentFlag == 0){
			int i=0;
			for(i ; i <= 61 ; i++){
				int value = i + myKey;
				if(alphabet[i] == tempChar && tempChar != '*'){
					printf("%c" , alphabet[value % 61]);
				}
			}	 
		}else{
			if(tempChar != ' '){
				charCount += 1;
			}
			
			
		}
		
		
	}
	return 0;
}
