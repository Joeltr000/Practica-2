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

void dar_concierto(Grupo *g){
    if (g == NULL){
        return;
    }
    printf("\nEl grupo %s esta dando un concierto\n", g->nombre);

    Idol *p = g->miembro;
    Idol *limite = g->miembro + g->n;

    while (p < limite){
        if (esta_activa(p)){
            int fans_ganados = popularidad_total(p) * 10;
            p->fans += fans_ganados;

            p->energia = limitar(p->energia -25, 0, p->energia_max);

            printf("-> %s participo en el concierto: gano %d fans y gasto energia.\n", p->nombre, fans_ganados);

            if (p->cancion != NULL && p->cancion->vigencia > 0) {
                p->cancion->vigencia--;
                printf("    [Canción '%s' gastó 1 presentación. Vigencia restante: %d]\n", p->cancion->nombre, p->cancion->vigencia);

                if (p->cancion->vigencia == 0) {
                    printf("    ¡ATENCIÓN! La canción '%s' ha llegado a 0 de vigencia y ya no otorga bono.\n", p->cancion->nombre);
                }
            }
        } else {
            printf(" -> %s no pudo participar porque no está activa (energía en 0).\n", p->nombre);
        }
        p++;
    }
    printf("-----------------------------------------------------------\n\n");
}
int main(){

    Cancion disco[2] = {
        {"Starlight", 10, 2}
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

    asignar_cancion(&lumina.miembro[0], &disco[0]);
    asignar_cancion(&lumina.miembro[1], &disco[0]);
    cambiar_lider(&lumina, &lumina.miembro[0]);

    printf("Pruebas de dar conciertos\n");

    dar_concierto(&lumina);


    dar_concierto(&lumina);

    dar_concierto(&lumina);

    return 0;
}



