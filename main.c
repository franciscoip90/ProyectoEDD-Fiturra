#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

const int matrizTest = 0;
const int Ciclosevo = 5;

typedef struct ubiccartesiana{
    int x;
    int y;
}ubicCartesiana;

typedef struct bacteriasinfo{
    unsigned char numeromagico[3];
    unsigned int N;
    unsigned int M;
    unsigned int cantidad;
} bacteriasInfo;

typedef struct coordenadas{
    unsigned int x;
    unsigned int y;
}Coordenadas;

typedef struct nodo{
    ubicCartesiana Coordenadas;
    int vida;
    struct Nodo* sgte;
} Nodo;

typedef struct Pila{
    Nodo* ultimo;
    int tam;
}Pila;

ubicCartesiana VecinoNorte(ubicCartesiana objetivo, int N){
    int x,y;
    if ((objetivo.x - 1)< 0){
        x=N-1;
    }else{
        x=objetivo.x - 1;
    }
    y=objetivo.y;

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoNO(ubicCartesiana objetivo, int N, int M){
    int x,y;

    if ((objetivo.x - 1)< 0){
        x=N-1;
    }else{
        x=objetivo.x - 1;
    }
    if ((objetivo.y - 1)< 0){
        y=M-1;
    }else{
        y=objetivo.y - 1;
    }

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoNE(ubicCartesiana objetivo, int N, int M){
    int x,y;
    if ((objetivo.x - 1)< 0){
        x=N-1;
    }else{
        x=objetivo.x - 1;
    }

    if ((objetivo.y + 1)>= (M)){
        y=0;
    }else{
        y=objetivo.y + 1;
    }

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoEste(ubicCartesiana objetivo, int M){
    int x,y;
    if ((objetivo.y + 1) >= M){
        y=0;
    }else{
        y=objetivo.y + 1;
    }
    x=objetivo.x;

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoOeste(ubicCartesiana objetivo, int M){
    int x,y;
    if ((objetivo.y - 1) < 0){
        y=M-1;
    }else{
        y=objetivo.y - 1;
    }
    x=objetivo.x;

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoSO(ubicCartesiana objetivo, int N, int M){
    int x,y;
    if ((objetivo.x + 1)>=N){
        x=0;
    }else{
        x=objetivo.x + 1;
    }

    if ((objetivo.y - 1)<0){
        y=M-1;
    }else{
        y=objetivo.y - 1;
    }

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoSur(ubicCartesiana objetivo, int N){
    int x,y;
    if ((objetivo.x + 1)>= N){
        x=0;
    }else{
        x=objetivo.x + 1;
    }
    y=objetivo.y;

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

ubicCartesiana VecinoSE(ubicCartesiana objetivo, int N, int M){
    int x,y;
    if ((objetivo.x + 1)>=N){
        x=0;
    }else{
        x=objetivo.x + 1;
    }

    if ((objetivo.y + 1)>=M){
        y=0;
    }else{
        y=objetivo.y + 1;
    }

    ubicCartesiana VN;
    VN.x = x;
    VN.y = y;
    return VN;
}

Pila* crearPila(){
    Pila* indice;
    indice = (Pila*) malloc(sizeof(Pila));
    if(indice!=NULL){
        indice->tam = 0;
        indice->ultimo=NULL;
        return indice;

    }else{
    printf ("Error \n\n");
        exit(-1);
    }

}

void Coloca(Pila* Pila, ubicCartesiana coordenada, int vida){
    Nodo* indice=(Nodo*) malloc(sizeof(Nodo));
    indice->vida=vida;
    indice->Coordenadas=coordenada;

    if(Pila->tam == 0){
        indice->sgte=NULL;
        Pila->ultimo=indice;
    }else{
        indice->sgte=Pila->ultimo;
        Pila->ultimo=indice;
    }
    Pila->tam++;
}

void Saca(Pila* Pila){
    if (Pila->tam > 0){
        Nodo *indice = Pila->ultimo->sgte;
        Pila->ultimo=indice;
        Pila->tam--;
    }

}

int vecinosVivos(ubicCartesiana objetivo,int N, int M,int matriz[N][M]){
    int VecinosVivos=0;
    if(matriz[VecinoNorte(objetivo,N).x][VecinoNorte(objetivo,N).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoNO(objetivo,N,M).x][VecinoNO(objetivo,N,M).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoNE(objetivo,N,M).x][VecinoNE(objetivo,N,M).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoEste(objetivo,M).x][VecinoEste(objetivo,M).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoOeste(objetivo,M).x][VecinoOeste(objetivo,M).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoSO(objetivo,N,M).x][VecinoSO(objetivo,N,M).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoSur(objetivo,N).x][VecinoSur(objetivo,N).y] == 1){
        VecinosVivos++;
    }
    if(matriz[VecinoSE(objetivo,N,M).x][VecinoSE(objetivo,N,M).y] == 1){
        VecinosVivos++;
    }
    return VecinosVivos;
}

void vidadBacteria(int N, int M,int matriz[N][M]){
    ubicCartesiana Pertenece;
    int vida=0;
    Pila* MK = crearPila();
    int a,b;
    for (a=0;a<N;a++){
        for (b=0;b<M;b++){
            ubicCartesiana objetivo;
            objetivo.x=a;
            objetivo.y=b;
            Pertenece.x=a;
            Pertenece.y=b;
            if ((matriz[a][b]==0) && ((vecinosVivos(objetivo,N,M,matriz)) == 3)){
                Coloca(MK,Pertenece,1);
            }

            else if ((matriz[a][b]==1) && (((vecinosVivos(objetivo,N,M,matriz)) == 2) || ((vecinosVivos(objetivo,N,M,matriz)) == 3))){
                vida=1;

            }
            else if (matriz[a][b]==1){
                Coloca(MK,Pertenece,0);
            }

        }
    }

    while (MK->ultimo != NULL){
        matriz[MK->ultimo->Coordenadas.x][MK->ultimo->Coordenadas.y]=MK->ultimo->vida;
        Saca(MK);
    }
}

int bacteriasVivas(int N, int M, int matriz[N][M]){
    int contador=0;
    int x,y;
    for (x=0;x<N;x++){
        for (y=0;y<M;y++){
            if(matriz[x][y] == 1){
                contador++;
            }}}
    return contador;
}

void ArchivoOP(int N,int M, int MatrizNueva[N][M]) {
    Pila* MK = crearPila();
    ubicCartesiana Pertenece;
    FILE *fr, *fw;
    bacteriasInfo IB;
    Coordenadas cor;
    int i,j;

    fr = fopen("bacterias.bin", "rb");

    fread(&IB, sizeof(bacteriasInfo), 1, fr);

    for (i=0;i<IB.cantidad;i++){
        fread(&cor, sizeof(Coordenadas), 1, fr);
        Pertenece.x=cor.x;
        Pertenece.y=cor.y;
        Coloca(MK,Pertenece,1);
    }
    fclose(fr);

    int n=IB.N;
    int m=IB.M;

    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            MatrizNueva[i][j]=0;
        }
    }

    while (MK->ultimo != NULL) {
        MatrizNueva[MK->ultimo->Coordenadas.x][MK->ultimo->Coordenadas.y] = MK->ultimo->vida;
        Saca(MK);
    }


}

bacteriasInfo Iarchivo() {

    bacteriasInfo IB;
    Coordenadas cor;
    //FILE * fr=fopen (const char *bacterias.bin, const char *rb);
    FILE *fr;
    fr = fopen("bacterias.bin", "rb");
    fread(&IB,sizeof(bacteriasInfo),1,fr);

    if(IB.numeromagico[0]==237){
        if(IB.numeromagico[1]==210){
            if(IB.numeromagico[2]==1){
                if(IB.numeromagico[3]==114){
                    printf ("numero magico OK\n");
                }else{
                    printf ("error, numero magico No OK \n");
                    exit(0);
                }
            } else{
                    printf ("error, numero magico No OK \n");
                exit(0);
            }
        }else{
                    printf ("error, numero magico No OK \n");
            exit(0);
        }

    }else{
                    printf ("error, numero magico No OK \n");
        exit(0);
    }
    return IB;
}

int Guardar(int N,int M,int K, int Matriz[N][M]){
    FILE *fw;
    int contador=0,header;
    int i,j;
    fw = fopen("salida.bin","wb");
    header= 0x7201D2ED;
    fwrite(&header, sizeof(int), 1, fw);
    fwrite(&N, sizeof(int), 1, fw);
    fwrite(&M, sizeof(int), 1, fw);
    fwrite(&K, sizeof(int), 1, fw);

    for (i=0;i<N;i++){
        for (j=0;j<M;j++){
            if (Matriz[i][j]==1){
                fwrite(&i, sizeof(int), 1, fw);
                fwrite(&j, sizeof(int), 1, fw);
                contador++;
            }

        }
    }
    if (contador==K){
        printf ("matriz guardada en <salida.bin>.\n");
    }else{
        printf ("error \n");
    }
    fclose(fw);
}

int main() {
    int N=5;
    int M=7;
    bacteriasInfo IB=Iarchivo();
    N=IB.N;
    M=IB.M;
    int matriz[N][M];
    int i,j;
    ArchivoOP(N,M,matriz);
    if(matrizTest==0){
        int cont = 0;
        for (i=0;i<N;i++){
            for (j=0;j<M;j++){
                if(i%2 == 0){
                    matriz[i][j]=1;
                }
                else
                    matriz[i][j]=0;
                if(j==3)matriz[i][j]=0;
                cont++;
            }
        }
    }
    printf ("bacterias vivas= %d\n", bacteriasVivas(N, M, matriz));
    for (i=0;i<N;i++){
        for (j=0;j<M;j++){
            printf (" %d",matriz[i][j]);
        }
        printf ("\n");
                    printf ("\n");
    }
    int viven = 0;
    int c;
    for (c=1;c<=Ciclosevo;c++){
        vidadBacteria(N,M,matriz);
        viven = bacteriasVivas(N, M, matriz);
        printf ("hay %d baterias en ciclo= %d\n",viven,c);
        if (viven == 0){
            printf ("se murieron bacterias en el ciclo %d\n",c);
            break;
        }
    }
    Guardar(N,M,viven,matriz);
    return 0;
}

