



typedef struct maillon
{
	int taille_serpent;
	char pseudo[10];
	struct maillon * suivant;
}SCORE;

typedef struct
{
		SCORE *premier;
} LISTE_SCORE;


void aff_liste(LISTE_SCORE * liste);
void ajoute_score (LISTE_SCORE * liste_score,SCORE *nv_score_elt);
void libere_liste(LISTE_SCORE * liste);
void lire_score(LISTE_SCORE * liste);
void ecrire_score(LISTE_SCORE * liste);
