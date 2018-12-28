
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "couleur_console.h"
#include <time.h>
#include "gestion_clavier.h"
#include "score.h"

// code des chiffre pour le platea
//>= 0 : serpent 1 (tete) >1 corps
//=-1 : case vide  ' '
//=-2 champi+  '+'
//=-3 champi- '~'
//=-4 mur du plateau : 'X'
// 0 est une variable temporaire servant au moivement du serpent


// MACROCONSTANTE
# define TAILLE 15 
// Plateau
# define TETE 1
# define TMP 0
# define VIDE -1
# define CHAMPIPLUS -2
# define CHAMPIMOIN -3
# define MUR -4
//Orientation
# define DROITE 1
# define GAUCHE 2
# define HAUT 3
# define BAS 4

// STRUCTURE

typedef struct
{
	int food_X;
	int food_Y;
}T_food;


//LES PROTOTYPES

void affichage_menue(void);

void affichage_regle(void);

int alea(int a, int b) ;

void initialisation_board (int board [TAILLE][TAILLE]);

void aff_board(int board [TAILLE][TAILLE]);

//int verifier_case_vide( int board[TAILLE][TAILLE],int x,int y) ;
 // a faire : verifier si le snake touche sa qeue ou un bord !

void ballaye_board(int board [TAILLE][TAILLE],int* x, int * y);

void placer_serpent_depart(int board [TAILLE][TAILLE]);

void placer_champi(int board [TAILLE][TAILLE],int champi);


void avance(int board[TAILLE][TAILLE], int *taille);

// LES FONCTION


void affichage_menue(void)
{
	printf(" *** MENUE ***\n\n");
	printf("  1 Jouer @000 \n");
	printf("  2 Voir Score \n");
	printf("  3 voir les regle \n");
	printf("  q JE VEUX QUITTER !\n");
}
void affichage_regle(void)
{
	printf(" \n\n*** Regle ***\n\n");
	printf("* e allez en haut  \n");
	printf("* d allez en bas  \n");
	printf("* f allez à droite \n");
	printf("* s allez à gauche \n");
	printf("* Si tu manges un + ton serpent grandira de 1 \n");
	printf("mais si tu mange un ~ il retrecira de 1 \n");
	printf(" * Si la tete de ton serpent touche un bors \n");
	printf("du plaetau ou sa propre queue tu meurs\n\n\n");
}

int alea(int a, int b) 
{
	srand(time(NULL)); // initialisation de rand
    return rand()%(b-a)+a;
}

void initialisation_board (int board [TAILLE][TAILLE])
{
	
	int i,j;
		
	for(i=1;i<(TAILLE);i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			board [i][j] = VIDE;
		}
	}
	
	for(i=0;i<TAILLE;i++) //premire ligne avec des -4
	{
		board [0][i] = MUR;
	}
	for(i=0;i<TAILLE;i++)// derniere ligne avec des -4
	{
		board [TAILLE-1][i] = MUR;
	}
	for(i=1;i<(TAILLE-1);i++) // premire colonne avec des -4 moins la premiere case et la derniere casse de la colone car deja en -4
	{
		board [i][0] = MUR;
	}
	for(i=1;i<(TAILLE-1);i++) // derniere colonne avec des -4 moins la premiere case et la derniere casse de la colone car deja en -4
	{
		board [i][TAILLE-1] = MUR;
	}
	
	return ;
}


void aff_board(int board [TAILLE][TAILLE])
{
	
	int i,j;
	
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			texte_effet(GRAS);	
			if (board [i][j]==MUR)
			{
				couleur_texte(MAGENTA);
				printf("X ");
				couleur_reset();
			}
			if (board [i][j]== VIDE)
			{
				printf("  ");	
			}
			if (board [i][j]== CHAMPIPLUS)
			{
				couleur_texte(CYAN);
				printf("+ ");
				couleur_reset();
			}
			if (board [i][j]== CHAMPIMOIN)
			{
				couleur_texte(JAUNE);
				printf("~ ");
				couleur_reset();
			}
			if (board [i][j]==TETE)
			{
				couleur_texte(VERT);
				printf("@ ");
				couleur_reset();
			}
			if (board [i][j]>TETE)
			{
				couleur_texte(BLANC);
				printf("0 ");
				couleur_reset();
			}
		}
		printf("\n");
	}
	
	return;
}


