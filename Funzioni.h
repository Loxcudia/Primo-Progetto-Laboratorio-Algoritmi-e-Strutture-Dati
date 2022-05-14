#include <stdio.h>

typedef struct Utente
{
	char nickname[1000];
	char password[1000];
	double saldo;
	struct Utente* next;
}Utente;

typedef struct Admin
{
	char nickname[1000];
	char password[1000];
	struct Admin* next;
}Admin;

typedef struct ListaDiAttesa
{
	char nickname[1000];
	char nomeProdotto[1000];
	char taglia[5];
	struct ListaDiAttesa* next;
}ListaDiAttesa;

typedef struct	CapiDiAbbigliamento //organizzati secondo Alberi Binari di Ricerca
{
	char marca[1000];
	char nome[1000];
	double prezzo;
	int quantita;
	char taglia[20][5];
	struct CapiDiAbbigliamento* left;
	struct CapiDiAbbigliamento* right;
}CapiDiAbbigliamento;

void menu(Utente *head, CapiDiAbbigliamento *radice, ListaDiAttesa *L, Admin *A);
Utente* creaNodo(char str[], char str2[]);
Utente* addUtente(Utente* head);
void login(Utente *head, CapiDiAbbigliamento *radice, ListaDiAttesa* L, Admin *A);
void toLower(char str[]);
Utente* standardizzazioneUtenti(Utente* head);
void visualizzaUtenti(Utente* head);
Utente* ricercaUtente(Utente *head, char nick[], char pass[]);
void ricaricaContoUtente(Utente* u);
void svuotaContoUtente(Utente* u);
void acquistaProdotto(CapiDiAbbigliamento* p);
CapiDiAbbigliamento* standardizzazioneCapiDiAbbigliamento(CapiDiAbbigliamento *radice);
void insertABRPerStandardizzazioneProgramma(CapiDiAbbigliamento** radice, char marca[], char nome[], double prezzo, int quantita, char* taglia[]);
void insertABR(CapiDiAbbigliamento** radice, char marca[], char nome[], double prezzo, int quantita, char* taglia[]);
void preorderVisit(CapiDiAbbigliamento* radice);
void postorderVisit(CapiDiAbbigliamento* radice);
void inorderVisit(CapiDiAbbigliamento* radice);
CapiDiAbbigliamento* cancellaProdotto(CapiDiAbbigliamento* radice, char nome[]);
CapiDiAbbigliamento* ricercaMinimoABR(CapiDiAbbigliamento* radice);
CapiDiAbbigliamento* ricercaABR(CapiDiAbbigliamento* radice, char nome[]);
void acquista(CapiDiAbbigliamento *radice, Utente *head, ListaDiAttesa *L);
int ricercaTagliaProdotto(CapiDiAbbigliamento *radice, char taglia[]);
ListaDiAttesa* insertListaDiAttesa(ListaDiAttesa* head, char nickname[]);
ListaDiAttesa* creaNodoListaDiAttesa(char nickname[]);
Admin* standardizzazioneAdmin(Admin *head);
Admin* creaNodoAdmin(char nickname[], char password[]);
Admin* ricercaAdmin(Admin *head, char nickname[], char password[]);
Utente* eliminaUtente(Utente* head);
CapiDiAbbigliamento* addProdotto(CapiDiAbbigliamento *radice);
void liberaAlberoBinario(CapiDiAbbigliamento *radice);
void liberaUtenti(Utente* head);
void liberaAdmin(Admin* head);
void liberaListaDiAttesa(ListaDiAttesa* head);