#include <stdio.h>
#include <stdlib.h>
int Tmc[100], Tmcach[100], Temp[100];
// Fonction de verification si exist le donnes
int verif(int t[], int e, int ta)
{
    int v, i;
    v = 0;
    i = 0;
    while (v == 0 && i < ta)
    {
        if (t[i] == e)
        {
            v = 1;
        }
        else
            (i++);
    }
    return v;
}
// Fonction de laffichage
void affich(int t[], int ta)
{
    int i;
    printf("\n|------------");
    for (i = 0; i < ta; i++)
    {
        if (t[i] >= 10)
            printf("|\n| %6d     |\n|------------", t[i]);
        else
            printf("|\n|     0%d     |\n|------------| ", t[i]);
    }
    printf("\n\n");
}
// remplisser les element des tableau
void read(int t[], int ta)
{
    int i;
    printf("\n");
    for (i = 0; i < ta; i++)
    {
        printf("->  ");
        t[i] = rand() % 58 - 1;
        printf("%d", t[i]);
    }
}
// Fonction remplissage de tableau initialiment
void fil(int t[], int ta)
{
    int i;
    for (i = 0; i < ta; i++)
    {
        t[i] = -1;
    }
}

// LRU

void lru(int T1[], int T2[], int n, int m)
{
    // n = taille MC et m= taille cache
    int i, j, l, k = 0;
    int miss = 0, hit = 0, r = 0, z, a, B;
    for (i = 0; i < n; i++)
    {
        l = 0;
        for (j = 0; j < m; j++)
        {
            if (T1[i] == T2[j])
            {
                hit++;
                l = 1;
            }
        }
        // debut remplier le tb de Mcach
        if (l == 0 && r < m)
        {
            miss++;
            T2[r] = T1[i];
            r++;
        }
        else
        {
            if (l == 0 && r == m)
            {
                // le tableau de Mcach et complet
                z = 0; // z indice pour tab de temp
                for (k = i - 1; k >= 0; k--)
                {
                    // k compter pour Mc
                    if (z < m)
                    {
                        for (j = 0; j < m; j++)
                        {
                            // rcherch chaine de rifirens avec Tb de Mcach
                            if (T1[k] == T2[j])
                            {
                                if (z == 0)
                                {
                                    // debut
                                    Temp[z] = T1[k];
                                    z++;
                                }
                                else
                                {
                                    B = 0; // boolene
                                    for (a = 0; a < z; a++)
                                    {
                                        if (Temp[a] == T1[k])
                                        {
                                            B = 1; // si trover le chaine de rifrence evec le tb tomp
                                        }
                                    }
                                    if (B == 0)
                                    { // si n'est pas trover le chaine de rifernce
                                        Temp[z] = T1[k];
                                        z++;
                                    }
                                }
                            }
                        }
                    }
                }
                for (j = 0; j < m; j++)
                {
                    if (Temp[z - 1] == T2[j])
                    {
                        // recharch la dernier chaine de rifrence de tb de temp est remplacer avec tb de mimoire cache
                        T2[j] = T1[i];
                        miss++;
                    }
                }
            }
        }
        printf("\t\t---etape numero %d---\n", i + 1);
        affich(T2, m);
        printf("\n\miss= %d\n", miss);
        printf("hit= %d\n\n", hit);
    }
}

int main()
{
    // definir les variables
    int tdmc, nbrmot, i, j, miss = 0, hit = 0, choise, st;
    // Lire la ms
    printf("Donnez la taille du memoire cache : ");
    scanf("%d", &tdmc);
    // Lire les mots
    printf("Donnez le Nombre des mots :  ");
    scanf("%d", &nbrmot);
    // lire declation
    int mc[tdmc], mot[nbrmot];
    // remplisser les element
    fil(mc, tdmc);
    // printf("Donnez les mot a utiliser \n");
    read(mot, nbrmot);
    st = 1;
    do
    {
        printf("\n\n\n\n1- FIFO\n2- Aleatoire\n3- LRU\n4- Exit\nVeillez Choisi l'Algorithme a utiliser : ");
        scanf("%d", &choise);
        if (choise == 5)
        {
            st = 0;

            printf("\n==============================================\n||End, Merci Pour Utiliser Mon Program (MMS)||\n==============================================\n");
        }

        switch (choise)
        {
        case 1:
            // system("cls");
            printf("\n\n\nVous avez choisissez FIFO\n\n");
            // printf("Click To Start...");getchar();getchar();
            miss = 0;
            hit = 0;
            j = 0;
            i = 0;
            // Fifo boucle
            while (i < nbrmot)
            {
                if (verif(mc, mot[i], tdmc) == 1)
                {
                    hit++;
                }
                else
                {
                    miss++;
                    mc[j] = mot[i];
                    j++;
                }

                if (j == tdmc)
                {
                    j = 0;
                }
                i++;
                affich(mc, tdmc);
                printf("miss = %d / hit = %d \n\n\n\n\n\n", miss, hit);
            }
            break;
        // aleatoire boucle
        case 2:
            miss = 0;
            hit = 0;
            j = 0;
            i = 0;
            while (i < nbrmot)
            {
                if (verif(mc, mot[i], tdmc) == 1)
                {
                    hit++;
                }
                else
                {
                    miss++;
                    j = (rand() % (tdmc));
                    mc[j] = mot[i];
                }

                i++;
                affich(mc, tdmc);
                printf("miss = %d / hit = %d \n\n\n\n\n\n", miss, hit);
            }
            break;
        // LRU boucle
        case 3:
            lru(mc, mot, tdmc, nbrmot);
            break;
        }

    } while (st == 1);
}
