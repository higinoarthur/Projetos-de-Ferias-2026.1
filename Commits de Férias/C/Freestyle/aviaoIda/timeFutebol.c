#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    int idade;
    int gols;
    int assists;
    int nCamisa;
    float nota;
}st_jogador;
typedef struct{
    st_jogador elenco[4];
    char nome[30];
    int anoFundacao;
    char nomeTreinador[30];
    int nTitulos;
    st_jogador melhorJogador;
    st_jogador artilheiro;
}st_timeFutebol;

void atribuiTimeFutebol(st_timeFutebol *timeFutebol) {
    printf("Digite o ano de fundacao do clube: ");
    scanf("%d",&timeFutebol->anoFundacao);
    printf("Digite o nome do treinador do clube: ");
    scanf("%s",timeFutebol->nomeTreinador);
    printf("Digite o numero de titulos do clube: ");
    scanf("%d",&timeFutebol->nTitulos);
    getchar();
}
float calculaNota(int gols, int assists) {
    float nota = 6.0f + ((1.0f * gols)/10.0f) + ((1.0f * assists)/10.0f);
    if (nota > 10.0) {
        nota = 10.0f;
    }
        return nota;
}
void atribuiElenco( st_timeFutebol *timeFutebol) {
    srand(time(NULL));
    timeFutebol->melhorJogador.nota =-1.0;
    timeFutebol->artilheiro.gols =-1;
    for ( int i = 0; i < 4; i++ ) {
        printf("Digite o nome do %d jogador", i+1);
        scanf("%s", timeFutebol->elenco[i].nome);
        getchar();
        printf("Digite a idade do %d jogador", i+1);
        scanf("%d", &timeFutebol->elenco[i].idade);
        timeFutebol->elenco[i]. gols = (rand() %20)+1;
        timeFutebol->elenco[i].assists = (rand() %20)+1;
        printf("Digite o numero da camisa do %d jogador", i+1);
        scanf("%d", &timeFutebol->elenco[i].nCamisa);
        getchar();
        timeFutebol->elenco[i].nota = calculaNota(timeFutebol->elenco[i].gols,timeFutebol->elenco[i].assists);
        if (timeFutebol->elenco[i].gols > timeFutebol->artilheiro.gols) {
            timeFutebol->artilheiro = timeFutebol->elenco[i];
        }
        if (timeFutebol->elenco[i].nota > timeFutebol->melhorJogador.nota) {
            timeFutebol->melhorJogador = timeFutebol->elenco[i];
        }
    }
}
int main() {
    FILE *arq;
    st_timeFutebol timeFutebol;
    printf("Digite o nome do clube: ");
    scanf("%s", timeFutebol.nome);
    getchar();
    atribuiTimeFutebol(&timeFutebol);
    atribuiElenco(&timeFutebol);
    arq = fopen(timeFutebol.nome, "w");
    if (arq != NULL) {
        fprintf(arq, "Nome: %s\nFundacao: %d\nNome do Treinador: %s\nNumero de Titulos: %d\n",
            timeFutebol.nome,timeFutebol.anoFundacao,timeFutebol.nomeTreinador, timeFutebol.nTitulos);
        fprintf(arq, "ELENCO:\n");
        for ( int i = 0; i < 4; i++ ) {
            fprintf(arq,"%s\t%d\t%d\t%d\t%.2f\n",
                timeFutebol.elenco[i].nome,timeFutebol.elenco[i].idade,timeFutebol.elenco[i].gols,timeFutebol.elenco[i].assists,timeFutebol.elenco[i].nota);
        }
        fprintf(arq, "MELHOR JOGADOR:\n");
        fprintf(arq,"%s\t%.2f\n",
                timeFutebol.melhorJogador.nome,timeFutebol.melhorJogador.nota);
        fprintf(arq, "ARTILHEIRO:\n");
        fprintf(arq,"%s\t%d\n",
                timeFutebol.artilheiro.nome,timeFutebol.artilheiro.gols);
    }
    fclose(arq);
    return 0;
}