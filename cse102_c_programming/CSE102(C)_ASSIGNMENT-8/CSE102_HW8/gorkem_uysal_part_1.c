#include <stdio.h>
#include <string.h>

#define MAX_ROWS 23
#define MAX_COLUMNS 5
#define MAX_LENGTH 20

int compare_inputs(char input1[], char input2[]){ /* input 1 buyukse -1, input 2 buyukse 1, esitlerse 0 doner.*/
    int result = strcmp(input1, input2);
    return result;
}

void sort_people_by_age(char members[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH + 1], int row_count, int isPrint){ /* insanlari kucukten buyuge dogru yasa gore sirala

    /*bubbleSort*/
    int i,j;
    for(i = 0; i <= row_count - 1; i++){
        for(j = 0; j <= row_count - i - 1; j++){
            if(compare_inputs(members[j][2], members[j+1][2]) > 0){ 
                char temp[MAX_LENGTH + 1];
                /* isim swap*/
                strcpy(temp, members[j][0]);
                strcpy(members[j][0], members[j + 1][0]);
                strcpy(members[j + 1][0], temp);
                /* surname swap */
                strcpy(temp, members[j][1]);
                strcpy(members[j][1], members[j + 1][1]);
                strcpy(members[j + 1][1], temp);
                /* age swap*/
                strcpy(temp, members[j][2]);
                strcpy(members[j][2], members[j + 1][2]);
                strcpy(members[j + 1][2], temp);
                /* branch1 swap */
                strcpy(temp, members[j][3]);
                strcpy(members[j][3], members[j + 1][3]);
                strcpy(members[j + 1][3], temp);
                /* branch2 swap */
                strcpy(temp, members[j][4]);
                strcpy(members[j][4], members[j + 1][4]);
                strcpy(members[j + 1][4], temp);
            }
        }

    }
    
    
    if(isPrint == 1){ /* yazdirilsin mi == 1 ise yazdir */
        char nameTitle[] = "Name", surnameTitle[] = "Surname", ageTitle[] = "Age", branch1Title[]="Branch1", branch2Title[]="Branch2";
        printf("%20s %20s %15s %20s %20s\n \n",nameTitle,surnameTitle,ageTitle,branch1Title,branch2Title);
        int i,j;
        for(i = 0; i <= row_count; i++) {
        	for(j = 0; j < 5; j++){
        		printf("%15s"," ");
        		printf("%s", members[i][j]);
        	
        	}
            printf("\n \n");

        }
    }


}
void sort_people_by_branch (char members[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH + 1], int row_count){ /* branchlere gore alfabetik sekilde sirala*/

    sort_people_by_age(members, row_count, 0); /* yasa gore siraladim ama yazdirmadim.*/

    /*bubbleSort*/
    int i,j;
    for(i = 0; i <= row_count - 1; i++){
        for(j = 0; j <= row_count - i - 1; j++){
            if(compare_inputs(members[j][3], members[j+1][3])  > 0){ /* branch1 alfabetik anlamda daha buyuk ise */
                char temp[MAX_LENGTH + 1];
                /* isim swap*/
                strcpy(temp, members[j][0]);
                strcpy(members[j][0], members[j + 1][0]);
                strcpy(members[j + 1][0], temp);
                /* surname swap */
                strcpy(temp, members[j][1]);
                strcpy(members[j][1], members[j + 1][1]);
                strcpy(members[j + 1][1], temp);
                /* age swap*/
                strcpy(temp, members[j][2]);
                strcpy(members[j][2], members[j + 1][2]);
                strcpy(members[j + 1][2], temp);
                /* branch1 swap */
                strcpy(temp, members[j][3]);
                strcpy(members[j][3], members[j + 1][3]);
                strcpy(members[j + 1][3], temp);
                /* branch2 swap */
                strcpy(temp, members[j][4]);
                strcpy(members[j][4], members[j + 1][4]);
                strcpy(members[j + 1][4], temp);
            }
        }

    }
    /* branch1ler esit ise branch 2 leri karsilastir */
    for(i = 0; i <= row_count - 1; i++){
        for(j = 0; j <= row_count - i - 1; j++){
        	if(compare_inputs(members[j][3], members[j+1][3]) == 0){
        		if(compare_inputs(members[j][4], members[j+1][4])  > 0){ 
		        char temp[MAX_LENGTH + 1];
		        /* isim swap*/
		        strcpy(temp, members[j][0]);
		        strcpy(members[j][0], members[j + 1][0]);
		        strcpy(members[j + 1][0], temp);
		        /* surname swap */
		        strcpy(temp, members[j][1]);
		        strcpy(members[j][1], members[j + 1][1]);
		        strcpy(members[j + 1][1], temp);
		        /* age swap*/
		        strcpy(temp, members[j][2]);
		        strcpy(members[j][2], members[j + 1][2]);
		        strcpy(members[j + 1][2], temp);
		        /* branch1 swap */
		        strcpy(temp, members[j][3]);
		        strcpy(members[j][3], members[j + 1][3]);
		        strcpy(members[j + 1][3], temp);
		        /* branch2 swap */
		        strcpy(temp, members[j][4]);
		        strcpy(members[j][4], members[j + 1][4]);
		        strcpy(members[j + 1][4], temp);
		    }
        	}
            
        }

    }
    
        char nameTitle[] = "Name", surnameTitle[] = "Surname", ageTitle[] = "Age", branch1Title[]="Branch1", branch2Title[]="Branch2";
        printf("%20s %20s %15s %20s %20s\n \n",nameTitle,surnameTitle,ageTitle,branch1Title,branch2Title);

        for(i = 0; i <= row_count; i++) {
        	for(j = 0; j < 5; j++){
        		
        		printf("%15s"," ");
        		printf("%s", members[i][j]);
        	
        	}
            printf("\n \n");

        }
}

