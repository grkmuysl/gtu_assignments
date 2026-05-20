#include <stdio.h>
/*print titles*/
void readTheTitle(FILE *file_name , int order){
    char karakter;
    printf("Title of %d. " , order);
    while((karakter = fgetc(file_name)) != '\n'){
        printf("%c", karakter);
    }
    printf("\n");
}
/* print news*/
void readTheNew1(){ /* tekrar tekrar okunabilmesi icin hepsini ayri ayri okutuyorum.*/
    FILE* file1;
    file1 = fopen("//home//gorkem//Desktop//news//1.txt" , "r");
    char karakter;
    while((karakter = fgetc(file1)) != EOF){
        printf("%c" , karakter);
    }
    fclose(file1);
}
void readTheNew2(){ 
    FILE* file2;
    file2 = fopen("//home//gorkem//Desktop//news//2.txt" , "r");
    char karakter;
    while((karakter = fgetc(file2)) != EOF){
        printf("%c" , karakter);
    }
    fclose(file2);
}
void readTheNew3(){ 
    FILE* file3;
    file3 = fopen("//home//gorkem//Desktop//news//3.txt" , "r");
    char karakter;
    while((karakter = fgetc(file3)) != EOF){
        printf("%c" , karakter);
    }
    fclose(file3);
}
void readTheNew4(){ 
    FILE* file4;
    file4 = fopen("//home//gorkem//Desktop//news//4.txt" , "r");
    char karakter;
    while((karakter = fgetc(file4)) != EOF){
        printf("%c" , karakter);
    }
    printf("\n");
    fclose(file4);
}
int isNewsAdded(FILE *readed_news_list , int order_of_list){ /*okunanlar listesine eklenip eklenmediginin kontrolu */
    int numara;
    while (fscanf(readed_news_list, "%d;", &numara) == 1) {

        if(numara == order_of_list ){
            return 1;
        }
    }
    return 0;
}

void readedNews(FILE *readed_news_list){ /* okunanlar listesinin ekrana yazdirilmasi*/
    int numara;
    while (fscanf(readed_news_list, "%d;", &numara) == 1) {
        printf("%d. new is readed.\n" , numara);
    }
}
/* find magic numbers for each news.*/
int findMagicNumberFor_1(){
	int totalOfMagicNumbers = 0;
	FILE* file1;
	file1 = fopen("//home//gorkem//Desktop//news//1.txt" , "r");
	char karakter , tempChar;
	while((karakter = fgetc(file1)) != EOF){
		if(karakter == '#'){
			int tempNum = fgetc(file1) - '0'; /* turn to num*/
			totalOfMagicNumbers += ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 ) * ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 );
		}
	}
	fclose(file1);
	return totalOfMagicNumbers;
}
int findMagicNumberFor_2(){
	int totalOfMagicNumbers = 0;
	FILE* file2;
	file2 = fopen("//home//gorkem//Desktop//news//2.txt" , "r");
	char karakter , tempChar;
	while((karakter = fgetc(file2)) != EOF){
		if(karakter == '#'){
			int tempNum = fgetc(file2) - '0'; /* turn to num*/
			totalOfMagicNumbers += ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 ) * ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 );
		}
	}
	fclose(file2);
	return totalOfMagicNumbers;
}
int findMagicNumberFor_3(){
	int totalOfMagicNumbers = 0;
	FILE* file3;
	file3 = fopen("//home//gorkem//Desktop//news//3.txt" , "r");
	char karakter , tempChar;
	while((karakter = fgetc(file3)) != EOF){
		if(karakter == '#'){
			int tempNum = fgetc(file3) - '0'; /* turn to num*/
			totalOfMagicNumbers += ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 ) * ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 );
		}
	}
	fclose(file3);
	return totalOfMagicNumbers;
}
int findMagicNumberFor_4(){
	int totalOfMagicNumbers = 0;
	FILE* file4;
	file4 = fopen("//home//gorkem//Desktop//news//4.txt" , "r");
	char karakter , tempChar;
	while((karakter = fgetc(file4)) != EOF){
		if(karakter == '#'){
			int tempNum = fgetc(file4) - '0'; /* turn to num*/
			totalOfMagicNumbers += ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 ) * ((tempNum*tempNum*tempNum) - (tempNum*tempNum) + 2 );
		}
	}
	fclose(file4);
	return totalOfMagicNumbers;
}

