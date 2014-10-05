#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LO (320)
#define HI (340)

#define TEMP_RAND (LO + (float)(rand()/(float)(RAND_MAX/(HI-LO))))
#define POWER_RAND ((float)rand()/(float)RAND_MAX)

char T_FNAME[32], P_FNAME[32];
float*** allocate3D(float l,float m,float n);

int main (int argc, char** argv)
{
    int i, j, k, rows_cols, layers;
    float ***T, ***P;
    FILE *ft, *fp;

    if (argc < 3)
    {
        printf("./gen [rows/cols] [layers]\n");
        return 1; 
    }

    rows_cols = atoi(argv[1]);
    layers = atoi(argv[2]);


    T =  (float***)malloc(layers * sizeof(float**));
    P =  (float***)malloc(layers * sizeof(float**));

    for(i = 0; i < layers; i++)
    {
        T[i] = (float**)malloc(rows_cols*sizeof(float*));
        for(j = 0; j < rows_cols; j++)
            T[i][j] = (float*)malloc(rows_cols*sizeof(float));
    }


    for(i = 0; i < layers; i++)
    {
        P[i] = (float**)malloc(rows_cols*sizeof(float*));
        for(j = 0; j < rows_cols; j++)
            P[i][j] = (float*)malloc(rows_cols*sizeof(float));
    }

    if (!T || !P)
    {
        printf("Cannot allocate memory\n");
        if (T) free(T);
        if (P) free(P);
        return 1;
    }

    srand(time(NULL));
    sprintf(T_FNAME, "temp_%dx%d",rows_cols,layers);
    ft = fopen(T_FNAME, "wb");
    if(!ft)
    {
        printf("Cannot open file %s\n",T_FNAME);
        return 1;
    }

    sprintf(P_FNAME, "power_%dx%d",rows_cols,layers);
    fp = fopen(P_FNAME, "wb");
    if(!fp)
    {
        printf("Cannot open file %s\n",P_FNAME);
        return 1;
    }

    for(i = 0; i < layers; i++)
        for(j = 0; j < rows_cols; j++)
            for(k = 0; k < rows_cols; k++)
            {
                T[i][j][k] = TEMP_RAND;
                P[i][j][k] = POWER_RAND;            
            }

    for(i = 0; i < layers; i++)
        for(j = 0; j < rows_cols; j++)
            for(k = 0; k < rows_cols; k++)
            {
                fprintf(ft, "%f\n",T[i][j][k]);
                fprintf(fp, "%f\n",P[i][j][k]);    
            }  

    fclose(ft);
    fclose(fp);

    for(i = 0; i < layers; i++)
        for(j = 0; j < rows_cols; j++)
        {
            free(T[i][j]);
            free(P[i][j]); 
        }

    for(k = 0; k < layers; k++)
    {
        free(T[k]);
        free(P[k]);
    }

    free(T);
    free(P);
    return 0;
}


float*** allocate3D(float l,float m,float n)
{
    float ***arr3D;
    int i,j,k;

    arr3D = (float***)malloc(l * sizeof(float **));

    for(i=0;i<l;i++)
    {
        arr3D[i] = (float**)malloc(m * sizeof(float*));
        for(j=0;j<m;j++)
        {
            arr3D[i][j] = (float*)malloc(n*sizeof(float));
        }
    }

    return arr3D;
}
