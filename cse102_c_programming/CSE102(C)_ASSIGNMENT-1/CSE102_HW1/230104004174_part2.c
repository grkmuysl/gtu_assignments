#include <stdio.h>
int main(){

	char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	
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
	
	while(scanf("%c" , &tempChar) != EOF){
		int i=0;
		if(tempChar == ' '){
			printf("%c" ,' ');
		}else if(tempChar == '\n'){
			printf("%c" ,'\n');
		}
		if(tempChar == '@'){ /* check if comment tine start or not and decrypted it. */
			printf("/*There is a ");
			char tempCharForCommentLine;
			for(int k = 0 ; k<3 ; k++){
				scanf("%c" , &tempCharForCommentLine);
				int i = 0;
				for(i ; i <= 61 ; i++){
				int value = i - myKey;
				if(value < 0){
					value += 61;
				}
				if(alphabet[i] == tempCharForCommentLine){
					printf("%c" , alphabet[value]);
				}
			}
			
			
		}
			printf(" characters are as a comment.*/");
		}
		for(i ; i <= 61 ; i++){ /* decrypted other chars. */
			int value = i - myKey;
			if(value < 0){
				value += 61;
			}
			if(alphabet[i] == tempChar){
				printf("%c" , alphabet[value]);
			}
		}
		
	}
	return 0;
}