void placer_serpent_depart(int board [TAILLE][TAILLE])
{
	int valid =0, X, Y;
	
	do 
	{
		// Initialisation aleatoire de la position initial X et Y de la tete du serpent
		X=alea(1,TAILLE-5);
		Y=alea(1,TAILLE-5);
		// verification que la case est bien vide
		valid=board [X][Y];
	}while(valid!=VIDE);
	board [X][Y]=1;
	
	return ;
}
void placer_champi(int board [TAILLE][TAILLE], int champi)
{
	int effet= champi;
	int valid=0;
	T_food food;
	
	do 
	{
		// Initialisation aleatoire de la position X et Y de la nourriture
		food.food_X=alea(1,TAILLE-1);
		food.food_Y=alea(1,TAILLE-1);
		// verivication que la case est bien vide
		valid=board [food.food_X][food.food_Y];
	}while(valid!=VIDE);
		
	if (effet==CHAMPIPLUS)
	{
		board [food.food_X][food.food_Y]= CHAMPIPLUS;
	}
	if (effet==CHAMPIMOIN)
	{
		board [food.food_X][food.food_Y]=CHAMPIMOIN;
	}
}
void cherche_tete(int board[TAILLE][TAILLE],int* x, int * y)
{
	int i, j ;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			if (  board[i][j]== 1) // la tete
			{
				*x = i;
				*y = j;
				return ;
			}
		}
	}
	return ;
}

void cherche_champi(int board[TAILLE][TAILLE],int* nb_plus, int *nb_moins)
{
	int i, j ;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			if (  board[i][j]== CHAMPIPLUS) // la tete
			{
				*nb_plus=*nb_plus +1;
			}
			if (  board[i][j]== CHAMPIMOIN) // la tete
			{
				*nb_moins=*nb_moins +1;
			}
		}
	}
	return ;
}

int mouvement (int board[TAILLE][TAILLE], int * t, int orientation)
{
	int X=0, Y=0, i ,j, valid;
	
	int * ptrx=&X;
	int * ptry=&Y;
	cherche_tete(board,ptrx,ptry);
	if (orientation==HAUT)
		X=X-1;
	if (orientation==BAS)
		X=X+1;
	if (orientation==GAUCHE)
		Y=Y-1;
	if (orientation==DROITE)
		Y=Y+1;
	
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
		
			
			valid=board[X][Y];
			

			if( valid == VIDE)
			{
				board[X][Y]= TMP;
				avance(board, t);
				return 0;
			}
			else if ((valid == MUR)||( valid > 0))
			{
				printf("GAME OVER\n");
				return 1;
			}
			else if ( valid == CHAMPIPLUS)
			{
				board[X][Y]= TMP;
				*t=*t+1;  // serpent grandi
				avance (board, t);
				return 0;
			}
			else // champimoins
			{
				if ( *t ==1)
				return 1;
				
				board[X][Y]= TMP;
				*t=*t-1; // serpent retrecit
				avance (board, t);
				return 0;
			}
		}
	}
	return 0;
}

void avance(int board[TAILLE][TAILLE], int  *taille)
{
	int i, j;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			if(( board[i][j] > VIDE) )
			{
				board[i][j]=board[i][j]+1;
			}
			if ((board[i][j] > *taille))
			{
				board[i][j] = VIDE;
			}
		}
	}
	return;
}


// MAIN


int main(void)
{
	char key='t';
	int taille_serpent, orientation= HAUT, mort =0;
	int * taille_s = &taille_serpent;
	char pseudo [10];
	LISTE_SCORE* liste_score = (LISTE_SCORE*)malloc(sizeof(LISTE_SCORE));
	liste_score->premier = NULL;
	
	char choix;
	int plateau[TAILLE][TAILLE];
	
	
	initialisation_board(plateau);
	placer_serpent_depart(plateau);

	
	
	do
	{
	
	affichage_menue();
	printf("\nvotre choix : ");
	scanf(" %c", &choix);

	if(choix == '1')
	{
		initialisation_board(plateau);
		placer_serpent_depart(plateau);
		taille_serpent=1;
		printf(" PSEUDO : ");
		scanf(" %s",pseudo);
		printf("\n\n");
		printf("\n\n\njoue\n\n\n");
		aff_board(plateau);

		do{
			key = pressing_key();
			int nb_champiplus=0, nb_champimoin=0;
			cherche_champi(plateau,&nb_champiplus, &nb_champimoin);
			//printf("Champ+ = %d , Champ- = %d\n",nb_champiplus,nb_champimoin);
			if (nb_champiplus<5)
				placer_champi(plateau, CHAMPIPLUS);
			if (nb_champimoin<2)
				placer_champi(plateau,CHAMPIMOIN);
		
			if (key == 'e')
				orientation=HAUT;
			if (key == 'd')
				orientation=BAS;
			if (key == 'f')
				orientation=DROITE;
			if (key == 's')
				orientation=GAUCHE;
		
			mort = mouvement (plateau,taille_s,orientation);
			aff_board(plateau);	

	
		}while( (key != 'q') && (mort != 1) );
		
		//Ajout (eventuel) du score

		SCORE* score = (SCORE*)malloc(sizeof(SCORE));

		score->taille_serpent = *taille_s;
		strcpy(score->pseudo,pseudo);

		ajoute_score(liste_score, score);

		
	}
	else if (choix == '2') // score
	{
		//
		aff_liste(liste_score);
	}
	else if(choix == '3') // regle
	{
		affichage_regle();
	}
	
	
	
	
	}while(choix!='q');
	
	printf("##\nle programme est terminé.\n");
	return 0;
}

