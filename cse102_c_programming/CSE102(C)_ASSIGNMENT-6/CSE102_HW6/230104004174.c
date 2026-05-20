#include <stdio.h>

int find_size_of_array(int number_array[]){ /* find size of array (exclude -1)*/
    int array_size = 0;
    while (number_array[array_size] != -1) {
        array_size++;
    }
    return array_size;
}

int count_of_number(int number , int number_array[]){ /*find how many times the entered number is in the array.  */
    int count_of_number = 0;
    for(int i = 0; number_array[i] != -1 ; i++){
        if(number_array[i] == number){
            count_of_number++;
        }
    }
    return count_of_number;
}

int max_repetition(int number_array[]){ /* find the max repetition number in the array*/
    int temp_num , max_repetition = 0 ;

    for(int i = 0; number_array[i] != -1 ; i++){
        int count_of_repetations = 0; 
        temp_num = number_array[i];
        for(int j = 0; number_array[j] != -1 ; j++){
            if(temp_num == number_array[j]){
                count_of_repetations++; /* increase by 1 for each repetations */
            }
        }
        if(count_of_repetations >= max_repetition){
            max_repetition = count_of_repetations;
        }
    }

    return max_repetition;
}

void display_histogram(int max_repetition_number ,int interval1 , int interval2 , int number_array[]){ /* display thee histogram */
    for (int line = max_repetition_number; line > 0; line--) { /* en cok tekrar eden sayi en ust line olacak sekilde line i yukaridan asagi azaltiyorum */
                for(int k = interval1  ; k <= interval2 ; k++){
                    if(count_of_number(k , number_array) < line){ /* eslesen sayilar icin '*' bastiriyorum eslesmeyenleri bos birakiyorum */
                        printf(" ");
                    }else{
                        printf("*");
                    }
                }
        printf("\n");
        }
}

void calculation_of_average(int number_array[] , int size_of_array , int interval1, int interval2){ /* calculation of average in the array*/
    float total_of_numbers = 0, average_of_numbers;
    int size_of_numbers = 0; /* aralik icerisindeki sayilari sayip ortalamayı ona gore buluyorum*/
    for(int i= 0; i < size_of_array  ; i++){
    	if(number_array[i] >= interval1 && number_array[i] <= interval2){
    		total_of_numbers += number_array[i];
    	   	size_of_numbers += 1;
    	}   
    }
    average_of_numbers = total_of_numbers / size_of_numbers;
    printf("Average: %.2f\n" , average_of_numbers);

}

void sort_the_numbers(int number_array[] , int size_of_array){  /* sort the numbers from smallest to largest */
    int tempNum;
    for (int i = 0; i < size_of_array - 1; i++) {
        for (int j = 0; j < size_of_array - i - 1; j++) {
            if (number_array[j] > number_array[j + 1]) {
                tempNum = number_array[j];
                number_array[j] = number_array[j + 1];
                number_array[j + 1] = tempNum;
            }
        }
    }
}

void calculation_of_median(int number_array[] , int size_of_array){ /* find the median in the array*/
    sort_the_numbers(number_array , size_of_array);
    if(size_of_array % 2 != 0){ /* if size is odd then print it */
        printf("\nMedian: %d\n" , number_array[(size_of_array - 1) / 2]);
    }

}

void calculation_of_mode(int number_array[] , int size_of_array , int max_repetition){ /* find the mode of the array*/
    sort_the_numbers(number_array , size_of_array); /* diziyi sirala*/
    printf("Mode: ");
    int temp_num , repetition_count = 0 ;

    for(int i = 0; i < size_of_array ; i++){
        int count_of_repetations = 0 , isMode = 0;
        temp_num = number_array[i];
        for(int j = 0; number_array[j] != -1 ; j++){
            if(temp_num == number_array[j]){
                count_of_repetations++;
                if(count_of_repetations >= max_repetition){
                    isMode = 1;

                }
            }
        }
        if(isMode == 1 && (number_array[i] == number_array[i+ max_repetition - 1])){ /* sayilari ekrana birer defa bastirmak icin boyle bir algoritma kurdum*/
            printf("%d " , number_array[i]); /* i sayisi yazdirilacak sayinin indexini belirtir */
        }
    }
    printf("\n");
}

int main() {
    int number_array[] = {3, 8, 9, 9, 5, 2, 4, 7, 4, 8, 9, 10, 2, 4, 5, -1};
    int max_repetition_number = max_repetition(number_array); /* en cok tekrar eden sayi kac kere tekrar etmis*/
    int interval1  , interval2;
    int size_of_array = find_size_of_array(number_array);
    printf("Enter first interval:");
    scanf("%d" ,&interval1);
    printf("Enter second interval:");
    scanf("%d" , &interval2);
    display_histogram(max_repetition_number,interval1,interval2,number_array);

    /*part-2 */
    int choice;
    printf("Would you like to add new numbers? (Press 1 for yes, Press 0 for no): ");
    scanf("%d" , &choice);
    if(choice == 1){
        printf("Enter the numbers: ");
        int eklenecek_sayilar[5] , new_number_array[size_of_array + 5] ,toplam_eklenen_sayi = 0;
        for(int i = 0 ; i < 5 ; i++){
            int eklenecek_sayi;
            scanf("%d" , &eklenecek_sayi);
            if(eklenecek_sayi != -1){
                eklenecek_sayilar[i] = eklenecek_sayi; /* eklenen sayilari yeni bir arrayda tut*/
                toplam_eklenen_sayi += 1;
            }else{
                break;
            }
        }
        for(int k = 0 ; k < toplam_eklenen_sayi; k++){ /* eklenecek sayilari yeni sayi kumesine ekle */
            new_number_array[k] = eklenecek_sayilar[k];
        }
        for(int j = 0; j <= size_of_array ; j++){ /* basta kurdugumuz sayilar kumesini new_number_array'in sonuna ekle. */
            new_number_array[toplam_eklenen_sayi + j] = number_array[j];
        }
        int new_max_repetition_number = max_repetition(new_number_array);

        display_histogram(new_max_repetition_number,interval1,interval2,new_number_array);
        calculation_of_average(new_number_array , size_of_array + toplam_eklenen_sayi , interval1, interval2);
        calculation_of_median(new_number_array , size_of_array + toplam_eklenen_sayi);
        calculation_of_mode(new_number_array , size_of_array + toplam_eklenen_sayi , new_max_repetition_number);
    }else{

        calculation_of_average(number_array , size_of_array , interval1 , interval2);
        calculation_of_median(number_array , size_of_array);
        calculation_of_mode(number_array , size_of_array , max_repetition_number);
    }
    return 0;
}