/*print menu*/
void menu(){
    /* declare and open files*/
    FILE* file1;
    FILE* file2;
    FILE* file3;
    FILE* file4;

    file1 = fopen("//home//gorkem//Desktop//news//1.txt" , "r");
    file2 = fopen("//home//gorkem//Desktop//news//2.txt" , "r");
    file3 = fopen("//home//gorkem//Desktop//news//3.txt" , "r");
    file4 = fopen("//home//gorkem//Desktop//news//4.txt" , "r");

    printf("**********Daily Press**********\n");
    printf("Today's news are listed for you :\n");

    readTheTitle(file1 , 1);
    readTheTitle(file2 , 2);
    readTheTitle(file3 , 3);
    readTheTitle(file4 , 4);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    int countOfReadedNews = 0;
    char option , isContinue = 'y';
    FILE *readed_news;
    while(isContinue == 'y'){
        printf("\nWhat do you want to do?\n");
        printf("a.Read a new\n");
        printf("b.List the readed news\n");
        printf("c.Get decrypted information from the news\n");
        scanf(" %c" , &option);
        switch(option){
            case 'a':
                printf("Which news do you want to read? Please press 1,2,3 or 4:\n");

                int order_of_news;
                scanf(" %d" , &order_of_news);
                fflush(stdin);
                if(order_of_news == 1){
                    readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r"); 
                    int isAdded = isNewsAdded(readed_news , 1);
                    fclose(readed_news);
                    if(isAdded != 1){ /* okunanlar listesinde yoksa: once oku sonra listeye id ile birlikte noktali virgul ekle.*/
                        readTheNew1();
                        countOfReadedNews++;
                        readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "a");
                        fprintf(readed_news , "%d", 1);
                        fprintf(readed_news , "%c", ';');
                        fclose(readed_news);
                    }else{
                        printf("This new is readed. Do you want to read again? Yes(1) / No(0):"); /*okunanlar listesine ekli ise okumadan once sor.*/
                        int choice;
                        scanf("%d" , &choice);
                        fflush(stdin);
                        if(choice == 1){
                            readTheNew1();
                        }
                    }
                }else if(order_of_news == 2){
                    readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r");
                    int isAdded = isNewsAdded(readed_news , 2);
                    fclose(readed_news);
                    if(isAdded != 1){
                        readTheNew2();
                        countOfReadedNews++;
                        readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "a");
                        fprintf(readed_news , "%d", 2);
                        fprintf(readed_news , "%c", ';');
                        fclose(readed_news);
                    }else{
                        printf("This new is readed. Do you want to read again? Yes(1) / No(0):");
                        int choice;
                        scanf("%d" , &choice);
                        fflush(stdin);
                        if(choice == 1){
                            readTheNew2();
                        }
                    }
                }else if(order_of_news == 3){
                    readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r");
                    int isAdded = isNewsAdded(readed_news , 3);
                    fclose(readed_news);
                    if(isAdded != 1){
                        readTheNew3();
                        countOfReadedNews++;
                        readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "a");
                        fprintf(readed_news , "%d", 3);
                        fprintf(readed_news , "%c", ';');
                        fclose(readed_news);
                    }else{
                        printf("This new is readed. Do you want to read again? Yes(1) / No(0):");
                        int choice;
                        scanf(" %d" , &choice);
                        fflush(stdin);
                        if(choice == 1){
                            readTheNew3();
                        }
                    }
                }else if(order_of_news == 4){
                    readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r");
                    int isAdded = isNewsAdded(readed_news , 4);
                    fclose(readed_news);
                    if(isAdded != 1){
                        readTheNew4();
                        countOfReadedNews++;
                        readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "a");
                        fprintf(readed_news , "%d", 4);
                        fprintf(readed_news , "%c", ';');
                        fclose(readed_news);
                    }else{
                        printf("This new is readed. Do you want to read again? Yes(1) / No(0):");
                        int choice;
                        scanf(" %d" , &choice);
                        fflush(stdin);
                        if(choice == 1){
                            readTheNew4();
                        }
                    }

                }else{
                    printf("Please enter a valid input! \n");
                }
                printf("Do you want to continue? Yes(y)/No(n):");
                scanf(" %c", &isContinue);
                fflush(stdin);
                break;
            case 'b':
            	readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r"); /* dosya bos mu degil mi kontrol et.*/
            	
            	if(fgetc(readed_news) == EOF){
            		printf("You haven't read any news yet!\n");
            		fclose(readed_news);
            	}else{
            		fclose(readed_news);
                    	readed_news = fopen("//home//gorkem//Desktop//readed_news.txt" , "r");
                   	 readedNews(readed_news);
                    	fclose(readed_news);
                }
	
                printf("Do you want to continue? Yes(y)/No(n):");
                scanf(" %c", &isContinue);
                fflush(stdin);
            break;

            case 'c':
		printf("Which news would you like to decrpyte?: ");
		int choice;
                scanf(" %d" , &choice);
                fflush(stdin);
                if(choice == 1){
                	readTheNew1();
                	int secretNumber = findMagicNumberFor_1();
                	printf("\nFirst Experiment Key = %d \n",secretNumber);
                }else if(choice == 2){
                	readTheNew2();
                	int secretNumber = findMagicNumberFor_2();
                	printf("\nSecond Experiment Key = %d \n",secretNumber);
                }else if(choice == 3){
                	readTheNew3();
                	int secretNumber = findMagicNumberFor_3();
                	printf("\nThird Experiment Key = %d \n",secretNumber);
                }else if(choice == 4){
                	readTheNew4();
                	int secretNumber = findMagicNumberFor_4();
                	printf("\nFourth Experiment Key = %d \n",secretNumber);
                }else{
                	printf("Enter a valid number! \n");
                }
                
                printf("Do you want to continue? Yes(y)/No(n):");
                scanf(" %c", &isContinue);
                fflush(stdin);
            break;
        }
    }
    printf("Good Bye! \n");
    fclose(readed_news);
}
int main(){
    menu();
    return 0;
}
