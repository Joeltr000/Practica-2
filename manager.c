#include <stdio.h>
#include <string.h>

typedef struct{
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
} Idol;

void mostrar(const Idol *i){
    printf("Nombre:      %s\n", i->nombre);
    printf("Popularidad: %d\n", i->popularidad);
    printf("Energia:     %d / %d\n", i->energia, i->energia_max);
    printf("Fans:        %d\n", i->fans);
}

int main(){
    Idol jennie = {"jennie", 50, 100, 100, 12000};

    printf("Idol registrada: %s\n", jennie.nombre);
    printf("Energia: %d / %d\n", jennie.energia, jennie.energia_max);

    Idol *p = &jennie;

    printf("1.Usando jennie.fans: %d\n", jennie.fans);
    printf("2.Usando (*p).fans: %d\n", (*p).fans);
    printf("3.usando p->fans: %d\n\n", p->fans);

    printf("Direccion guardada en p: %p\n", (void *)p);
    printf("Direccion de &jennie:     %p\n", (void *)&jennie);

    mostrar(&jennie);

return 0;
}
