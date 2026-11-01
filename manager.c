#include <stdio.h>
#include <string.h>


typedef struct{
    char nombre[30];
    int bonus;
    int vigencia;
} Cancion;

typedef struct{
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    Cancion *cancion;
} Idol;

typedef struct{
    char nombre[30];
    Idol miembro[4];
    int n;
    Idol *lider;
}Grupo;

void mostrar(const Idol *i){ printf("Nombre: %s\n", i->nombre);
    printf("Popularidad: %d\n", i->popularidad); printf("Energia: %d / %d\n", i->energia, i->energia_max); printf("Fans: %d\n", i->fans);

    if (i->cancion != NULL){
        printf("Cancion: %s (Bonus: %d, Vigencia: %d\n", i->cancion->nombre, i->cancion->bonus, i->cancion->vigencia);
    } else {
        printf("Cancion: Ninguna(NULL)\n");
    }
    printf("-------------------------------------------------------\n");
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

void asignar_cancion(Idol *i, Cancion *c){
    if (i == NULL){
        return;
    }
    i->cancion = c;
}

int popularidad_total(const Idol *i){
    if (i == NULL) return 0;

    if (i->cancion != NULL && i->cancion->vigencia > 0){
       return i->popularidad + i->cancion->bonus;
    }

    return i->popularidad;
}

int cambiar_lider(Grupo *g, Idol *nueva){
    if (g == NULL || nueva == NULL){
        return 0;
    }

    for (int i = 0; i<g->n; i++){
        if (&g->miembro[i] == nueva){
            g->lider = nueva;
            return 1;
        }
    }
    return 0;
}

void mostrar_grupo(const Grupo *g){
     if(g == NULL) {
        return;
     }
     printf("Grupo: %s (total integrantes: %d)\n", g->nombre, g->n);
     if (g->lider !=NULL){
         printf("Lider actual: %s\n", g->lider->nombre);
     } else {
         printf("Lider actual: Ninguna\n");
     }
     printf("-------------------------------------------\n");

     const Idol *p = g->miembro;
     const Idol *limite = g->miembro + g->n;

     while (p < limite){
         mostrar(p);
         p++;
     }
}

int contar_activas(const Grupo  *g){
    if (g == NULL || g->n <= 0){
        return 0;
    }
    int activas = 0;
    const Idol *p = g->miembro;
    const Idol *limite = g->miembro + g->n;

    while (p < limite){
        if (esta_activa(p)){
            activas++;
        }
        p++;
    }
    return activas;
}

Idol *idol_mas_cansada(Grupo *g){
    if (g == NULL || g->n <= 0){
        return NULL;
    }

    Idol *mas_cansada = &g->miembro[0];
    Idol *p = g->miembro + 1;
    Idol *limite = g->miembro + g->n;

    while (p < limite) {
        if (p->energia < mas_cansada->energia){
            mas_cansada = p;
        }
        p++;
    }
    return mas_cansada;
}

int main(){

    Cancion disco[2] = {
        {"Starlight", 10, 3},
        {"Nova", 5,6}
    };

    Grupo lumina = {
        "Lumina",
        {
            {"jennie", 50, 100, 100, 12000,NULL},
            {"rose", 45, 100, 100, 10000,NULL},
            {"lisa", 55, 100, 100, 15000,NULL}
        },
        3,
        NULL
    };

    printf("Pruebas de idol_mas_cansada\n");


    Idol *cansada = idol_mas_cansada(&lumina);


    if (cansada != NULL) {
        printf("La integrante mas cansada es: %s con %d de energia.\n\n", cansada->nombre, cansada->energia);
        printf("Haciendo descansar a %s...\n", cansada->nombre);
        descansar(cansada);
        printf("Nueva energia de %s despues de descansar: %d\n", cansada->nombre, cansada->energia);
    }
    Idol *nulo = idol_mas_cansada(NULL);
    if (nulo == NULL) {
        printf("\nPrueba de seguridad idol_mas_cansada(NULL) superada con exito (retorno NULL).\n");
    }
return 0;
}
