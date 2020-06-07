/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#include "carros.h"
#include "utils.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>


int num_carros(char *nomeficheiro){
    FILE *f= fopen(nomeficheiro, "rt");
    char c;
    int contador=0;
    int nr=0;
    
    if(f==NULL){
        fprintf(f, "Erro na abertura do ficheiro: %s\n", nomeficheiro);
        return 0;
    }
    
    while ((c = fgetc(f)) != EOF)
        if (c == '\n')
            contador++;

    if (c != '\n' && contador != 0)
        contador++;

    fclose(f);
    contador++;
    nr=contador/2;
    
    return nr;
}



carros* inicializa_carros(char *nomeficheiro, int total){
    FILE *f= fopen(nomeficheiro, "rt");
    carros *aux;
    int i;
    
    if(f==NULL){
        fprintf(f, "Erro na abertura do ficheiro: %s\n", nomeficheiro);
        return 0;
    }
    
    aux = malloc(sizeof(carros) * (total));
    if(aux==NULL){
        printf("Erro na alocação de memoria.\n");
        fclose(f);
        return 0;
    }
    
    for(int i=0; i<total; i++){
       if ((fscanf(f, "%d %d %d %d ", &aux[i].id_carro,
                &aux[i].potencia_carro, &aux[i].avariado, &aux[i].disponibilidade_carro ))!=4 ) {
                    fprintf(stderr, "Erro na leitura do ficheiro.\n");
                    fclose(f);
                    return NULL;
        }
    }
    listar_carros(aux,total);
    fclose(f);
    return aux;
}


void listar_carros(carros *p, int total){
    int i;
    
    if(p==NULL){
        printf("Nao existem carros!\n");
        return;
    }
    
    for(i=0; i<total; i++){
        printf("CARRO %3d: \n\tPotencia: %d \n\tAvariado: %d \n\tDisponibilidade:  %d \n\n",
                (p+i)->id_carro, (p+i)->potencia_carro, (p+i)->avariado, (p+i)->disponibilidade_carro);
    }
}


void procura_carro(carros *p, int total){
     
    int i, flag=0;
    int id;
    
    if(p==NULL){
        printf("Nao existem carros!\n");
        return;
    }
    
    printf("ID do carro: ");
    scanf(" %d", &id);
    
    for(i=0; i<total; i++){
 
        if(id==(p+i)->id_carro){
            printf("\nCARRO %3d: \n\tPotencia: %d \n\tAvariado: %d \n\tDisponibilidade:  %d \n\n",
                (p+i)->id_carro, (p+i)->potencia_carro, (p+i)->avariado, (p+i)->disponibilidade_carro);
            flag=1;
        }
        
    }
    
    if(flag==0){
        printf("Esse carro nao existe!\n");
    } 
}



carros* atualiza_carros_fim_corrida(pequipas eq, carros *c, int total_c){
    
    int i;
    pequipas aux;
    aux=eq;
    
    for(i=0; i<total_c;i++){
        (c+i)->avariado = (c+i)->avariado - 1;
        if((c+i)->avariado < 0){
           (c+i)->avariado = 0;
        }
    }
    
    for(aux=eq; aux; aux=aux->prox){
        for(i=0; i<total_c;i++){
            if(aux->id_carro == (c+i)->id_carro){
                 if(aux->ocorreu_acidente == COM_ACIDENTE){
                    (c+i)->avariado = (c+i)->avariado + 1;
                 }
            }
        }
    }
    
    
    for(i=0; i<total_c; i++){
        (c+i)->disponibilidade_carro= LIVRE;
    }
    
    return c;
}

void gravar_vetorC(carros *c, char *nomefich, int total) {
    FILE *f = fopen(nomefich, "wt");
    int i;

    if (!f) {
        fprintf(stderr, "Erro a abrir o ficheiro %s", nomefich);
        return;
    }
    
    printf("Total carros: %d", total);
    
    
    for(int i=0; i<total; i++){
        fprintf(f, "%d %d %d %d",(c + i)->id_carro,(c + i)->potencia_carro,
               (c + i)->avariado, (c + i)->disponibilidade_carro);
        if(i!=total){
            fprintf(f, "\n");
       }
    }

    fclose(f);
}