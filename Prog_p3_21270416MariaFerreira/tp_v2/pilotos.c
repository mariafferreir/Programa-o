/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
*/

#include "pilotos.h"
#include "utils.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int num_pilotos(char *nomeficheiro){
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
    nr=contador/3;
    
    return nr;
}



pilotos* inicializa_pilotos(char *nomeficheiro, int total){
    FILE *f= fopen(nomeficheiro, "rt");
    pilotos *aux;
    int i;
    
    if(f==NULL){
        fprintf(f, "Erro na abertura do ficheiro: %s\n", nomeficheiro);
        return 0;
    }
    
    aux = malloc(sizeof(pilotos) * (total));
    if(aux==NULL){
        printf("Erro na alocação de memoria para pilotos.\n");
        fclose(f);
        return 0;
    }
    
    for(int i=0; i<total; i++){
       if ((fscanf(f, "%99[^\n]   %d %d %d %d %d %f %d %d ", aux[i].nome_piloto,
                &aux[i].id_piloto, &aux[i].dia, &aux[i].mes,
                &aux[i].ano, &aux[i].peso_piloto, &aux[i].experiencia_piloto,
                &aux[i].impedimento_piloto, &aux[i].disponibilidade_piloto)) != 9) {
                    fprintf(stderr, "Erro na leitura do ficheiro.\n");
                    fclose(f);
                    return NULL;
        }
    }

    fclose(f);
    return aux;
}




void listar_pilotos(pilotos *p, int total){
    int i;
    
    printf("\n\n------LISTA DE PILOTOS------\n\n");
    
    if(p==NULL){
        printf("Nao existem pilotos!\n");
        return;
    }
    
    for(i=0; i<total; i++){
        printf("PILOTO %3d: \n\tNome: %s \n\tData de Nascimento: %2d.%2d.%4d \n\tPeso: %d \n\tExperiencia: %.2f \n\tImpedimento:  %d \n\tDisponibilidade:  %d \n\n",
                (p+i)->id_piloto, (p+i)->nome_piloto, (p+i)->dia, (p+i)->mes, (p+i)->ano, (p+i)->peso_piloto, (p+i)->experiencia_piloto, (p+i)->impedimento_piloto, (p+i)->disponibilidade_piloto);
    }
}

void procura_piloto(pilotos *p, int total){
    
    int i, flag=0;
    char nome[100];
    printf("\n\n------PROCURA PILOTO------\n\n");
    if(p==NULL){
        printf("Nao existem pilotos!\n");
        return;
    }
    
    printf("Nome do piloto: ");
    scanf(" %99[^\n]", nome);

    for(i=0; i<total; i++){
 
        if(strcmp(nome,(p+i)->nome_piloto)==0){
            printf("\nPILOTO %3d: \n\tNome: %s \n\tData de Nascimento: %2d.%2d.%4d \n\tPeso: %d \n\tExperiencia: %.2f \n\tImpedimento:  %d \n\tDisponibilidade:  %d \n\n",
                (p+i)->id_piloto, (p+i)->nome_piloto, (p+i)->dia, (p+i)->mes, (p+i)->ano, (p+i)->peso_piloto, (p+i)->experiencia_piloto, (p+i)->impedimento_piloto, (p+i)->disponibilidade_piloto);
            flag=1;
        }
        
    }
    
    if(flag==0){
        printf("Esse piloto nao existe!\n");
    } 
    
}

pilotos* adiciona_penalizacao(pilotos *p, int total){
    int id, i, pen;
    
    listar_pilotos(p,total);
    
    printf("\n\n------ADICIONAR PENALIZACAO------\n\n");
    
    printf("ID Piloto a quem adicionar penalizacao:  ");
    scanf(" %d", &id);
    
    do{
        printf("Penalizacao a adicionar:  ");
        scanf(" %d", &pen);
    }while(pen>3 || pen<1);
    
    
    for(i=0; i<total; i++){
        if(id == (p+i)->id_piloto){
            if((p+i)->impedimento_piloto == 3){
                (p+i)->impedimento_piloto == 3;
            }else{
                (p+i)->impedimento_piloto = (p+i)->impedimento_piloto + pen;
                
                if((p+i)->impedimento_piloto > 3){
                    (p+i)->impedimento_piloto = 3;
                }
                
            }
            
        }    
    }
    
    return p;
    
}


pilotos* atualiza_pilotos_fim_corrida(pequipas eq, pilotos *p, int total_p){
    int i,j;
    pequipas aux=NULL;
    
    aux=eq;
    
    
    for(i=0; i<total_p;i++){
        (p+i)->impedimento_piloto = (p+i)->impedimento_piloto - 1;
        if((p+i)->impedimento_piloto < 0){
            (p+i)->impedimento_piloto = 0;
        }
    }
   
    
   
   for(aux=eq;aux;aux=aux->prox){
        for(i=0; i<total_p;i++){
            if(aux->id_piloto == (p+i)->id_piloto){
                if(aux->ocorreu_acidente == COM_ACIDENTE){
                    (p+i)->experiencia_piloto = (p+i)->experiencia_piloto - 1;
                    (p+i)->impedimento_piloto = (p+i)->impedimento_piloto + 1;
                    if((p+i)->experiencia_piloto < 0){
                        (p+i)->experiencia_piloto = 0;
                    }
                }else{
                    (p+i)->experiencia_piloto = (p+i)->experiencia_piloto + (aux->contador_plugar*0.5);
                }
            }
        }
   }
    
    for(i=0; i<total_p; i++){
        (p+i)->disponibilidade_piloto = LIVRE;
    }
    
    
    return p;
}


void gravar_vetorP(pilotos *p, char *nomefich, int total) {
    FILE *f = fopen(nomefich, "wt");
    int i;

    if (!f) {
        fprintf(stderr, "Erro a abrir o ficheiro %s", nomefich);
        return;
    }


    
    for(int i=0; i<total; i++){
       fprintf(f, "%s", (p + i)->nome_piloto);
       fprintf(f, "\n");
       fprintf(f, "%d %d %d %d %d %.2f %d %d",
                 (p + i)->id_piloto,  (p + i)->dia,  (p + i)->mes,
                 (p + i)->ano,  (p + i)->peso_piloto,  (p + i)->experiencia_piloto,
                 (p + i)->impedimento_piloto,  (p + i)->disponibilidade_piloto);
       if(i!=total){
            fprintf(f, "\n\n");
       }
    }

    fclose(f);
}



pilotos* atualiza_experiencia_campeonato(pcampeonato camp,  pilotos *p, int total_p){
    
  pcampeonato aux=camp;
  int  valores[total_p];
  int i=0;
  int maior=0;
  
  while(aux){
      valores[i]=aux->pontuacoes;
      aux=aux->prox;
      i++;
  }

  for(i=0; i<total_p;i++){
      if(valores[i]>maior){
          maior=valores[i];
      }
  }
    
  for(aux=camp; aux; aux=aux->prox){
      if(maior == aux->pontuacoes){
          for(i=0; i< total_p;i++){
              if(aux->id_piloto ==  (p+i)->id_piloto){
                (p+i)->experiencia_piloto+=10;
              }
          }
          
      }
  }
  return p;
}