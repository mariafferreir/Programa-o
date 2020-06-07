/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
*/

#include "structs.h"
#include "carros.h"
#include "pilotos.h"
#include "corrida.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


int num_equipas(int num_max, carros *c, int total_c, pilotos *p, int total_p){
    int contador_carros=0, contador_pilotos=0, total_equipas;
    
    for(int i=0; i<total_c; i++){
        if((c+i)->avariado <= 0 ){
            contador_carros++;
        }
    }
    
    for(int j=0; j<total_p; j++){
        if((p+j)->impedimento_piloto <= 0  ){
            contador_pilotos++;
        }
    }
    
    if(contador_pilotos <= contador_carros){
        total_equipas = contador_pilotos;
    }else{
        total_equipas = contador_carros;
    } 
    
    if(total_equipas>=num_max){
        return num_max;
        
    }else{
        return total_equipas;
    }
    
    
}

pequipas criaEquipa(pequipas eq, int total_e, carros *c, int total_c, pilotos *p, int total_p){
    int conta_equipas=0;
    pequipas novo; 
    pequipas aux;
    novo = malloc(sizeof(equipas)); 
    int i, a=0;
   
    if(novo == NULL){
        fprintf(stderr, "Erro a reservar memoria para o novo paciente.\n");
        return eq;
    }
    
    if(total_p < total_c){
        for(int i=0; i<total_p; i++){ 
            if((p+i)->impedimento_piloto <= 0 && (p+i)->disponibilidade_piloto == LIVRE){
                
                novo->ocorreu_acidente=SEM_ACIDENTE;
                 
                novo->id_piloto = (p+i)->id_piloto;
                (p+i)->disponibilidade_piloto = OCUPADO;

                do{
                    a=intUniformRnd(0, (total_c-1));
                }while((c+a)->avariado > 0 || (c+a)->disponibilidade_carro == OCUPADO);

                novo->id_carro = (c+a)->id_carro;
                (c+a)->disponibilidade_carro = OCUPADO;
                    
                break;
            }
        }
    }else{
        for(i=0; i<total_c; i++){
            if((c+i)->avariado <= 0  && (c+i)->disponibilidade_carro == LIVRE){

                novo->ocorreu_acidente=SEM_ACIDENTE;

                novo->id_carro = (c+i)->id_carro;
                (c+i)->disponibilidade_carro = OCUPADO;

                do{
                    a=intUniformRnd(0, (total_p-1));
                }while((p+a)->impedimento_piloto >0 || (p+a)->disponibilidade_piloto == OCUPADO );

                novo->id_piloto = (p+a)->id_piloto;
                (p+a)->disponibilidade_piloto = OCUPADO;
                
                break;  
            }
            
        }
        
    }
    
    novo->contador_plugar=0;
    novo->classificacao=0; 
    novo->ocorreu_acidente=SEM_ACIDENTE;
    novo->tempo=0;
    novo->prox= NULL;
    
    
    if(eq==NULL ){
        novo->prox = eq; 
        eq=novo;
    }
    else{
        aux=eq;
        while(aux->prox != NULL){
            aux=aux->prox;
        }
        novo->prox=aux->prox;
        aux->prox=novo;
    }
    
   
    return eq;
    
}



void listar_equipas(pequipas eq){
    int i=1;
    while(eq){
        printf("\n\n\n\nEQUIPA %3d:  \n\tID Piloto: %d\t ID Carro: %d\n\n", i, eq->id_piloto, eq->id_carro);
        eq=eq->prox;
        i++;
    }
}


pequipas getinfo(pequipas aux, int index){
    
    while(aux && index--){
        aux=aux->prox;
    }
    
    return aux;
}

