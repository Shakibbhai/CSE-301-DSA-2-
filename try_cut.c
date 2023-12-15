#include<stdio.h>

int cutting_rod(int *price, int l);
int max(int a, int b);
int l_size[105], price_length, cuter[100];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int cutting_rod(int *price, int l) {
    if (l == 0) return 0;
    if (l_size[l] != -1) return l_size[l];
    int benefit = 0;
    for (int i = 1; i <= l && i <= price_length; i++) {
        if (l - i >= 0) {
            int temp = price[i - 1] + cutting_rod(price, l - i);
            if (temp > benefit) {
                benefit = temp;
                cuter[l] = i;
            }
        }
    }
    return l_size[l] = benefit;
}

int main(int argc, char *argv[]) {
    freopen("asus.txt","r",stdin);
    int l;
    //printf("enter the rod's length:");
    scanf("%d", &l);

    //printf("enter the price length:");
    scanf("%d", &price_length);

    printf("rod length is :%d\n",l);
     printf("price length is :%d\n",price_length);
    int price[price_length];

    for (int i = 0; i < price_length; i++) {
        scanf("%d", &price[i]);
    }

    for (int i = 0; i < 105; i++) {
        l_size[i] = -1;
    }

    int result = cutting_rod(price, l);
    printf("maximum revenue: %d\n", result);
    printf("optimal solution is:\n");

    while (l > 0) {
        printf("%d ", cuter[l]);
        l = l - cuter[l];
    }
    printf("\n");
    return 0;
}
