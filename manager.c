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
    printf("---------------------------------------------------\n");
}

int limitar(int valor, int minimo, int maximo){
    if (valor < minimo){
	return minimo;
    }
    if (valor > maximo){
	return maximo;
    }
    return valor;
}

void ensayar(Idol *i){
    i->popularidad += 5;
    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}

void descansar(Idol *i){
    int recuperacion = 30;
    i->energia = limitar(i->energia + recuperacion, 0, i->energia_max);
}

int esta_activa(const Idol *i){
    if (i->energia > 0){
        return 1;
    }
    return 0;
}

void ensayos_por_valor(Idol i){
   i.popularidad +=5;
   i.energia = limitar(i.energia - 20, 0, i.energia_max);
   printf("Popularidad local: %d, Energia local: %d\n", i.popularidad, i.energia);
}


int colaboracion(Idol *a, Idol *b) {
    
    if (a == NULL || b == NULL || a == b) {
        return 0; 
    }

    a->popularidad += 10;
    a->energia = limitar(a->energia - 15, 0, a->energia_max);

    b->popularidad += 10;
    b->energia = limitar(b->energia - 15, 0, b->energia_max);

    printf("¡Colaboracion exitosa entre %s y %s!\n", a->nombre, b->nombre);
    return 1;
}

int main(){
    Idol jennie = {"jennie", 50, 100, 100, 12000};
    Idol rose = {"rose", 45, 100, 100, 10000};

    printf("Idol registrada: %s\n", jennie.nombre);
    printf("Energia: %d / %d\n", jennie.energia, jennie.energia_max);

    Idol *p = &jennie;

    printf("1.Usando jennie.fans: %d\n", jennie.fans);
    printf("2.Usando (*p).fans: %d\n", (*p).fans);
    printf("3.usando p->fans: %d\n\n", p->fans);

    printf("Direccion guardada en p: %p\n", (void *)p);
    printf("Direccion de &jennie:     %p\n", (void *)&jennie);

    mostrar(&jennie);
    mostrar(&rose);

    printf("limitar(-5, 0, 100)  -> Resultado: %d (Debe ser 0)\n", limitar(-5, 0, 100));
    printf("limitar(150, 0, 100) -> Resultado: %d (Debe ser 100)\n", limitar(150, 0, 100));
    printf("limitar(40, 0, 100)  -> Resultado: %d (Debe ser 40)\n\n", limitar(40, 0, 100));

    printf("¿Esta activa al inicio? (1=Si, 0=No): %d\n",esta_activa(&jennie));

    for(int j = 1; j <= 5; j++){
       ensayar(&jennie);
    }

    printf("estado despues de 5 ensayos consecutivos:\n");
    mostrar(&jennie);

    printf("¿Esta activa con 0 de energia? (1=Si, 0=No): %d\n",esta_activa(&jennie));

    for(int j = 1; j <= 1; j++){
       descansar(&jennie);
    }

    printf("despues de 1 descanso consecutivo:\n");
    printf("¿Esta activa con energia > 0? (1=Si, 0=No): %d\n\n", esta_activa(&jennie));


    printf("Llamando a ensayar_por_valor(jennie):\n");
    ensayos_por_valor(jennie);
    printf("En el main despues de pasar por valor, la popularidad sigue siendo: %d (No cambio)\n\n", jennie.popularidad);

    printf("Llamando a ensayar(&jennie) con apuntador:\n");
    ensayar(&jennie);
    printf("En el main despues de pasar por apuntador, la popularidad cambio a: %d (Si cambio)\n\n", jennie.popularidad);


    printf("¿Sigue activa jennie? (1=Si, 0=No): %d\n",esta_activa(&jennie));


    printf("1.colaboracion(&jennie, &jennie)\n");
    int res1 = colaboracion(&jennie, &jennie);
    printf("Resultado obtenido (esperado 0): %d\n\n", res1);

    
    printf("2.colaboracion(NULL, &rose)\n");
    int res2 = colaboracion(NULL, &rose);
    printf("Resultado obtenido (esperado 0): %d\n\n", res2);

    
    printf("3.colaboracion(&jennie, &rose)\n");
    int res3 = colaboracion(&jennie, &rose);
    printf("Resultado obtenido (esperado 1): %d\n", res3);

    printf("\nEstado despues de la colaboracion valida:\n");
    mostrar(&jennie);
    mostrar(&rose);


Idol *turno = &jennie;
    Idol *otra = &rose;
    int contador_turnos = 1;

    
    while (esta_activa(turno) && esta_activa(otra)) {
        printf("Turno %d: A ensayar -> %s\n", contador_turnos, turno->nombre);
        
        
        ensayar(turno);

        
        Idol *temp = turno;
        turno = otra;
        otra = temp;

        contador_turnos++;
    }

    printf("\n--- Fin de la dinamica por turnos ---\n");
    
    if (esta_activa(&jennie)) {
        printf("¡%s conserva energia y gana la dinamica!\n", jennie.nombre);
    } else if (esta_activa(&rose)) {
        printf("¡%s conserva energia y gana la dinamica!\n", rose.nombre);
    } else {
        printf("Ambas se quedaron sin energia al mismo tiempo.\n");
    }

    printf("\nEstado final de las idols:\n");
    mostrar(&jennie);
    mostrar(&rose);
return 0;
}