pcorridas adicionaNo(int *flag,  int v,int num_voltas, int comprimento, int nr_carros, pequipas infoequipa, int total_e, pcorridas corrida, carros *c, int total_c, pilotos *p, int total_p){
    pcorridas novo, aux;
    int idade, peso, experiencia, potencia;
    int i, d, m, a;
    
    
    
    for(i=0; i<total_e; i++){
        if(infoequipa->ocorreu_acidente == COM_ACIDENTE){
            return corrida;
        }
    }
    
    
    novo= malloc(sizeof(corridas));
    
        
    
    if(!novo){
        fprintf(stderr, "Erro a reservar memoria para o novo no de corrida.\n");
        return corrida;
    }
    
    
    novo->com_pista = comprimento;
    novo->nr_voltas = num_voltas;
    novo->max_carros = nr_carros;
    novo->volta = v;
    novo->id_carro=infoequipa->id_carro ;
    novo->id_piloto=infoequipa->id_piloto;
    novo->lugar=0;
    novo->acidente=probEvento(PROB_ACIDENTE);
   
    //----------Idade Piloto------------
    for(i=0; i< total_p;i++){
        if(infoequipa->id_piloto == (p+i)->id_piloto){
            d = (p+i)->dia;
            m = (p+i)->mes;
            a = (p+i)->ano;
            idade = retornaIdade(d, m, a);
        }
    }
    
    
    //-----------Peso Piloto------------
    for(i=0; i< total_p;i++){
        if(infoequipa->id_piloto == (p+i)->id_piloto){
            peso=(p+i)->peso_piloto;
        }
    }
    
    
    //----------Potencia Carro----------
    for(i=0; i< total_c;i++){
        if(infoequipa->id_carro  == (c+i)->id_carro){
            potencia=(c+i)->potencia_carro;
        }
    }
    
    novo->tempo=0;
    novo->tempo= calculaSegundos(idade, peso, experiencia, potencia, comprimento);
    
    
    if(novo->acidente == 1){
        novo->volta_acidente=v;
        novo->tempo=0;
        *flag = COM_ACIDENTE;
        
    }else{
        novo->volta_acidente=0;
        *flag = SEM_ACIDENTE;
    }    
    
    novo->prox=NULL;
    
     if(corrida==NULL || (corrida->tempo > novo->tempo)){
        novo->prox= corrida;
        corrida=novo;
    }else{
        aux=corrida;
        
        while(aux->prox && aux->prox->tempo <= novo->tempo){
            aux=aux->prox;
        }
        
        novo->prox=aux->prox;
        aux->prox=novo;
    }
    
    
    return corrida;
}