void filter_people_by_branch(char members[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH + 1], int row_count){ /* icerisinde searchBranch stringi bulunanlari filtrele.*/
 
    int i ,j;
    char searchBranch[] = "SCIENCE";
    char nameTitle[] = "Name", surnameTitle[] = "Surname", ageTitle[] = "Age", branch1Title[]="Branch1", branch2Title[]="Branch2";
    printf("%20s %20s %15s %20s %20s\n \n",nameTitle,surnameTitle,ageTitle,branch1Title,branch2Title);
        	
    for(i = 0; i <= row_count; i++){
        char* result_br_1 = strstr(members[i][3], searchBranch); /*branch1 ve branch2 icerisinde "SCIENCE" bulunduruyor mu kontrol et */
        char* result_br_2 = strstr(members[i][4], searchBranch);
        
	
        if(result_br_1 != NULL || result_br_2 != NULL){ /*sonuc null degil ise bulunduruyordur */

			for(j = 0; j < 5; j++){
				printf("%15s"," ");
				printf("%s", members[i][j]);

		}
		   printf("\n \n");

        }
    
    }
}

void filter_people_by_profession(char members[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH + 1], int row_count){ /* tek uzmanligi computer science olan uyeleri filtrele.*/
    char searchText1[] = "COMPUTER SCIENCE";

    char nameTitle[] = "Name", surnameTitle[] = "Surname", ageTitle[] = "Age", branch1Title[]="Branch1", branch2Title[]="Branch2";
    printf("%20s %20s %15s %20s %20s\n \n",nameTitle,surnameTitle,ageTitle,branch1Title,branch2Title);

   int i ,j;
    for(i = 0; i <= row_count; i++){
        char* result_br_1_for_comp = strstr(members[i][3], searchText1); /*branch1 ve branch2 icerisinde COMPUTER SCIENCE bulunduruyor mu kontrol et */
        char* result_br_2_for_comp = strstr(members[i][4], searchText1);



        if(result_br_1_for_comp != NULL || result_br_1_for_comp != NULL){ /*cumputer science olanlar if bloguna girer girer */
            if(strlen(members[i][4]) == 0){ /* branch2 bos ise baska uzmanlik yoktur*/

			for(j = 0; j < 5; j++){
				printf("%15s"," ");
				printf("%s", members[i][j]);
			
			}
		    printf("\n \n");
            }

        }

    }
}

int read_the_file(FILE* myFile, int choice){ /* dosyayi okur ve members array'ine kaydeder. */

    char members[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH + 1];
    int row = 0, column = 0, okunan_harf = 0, virgulden_sonra = 0;
    char c;

    while((c = fgetc(myFile)) != EOF){
        if (c == '\n') {
            if(column == 3){
                strcpy(members[row][4], ""); /* 3. columnda satir atliyorsa branch 2 bos demek.*/
            }
            members[row][column][okunan_harf] = '\0';
            column = 0;
            okunan_harf = 0;
            row ++; /* bu islemle sonraki satirin basina gidiyorum */

        }else{
            if(c == ','){
            members[row][column][okunan_harf] = '\0'; /* her bir degerin String sonu oldugunu bildiriyorum */
            column++;
            okunan_harf = 0;
            virgulden_sonra = 1;
            }else if (virgulden_sonra == 1 && c == ' ') {
            /* bosluk karakterlerini atla */
            }else{
                members[row][column][okunan_harf] = c;
                okunan_harf ++;
                virgulden_sonra = 0;
            }
        }


    }
    members[row][column][okunan_harf] = '\0'; /* son kelime icin string sonlandirir */
    
    /* kullanicidan alinan secime gore islemler yapilir. */
    if(choice == 1){
        sort_people_by_age(members, row, 1);
    }else if(choice == 2){
        sort_people_by_branch(members, row);
    }else if(choice == 3){
        filter_people_by_branch(members,row );
    }else if(choice == 4){
        filter_people_by_profession(members, row);
    }

    return 0;
}

int main() {


    printf("******MENU******** \n");
    printf("1. Sort and display all individuals by age\n");
    printf("2. Sort and display individuals in the branch by age\n");
    printf("3. Show individuals with the branch 'SCIENCE \n");
    printf("4. Show computer scientists who are not mathematicians\n");
    printf("5. Exit\n");
    int choice;

    while(choice != 5){
            FILE* myFile = fopen("//home//gorkem//Desktop//input1.txt" , "r");
            if (myFile == NULL) {
                printf("Dosya acilamadi!\n");
                return 1;
            }
            printf("Choice: ");
            scanf(" %d", &choice);
             switch(choice){
                case 1:
                    read_the_file(myFile, choice);
                    fclose(myFile);
                    break;
                case 2:
                    read_the_file(myFile, choice);
                    fclose(myFile);
                    break;
                case 3:
                    read_the_file(myFile, choice);
                    fclose(myFile);
                    break;
                case 4:
                    read_the_file(myFile, choice);
                    fclose(myFile);
                    break;
                case 5:
                    return 0;
                    break;
                default:
                    printf("Please enter a valid choice!\n");
            }
    }
    return 0;
}
