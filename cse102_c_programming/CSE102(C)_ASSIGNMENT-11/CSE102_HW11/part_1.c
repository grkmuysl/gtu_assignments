#include <stdio.h>

int numPathsHome(int street, int avenue) {

    if (street == 1 && avenue == 1) { /* hedefe ulasildi mi kontrol et ulasildiysa o yol gecerlidir. */
        return 1;
    }

    if (street < 1 || avenue < 1) {  /* haritanin disina cikilan yollar gecersiz yoldur 0 sayilir. */
        return 0;
    }

    /* sola ve asagi yondeki her hareketi return et gecerli yol ise +1 ekler. */
    return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
}

int main() {

    int initial_street, initial_avenue;
    printf("Enter the street number: ");
    scanf("%d" , &initial_street);
    if(initial_street < 1 || initial_street > 5){
    	printf("Please enter a valid number!\n");
  	return 0;
    }
    printf("Street: %d" , initial_street);
    printf("\nEnter the avenue number: ");
    scanf("%d" , &initial_avenue);
    if(initial_avenue < 1 || initial_avenue > 5){
    	printf("Please enter a valid number!\n");
  	return 0;
    }
    printf("Avenue: %d\n" , initial_avenue);

    int totalPaths = numPathsHome(initial_street, initial_avenue);

    printf("Number of optimal paths to take back home: %d\n", totalPaths);

    return 0;
}