void mostraCorridaCompleta(int num_voltas, pcorridas corrida, pilotos *p, int total_p){
    int i,j;
    pcorridas aux, aux_c;
    
    if(!corrida){
        puts("ERRO NA CORRIDA!\n");
        return;
    }
    
    
    puts("\n\nKARTS@ISEC - Detalhes de corrida completa: \n\n\n");
    
    for(j=0; j<num_voltas;j++){
        printf("\n\nCLASSIFICACAO DA %da VOLTA: \n", (j+1));
        for(aux=corrida; aux; aux=aux->prox){
            if(aux->volta==(j+1)){
                if(aux->acidente!=COM_ACIDENTE){
                    for( i=0; i<total_p;i++){
                        if(aux->id_piloto == (p+i)->id_piloto){
                             printf("\t%do: %s (ID: %d)    //   Carro %d: %d segundos\n", aux->lugar, (p+i)->nome_piloto ,(p+i)->id_piloto, aux->id_carro, aux->tempo);
                        }  
                    }
                }
            }
        }
    }
    
    for(aux_c = corrida; aux_c; aux_c=aux_c->prox){
        if(aux_c->acidente==COM_ACIDENTE){
            for(int i=0; i<total_p;i++){
                if(aux_c->id_piloto == (p+i)->id_piloto){
                    printf("Carro com acidente na %da volta: \n", aux_c->volta);
                    printf("\t %s (ID: %d)    //   Carro %d: %d segundos\n", (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                }  
            }
        }
    }
    
    
}


pequipas colocaAcidente(pequipas eq, int corredor){
    pequipas aux=NULL;
    
    aux=eq;
    
    for(int i=0; i<corredor;i++){
        aux=aux->prox;
    }
    
    aux->ocorreu_acidente=COM_ACIDENTE;
    
    
    return eq;
}

pcorridas atribuiClassificao(int num_voltas,pcorridas corrida){
    int i=1;
    pcorridas aux;
    aux=corrida;
       
    while(aux){
        if(num_voltas == aux->volta){
           if(aux->acidente == SEM_ACIDENTE){
               aux->lugar= i;
               i++;
            }else{
                aux->lugar=0;
            } 
        }
        aux=aux->prox;
    }
    
 
    
    return corrida;
    
}

void mostraResultadosVolta(int v, pcorridas corrida,  pilotos *p, int total_p){
    
    
    pcorridas aux_c;
    aux_c=corrida;
    
    printf("\n\n\n\nCLASSIFICACAO DA %da VOLTA: \n", v);
    
    while(aux_c){
        if(aux_c->volta==v){
            if(aux_c->acidente!=COM_ACIDENTE){
                for(int i=0; i<total_p;i++){
                    if(aux_c->id_piloto == (p+i)->id_piloto){
                        if(aux_c->lugar !=0){
                            printf("\t%do: %s (ID: %d)    //   Carro %d: %d segundos\n", aux_c->lugar, (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                        }  
                    }  
                }
            }
        }
        aux_c=aux_c->prox;
    }

    for(aux_c = corrida; aux_c; aux_c=aux_c->prox){
        if(aux_c->acidente==COM_ACIDENTE){
            for(int i=0; i<total_p;i++){
                if(aux_c->id_piloto == (p+i)->id_piloto){
                    printf("\nCarro com acidente na %da volta: \n",aux_c->volta_acidente);
                    printf("\t %s (ID: %d)    //   Carro %d: %d segundos\n", (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                }  
            }
        }
    }




}





pequipas calculaTempoFinal( pequipas eq, pcorridas corrida){
    int somaTempos;
    pcorridas aux_c;
    pequipas aux_e;
    aux_e=eq;
    aux_c=corrida;
    
    while(aux_e){
        somaTempos=0;
        aux_c=corrida;
        while(aux_c){
            if(aux_e->id_piloto == aux_c->id_piloto){
                somaTempos += aux_c->tempo;
            }
            aux_e->classificacao=somaTempos;
            aux_c=aux_c->prox;
        }
        aux_e=aux_e->prox;
    }
    return eq;
    
}

pequipas classificacaoFinal( pequipas eq, pcorridas corrida, int total_e){
    pequipas aux=NULL, auxClassificacao=NULL;
    int i=0, j=0;
    int classificacao[total_e];
    aux=eq;
    int aux_classificacao;
    
    while(aux){
        classificacao[i]=aux->classificacao;
        i++;
        aux=aux->prox;
    }
    
    for (i = 0; i < total_e; i++){
        for (j = 0; j < total_e; j++){
            if (classificacao[i] < classificacao[j] ){
                aux_classificacao=classificacao[i]; 
                classificacao[i]=classificacao[j];
                classificacao[j]=aux_classificacao;
            }
        }
    }
    auxClassificacao=eq;
    
    
    while(auxClassificacao){
        for(i=1; i<(total_e+1);i++){ 
            if(auxClassificacao->classificacao == classificacao[i]){
                if(auxClassificacao->ocorreu_acidente == SEM_ACIDENTE){
                    auxClassificacao->classificacao=(i);
                }else{
                    auxClassificacao->classificacao=0;  
                }
            }
        }
        auxClassificacao=auxClassificacao->prox;  
    }
    
    
    
    return eq;
    
}


pequipas contaPrimeirosLugares(int num_voltas, pequipas eq,int total_e, pcorridas corrida){
    int i=1;
    int c;
    pcorridas aux_c;
    pequipas aux_e;
    
    for(aux_e=eq;aux_e;aux_e=aux_e->prox){
        for(aux_c=corrida;aux_c;aux_c=aux_c->prox){
            if(aux_e->id_piloto==aux_c->id_piloto){
                if(aux_c->lugar==1){
                    aux_e->contador_plugar++;
                }
            }
        }
    }
    
    return eq;
}

void  mostraClassificaoFinal(int num_voltas, pequipas eq,int total_e, pcorridas corrida, pilotos *p, int total_p){
    int i=0, classificacao=1;
    pequipas aux_e;
    pcorridas aux_c;
    int somaTempo;
    printf("\n\n\n\nCLASSIFICACAO FINAL DA CORRIDA: \n");
    for(i=0; i<total_e;i++){
        for(aux_e=eq; aux_e; aux_e=aux_e->prox){
            if(aux_e->classificacao == i){
                somaTempo=0;
                for(aux_c=corrida; aux_c; aux_c=aux_c->prox){
                    if(aux_e->id_piloto == aux_c->id_piloto){
                        somaTempo += aux_c->tempo;
                    } 
                }
                for(int j=0; j<total_p;j++){
                    if(aux_e->id_piloto == (p+j)->id_piloto){
                        if(aux_e->ocorreu_acidente == SEM_ACIDENTE){
                            printf("\t%do: %s (ID: %d)    //   Carro %d: %d segundos\n",classificacao, (p+j)->nome_piloto ,(p+j)->id_piloto, aux_e->id_carro, somaTempo);
                            classificacao++;
                        }
                    }
                }    
            }
        }
    }
    
    
    for(aux_c = corrida; aux_c; aux_c=aux_c->prox){
        if(aux_c->acidente==COM_ACIDENTE){
            for(int i=0; i<total_p;i++){
                if(aux_c->id_piloto == (p+i)->id_piloto){
                    printf("Carro com acidente na %da volta: \n", aux_c->volta);
                    printf("\t %s (ID: %d)    //   Carro %d: %d segundos\n", (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                }  
            }
        }
    }
}    

void mostraVoltaEspecifica(pcorridas corrida, pilotos *p, int total_p){
    
    pcorridas aux_c;
    int v;
    printf("\n\n\nIndique a volta que deseja ver: ");
    scanf(" %d", &v);
    
    
    printf("\n\nCLASSIFICACAO DA %da VOLTA: \n", v);
    for(aux_c = corrida; aux_c; aux_c=aux_c->prox){
        if(aux_c->volta==v){
            if(aux_c->acidente!=COM_ACIDENTE){
                for(int i=0; i<total_p;i++){
                    if(aux_c->id_piloto == (p+i)->id_piloto){
                         printf("\t%do: %s (ID: %d)    //   Carro %d: %d segundos\n", aux_c->lugar, (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                    }  
                }
            }else{
                for(int i=0; i<total_p;i++){
                    if(aux_c->id_piloto == (p+i)->id_piloto){
                        printf("Carro com acidente na %da volta: \n", v);
                        printf("\t %s (ID: %d)    //   Carro %d: %d segundos\n", (p+i)->nome_piloto ,(p+i)->id_piloto, aux_c->id_carro, aux_c->tempo);
                    }  
                }
            }
        }
    }
    
    
    
    
}   

void libertaCorrida(pcorridas corrida){
    pcorridas aux;
    while(corrida){
        aux = corrida; 
        corrida=corrida->prox;
        free(aux);
    }
}


pequipas inicializa_corrida( carros *c, int total_c, pilotos *p, int total_p){
    pcorridas corrida=NULL;
    pequipas infoequipa;
    pequipas eq = NULL;
    int total_e;
    int num_voltas, comprimento, nr_carros;
    int c_corredores=0, c_voltas=1;
    int i, j;
    int flag_acidente;
    int op;
    
    
    printf("\n\n\n\n\nDEFINIR CORRIDA: \n\n");
    do{
        printf("\n\tNumero de Voltas [5-10]: ");
        scanf(" %d", &num_voltas);
    }while(num_voltas<5 || num_voltas>10);
    
    do{
    printf("\n\tComprimento da pista em metros [500-1000]: ");
        scanf(" %d", &comprimento);
    }while(comprimento<500 || comprimento>1000);
    
    printf("\n\tNumero maximo de carros que podem participar: ");
    scanf(" %d", &nr_carros);
    
    
    total_e=num_equipas(nr_carros,c, total_c, p, total_p);
    
    
    //printf("Numero equipas: %d\n", total_e);
    
    for(i=0; i<total_e;i++){
        eq=criaEquipa(eq, total_e, c, total_c, p, total_p);
    }
    
    listar_equipas(eq);
    
    
    for(i=0; i<(total_e*num_voltas); i++){
        infoequipa=getinfo(eq,c_corredores);
        if(infoequipa->ocorreu_acidente == SEM_ACIDENTE){
            flag_acidente=SEM_ACIDENTE;
            corrida=adicionaNo(&flag_acidente,c_voltas,num_voltas, comprimento, nr_carros,infoequipa, total_e, corrida, c, total_c, p, total_p);
            if(flag_acidente==COM_ACIDENTE){
                eq=colocaAcidente(eq,c_corredores);
            }
        }
     
    c_corredores++; 
        
    if(c_corredores == total_e){ 
        corrida=atribuiClassificao(c_voltas, corrida);
        c_corredores=0;
        mostraResultadosVolta(c_voltas,corrida, p, total_p);
        espera(5);
        c_voltas++;
     }
    }
    
    eq=calculaTempoFinal(eq,corrida);
    eq=classificacaoFinal(eq,corrida,total_e);
    //listar_equipas(eq);
    eq=contaPrimeirosLugares(num_voltas, eq, total_e, corrida);
    mostraClassificaoFinal(num_voltas, eq, total_e, corrida,p, total_p);
    
    
    do{
        menuFinaldeCorrida();
        scanf(" %d", &op);
        switch(op){
            
            case 1:
                mostraCorridaCompleta(num_voltas, corrida, p, total_p);
                break;
            case 2:
                mostraVoltaEspecifica(corrida, p, total_p);
                break;   
        }            
    }while(op!=3);
    
    libertaCorrida(corrida);
    
    return eq;
}



