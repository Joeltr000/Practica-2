#include <stdio.h>
#include <string.h>

typedef struct{
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans
} Idol;

int main(){
    Idol jennie = {"jennie", 50, 100, 100, 12000};

    printf("Idol registrada: %s\n" jennie.nombre);
    printf("Energia: %d / %d\n", jennie,energia, jennie.energia_max);
return 0;
}
