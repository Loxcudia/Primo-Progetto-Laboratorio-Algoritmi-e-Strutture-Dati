#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Funzioni.h"
#define _CRT_SECURE_NO_WARNINGS
void toLower(char str[])
{
	for (int i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

Utente* creaNodo(char str[], char str2[])
{
	Utente* nuovoNodo = (Utente*)malloc(sizeof(Utente));
	if (nuovoNodo)
	{
		strcpy(nuovoNodo->nickname, str);
		strcpy(nuovoNodo->password, str2);
		nuovoNodo->saldo = 0;
		nuovoNodo->next = NULL;
	}
	return nuovoNodo;
}

Admin* creaNodoAdmin(char nickname[], char password[])
{
	Admin* nuovoNodo = (Admin*)malloc(sizeof(Admin));
	if (nuovoNodo)
	{
		strcpy(nuovoNodo->nickname, nickname);
		strcpy(nuovoNodo->password, password);
		nuovoNodo->next = NULL;
	}
	return nuovoNodo;
}

ListaDiAttesa* creaNodoListaDiAttesa(char nickname[], char nomeprodotto[], char taglia[])
{
	ListaDiAttesa* nuovoNodo = (ListaDiAttesa*)malloc(sizeof(ListaDiAttesa));
	if (nuovoNodo)
	{
		strcpy(nuovoNodo->nickname, nickname);
		strcpy(nuovoNodo->nomeProdotto, nomeprodotto);
		strcpy(nuovoNodo->taglia, taglia);
		nuovoNodo->next = NULL;
	}
	return nuovoNodo;
}

Utente* addUtente(Utente* head)
{
	char nick[1000];
	char password[1000];
	printf("Inserisci nickname:\n");
	scanf("%s", &nick);
	printf("Inserisci password:\n");
	scanf("%s", &password);
	Utente* nuovo = creaNodo(nick, password);
	if (head && nuovo)
	{
		Utente* curr = head;
		while (curr->next)
			curr = curr->next;
		curr->next = nuovo;
		return head;
	}
	else
		return nuovo;
}

Utente* standardizzazioneUtenti(Utente* head)
{
	char nicknames[5][1000] = { "Cloud", "Kirby", "Giantrix", "Bomber99", "Boh" };
	char passwords[5][1000] = { "123", "456", "789" ,"987", "654" };
	for (int i = 0; i < 5; i++)
	{
		Utente* nuovo = creaNodo(nicknames[i], passwords[i]);
		if (!head && nuovo)
		{
			head = nuovo;
		}
		else
		{
			Utente* curr = head;
			while (curr->next)
				curr = curr->next;
			curr->next = nuovo;
		}
	}
	return head;
}

void visualizzaUtenti(Utente* head)
{
	Utente* tmp = head;
	while (tmp)
	{
		printf("Nickname: %s, ", tmp->nickname);
		printf("Saldo: %g\n", tmp->saldo);
		tmp = tmp->next;
	}
}

Utente* ricercaUtente(Utente* head, char nick[], char pass[])
{
	Utente* tmp = head;
	while (tmp)
	{
		if ( (strcmp(tmp->nickname, nick) == 0) && (strcmp(tmp->password, pass) == 0) )
			return tmp;
		else
			tmp = tmp->next;
	}
	return NULL;
}

void ricaricaContoUtente(Utente* u)
{
	double x;
	do
	{
		printf("Quanto vuoi ricaricare?\n");
		scanf("%lf", &x);
		u->saldo = u->saldo + x;
		if (x <= 0)
			printf("Errore, inserisci un valore maggiore di 0\n");
	}
	while (x <= 0);
	printf("Ricarica effettuata, nuovo saldo: %lf\n", u->saldo);
}

void svuotaContoUtente(Utente* u)
{
	if (u->saldo == 0)
	{
		printf("Conto gia vuoto \n");
		return;
	}
	u->saldo = 0;
	printf("Conto svuotato, nuovo saldo: %lf\n");
}

void insertABRPerStandardizzazioneProgramma(CapiDiAbbigliamento** radice, char marca[], char nome[], double prezzo, int quantita, char *taglia[])
{
	int i = 0;
	static int j = 0;
	if (*radice == NULL)
	{
		CapiDiAbbigliamento* nuovoNodo = (CapiDiAbbigliamento*)malloc(sizeof(CapiDiAbbigliamento));
		if (nuovoNodo)
		{
			strcpy(nuovoNodo->marca, marca);
			strcpy(nuovoNodo->nome, nome);
			nuovoNodo->quantita = quantita;
			nuovoNodo->prezzo = prezzo;
			strcpy(nuovoNodo->taglia[i++], taglia[j++]);
			nuovoNodo->left = NULL;
			nuovoNodo->right = NULL;
			*radice = nuovoNodo;
		}
	}
	else if (strcmp((*radice)->nome, nome) > 0)
		insertABRPerStandardizzazioneProgramma(&(*radice)->left, marca, nome, prezzo, quantita, taglia);
	else if (strcmp((*radice)->nome, nome) < 0)
		insertABRPerStandardizzazioneProgramma(&(*radice)->right, marca, nome, prezzo, quantita, taglia);
}

void insertABR(CapiDiAbbigliamento** radice, char marca[], char nome[], double prezzo, int quantita, char* taglia[])
{
	if (*radice == NULL)
	{
		CapiDiAbbigliamento* nuovoNodo = (CapiDiAbbigliamento*)malloc(sizeof(CapiDiAbbigliamento));
		if (nuovoNodo)
		{
			strcpy(nuovoNodo->marca, marca);
			strcpy(nuovoNodo->nome, nome);
			nuovoNodo->quantita = quantita;
			nuovoNodo->prezzo = prezzo;
			for (int i = 0; i < 20; i++)
			{
				if (strcmp(taglia[i], "") == 0)
					break;
				strcpy(nuovoNodo->taglia[i], taglia[i]);
			}
			nuovoNodo->left = NULL;
			nuovoNodo->right = NULL;
			*radice = nuovoNodo;
		}
	}
	else if (strcmp((*radice)->nome, nome) > 0)
		insertABR(&(*radice)->left, marca, nome, prezzo, quantita, taglia);
	else if (strcmp((*radice)->nome, nome) < 0)
		insertABR(&(*radice)->right, marca, nome, prezzo, quantita, taglia);
}

CapiDiAbbigliamento* standardizzazioneCapiDiAbbigliamento(CapiDiAbbigliamento* radice)
{
	char taglie2[20][5] = { "L", "XXL", "M", "XS", "S" };
	char marche[5][1000] = { "Nike", "Adidas", "Puma", "Kappa", "Givova" };
	char nomi[5][1000] = { "AirForce", "Maglia", "Berretto", "Polo", "Tuta" };
	int quantita[5] = { 5,10,15,20,0 };
	double prezzi[5] = { 500,400,300,200,100 };
	char** taglie = (char**)malloc(20 * sizeof(char*));
	for (int i = 0; i < 20; i++) taglie[i] = (char*)malloc(5 * sizeof(char));
	for (int i = 0; i < 20; i++) strcpy(taglie[i], taglie2[i]);
	for (int i = 0; i < 5; i++)
		insertABRPerStandardizzazioneProgramma(&radice, marche[i], nomi[i], prezzi[i], quantita[i], taglie);
	return radice;
}
void preorderVisit(CapiDiAbbigliamento* radice)
{
	if (radice)
	{
		printf("Nome: %s\n", radice->nome);
		printf("Marca: %s\n", radice->marca);
		printf("Prezzo: %lf\n", radice->prezzo);
		printf("Quantita: %d\n", radice->quantita);
		printf("Taglie: \n");
		for (int i = 0; i < 20; i++)
		{
			if ( strcmp(radice->taglia[i], "") == 0)
				break;
			printf("%s, ", radice->taglia[i]);
		}
		printf("\n");
		preorderVisit(radice->left);
		preorderVisit(radice->right);
	}
}

void postorderVisit(CapiDiAbbigliamento* radice)
{
	if (radice)
	{
		postorderVisit(radice->left);
		postorderVisit(radice->right);
		printf("Nome: %s\n", radice->nome);
		printf("Marca: %s\n", radice->marca);
		printf("Prezzo: %lf\n", radice->prezzo);
		printf("Quantita: %d\n", radice->quantita);
		printf("Taglie: \n");
		for (int i = 0; i < 20; i++)
		{
			if (strcmp(radice->taglia[i], "") == 0)
				break;
			printf("%s, ", radice->taglia[i]);
		}
		printf("\n");
	}
}

void inorderVisit(CapiDiAbbigliamento* radice)
{
	postorderVisit(radice->left);
	printf("Nome: %s\n", radice->nome);
	printf("Marca: %s\n", radice->marca);
	printf("Prezzo: %lf\n", radice->prezzo);
	printf("Quantita: %d\n", radice->quantita);
	printf("Taglie: \n");
	for (int i = 0; i < 20; i++)
	{
		if (strcmp(radice->taglia[i], "") == 0)
			break;
		printf("%s, ", radice->taglia[i]);
	}
	printf("\n");
	postorderVisit(radice->right);
}

CapiDiAbbigliamento* ricercaMinimoABR(CapiDiAbbigliamento* radice)
{
	CapiDiAbbigliamento* min = NULL;
	if (radice)
	{
		if (!radice->left)
			min = radice;
		else
			min = ricercaMinimoABR(radice->left);
	}
	return min;
}

CapiDiAbbigliamento* cancellaProdotto(CapiDiAbbigliamento* radice, char nome[])
{
	if (radice == NULL)
		return radice;
	if (strcmp(nome, radice->nome) < 0)
		radice->left = cancellaProdotto(radice->left, nome);
	else if (strcmp(nome, radice->nome) > 0)
		radice->right = cancellaProdotto(radice->right, nome);
	else
	{
		if (radice->left == NULL)
		{
			CapiDiAbbigliamento* tmp = radice->right;
			free(radice);
			return tmp;
		}
		else if (radice->right == NULL)
		{
			CapiDiAbbigliamento* tmp = radice->left;
			free(radice);
			return tmp;
		}
		CapiDiAbbigliamento* tmp = ricercaMinimoABR(radice->right);
		strcpy(radice->nome, tmp->nome);
		radice->right = cancellaProdotto(radice->right, tmp->nome);
	}
	return radice;
}

CapiDiAbbigliamento* ricercaABR(CapiDiAbbigliamento* radice, char nome[])
{
	if (!radice)
		return radice;
	toLower(nome);
	char tmp[1000];
	strcpy(tmp, radice->nome);
	toLower(tmp);
	if (strcmp(tmp, nome) == 0)
		return radice;
	if (strcmp(tmp, nome) < 0)
		return ricercaABR(radice->right, nome);
	return ricercaABR(radice->left, nome);
}

int ricercaTagliaProdotto(CapiDiAbbigliamento* radice, char taglia[])
{
	char tmp[5];
	toLower(taglia);
	for (int i = 0; i < 20; i++)
	{
		//if (strcmp(radice->taglia[i], "") == 0)
			//break;
		strcpy(tmp, radice->taglia[i]);
		toLower(tmp);
		if (strcmp(tmp, taglia) == 0)
			return 1;
	}
	return 0;
}

ListaDiAttesa* insertListaDiAttesa(ListaDiAttesa* head, char nickname[], char nomeprodotto[], char taglia[])
{
	ListaDiAttesa* nuovo = creaNodoListaDiAttesa(nickname, nomeprodotto, taglia);
	if (head && nuovo)
	{
		ListaDiAttesa* curr = head;
		while (curr->next)
			curr = curr->next;
		curr->next = nuovo;
		return head;
	}
	else
		return nuovo;
}

void acquista(CapiDiAbbigliamento* radice, Utente *head, ListaDiAttesa* L)
{
	char nomeprodotto[1000];
	char scelta[5];
	char sceltataglia[5];
	CapiDiAbbigliamento* prodotto = NULL;
	printf("Scrivi il nome del prodotto che vorresti cercare e/o acquistare:\n");
	do
	{
		scanf("%s", &nomeprodotto);
		prodotto = ricercaABR(radice, nomeprodotto);
		if (!prodotto)
			printf("Prodotto non trovato, riprova\n");
	} while (prodotto == NULL);
	printf("Prodotto trovato: %s, %s, prezzo: %lf \n", prodotto->nome, prodotto->marca, prodotto->prezzo);
	printf("Quale taglia desideri? (Ad esempio S, M, L, XL ecc...)\n");
	do
	{
		scanf("%s", &sceltataglia);
		toLower(sceltataglia);
		if (ricercaTagliaProdotto(prodotto, sceltataglia) == 0)
			printf("Taglia non esistente, riprova.\n");
	} while (ricercaTagliaProdotto(prodotto, sceltataglia) == 0);
	printf("Vuoi acquistare questo prodotto?\n(Digita si o no)\n");
	do
	{
		scanf("%s", &scelta);
		toLower(scelta);
		if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
			printf("Errore di inserimento, ricorda di digitare si o no\n");
		if (strcmp(scelta, "no") == 0)
		{
			printf("Vuoi acquistare altro?\n");
			scanf("%s", &scelta);
			toLower(scelta);
			if (strcmp(scelta, "no") == 0)
			{
				printf("Arrivederci!\n");
				return;
			}
			else if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
				acquista(radice, head, L);
		}
	} while ( (strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0) );
	if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
	{
		if (prodotto->quantita == 0)
		{
			char scelta[5];
			printf("Quantita finite. vuoi metterti in lista da attesa per questo prodotto?\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
					printf("Errore di inserimento, ricorda di digitare si o no\n");
			} while ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0));
			if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
			{
				insertListaDiAttesa(L, head->nickname, prodotto->nome, sceltataglia);
				printf("Inserito/a in lista di attesa!\n");
			}
			printf("Vuoi continuare ad acquistare?\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
					printf("Errore di inserimento, ricorda di digitare si o no\n");
			} while ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0));
			if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
				acquista(radice, head, L);
			else
			{
				printf("Arrivederci\n");
				return;
			}
		}
		if (head->saldo >= prodotto->prezzo)
		{
			head->saldo = head->saldo - prodotto->prezzo;
			prodotto->quantita--;
			printf("Prodotto acquistato! Saldo corrente: %lf\n", head->saldo);
			char scelta[5];
			printf("Vuoi continuare ad acquistare?\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
					printf("Errore di inserimento, ricorda di digitare si o no\n");
			} while ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0));
			if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
				acquista(radice, head, L);
			else
			{
				printf("Arrivederci\n");
				return;
			}
		}
		else
		{
			char scelta[5];
			printf("Saldo insufficiente, vuoi effettuare una ricarica?\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
					printf("Errore di inserimento, ricorda di digitare si o no\n");
			} while ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0));
			if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
			{
				do
				{
					ricaricaContoUtente(head);
					if (head->saldo < prodotto->prezzo)
						printf("\nNon hai caricato abbastanza soldi, ricarica di nuovo!\n");
				} while (head->saldo < prodotto->prezzo);
				printf("Prodotto acquistato.\n");
				printf("Vuoi continuare ad acquistare?\n");
				do
				{
					scanf("%s", &scelta);
					toLower(scelta);
					if ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0))
						printf("Errore di inserimento, ricorda di digitare si o no\n");
				} while ((strcmp(scelta, "si") != 0) && (strcmp(scelta, "sì") != 0) && (strcmp(scelta, "no") != 0));
				if ((strcmp(scelta, "si") == 0) || (strcmp(scelta, "sì") == 0))
					acquista(radice, head, L);
				else
				{
					printf("Arrivederci\n");
					return;
				}
			}
		}
		
	}
}

Admin* standardizzazioneAdmin(Admin* head)
{
	char nicknames[3][1000] = { "admin", "admin2", "admin3"};
	char passwords[3][1000] = { "admin", "admin2", "admin3"};
	for (int i = 0; i < 5; i++)
	{
		Admin* nuovo = creaNodoAdmin(nicknames[i], passwords[i]);
		if (!head && nuovo)
		{
			head = nuovo;
		}
		else
		{
			Admin* curr = head;
			while (curr->next)
				curr = curr->next;
			curr->next = nuovo;
		}
	}
	return head;
}

Admin* ricercaAdmin(Admin* head, char nickname[], char password[])
{
	Admin* tmp = head;
	while (tmp)
	{
		if ((strcmp(tmp->nickname, nickname) == 0) && (strcmp(tmp->password, password) == 0))
			return tmp;
		else
			tmp = tmp->next;
	}
	return NULL;
}

Utente* eliminaUtente(Utente* head)
{
	char nickname[1000];
	Utente* temp = head;
	Utente* prev = NULL;
	printf("Inserisci il nickname dell'utente da eliminare:\n");
	scanf("%s", &nickname);
	while (temp)
	{
		if (strcmp(temp->nickname, nickname) == 0)
		{
			if (prev == NULL) { 
				head = head->next;
				free(temp);
				printf("Utente eliminato.\n");
				return head;
			}
			else {
				prev->next = temp->next;
				free(temp);
				printf("Utente eliminato.\n");
				return head;
			}
		}
		prev = temp;
		temp = temp->next;
	}
	return head;
}

CapiDiAbbigliamento* addProdotto(CapiDiAbbigliamento* radice)
{
	char nome[1000];
	char marca[1000];
	int quantita;
	double prezzo;
	int ntaglie;
	char** taglie = (char**)malloc(20 * sizeof(char*));
	for (int i = 0; i < 20; i++) taglie[i] = (char*)malloc(5 * sizeof(char));
	for (int i = 0; i < 20; i++) strcpy(taglie[i], "");
	printf("Inserisci il nome del nuovo prodotto:\n");
	scanf("%s", &nome);
	printf("Inserisci la marca del nuovo prodotto:\n");
	scanf("%s", &marca);
	printf("Inserisci il numero di taglie che vuoi rendere disponibili:\n");
	scanf("%d", &ntaglie);
	for (int i = 0; i < ntaglie; i++)
	{
		printf("Inserisci taglia: ");
		scanf("%s", taglie[i]);
	}
	do
	{
		printf("\nInserisci la quantita della merce:\n");
		scanf("%d", &quantita);
		if (quantita < 0)
			printf("Errore, inserisci una quantita maggiore di 0\n");
	} while (quantita < 0);
	do
	{
		printf("Inserisci il prezzo:\n");
		scanf("%lf", &prezzo);
		if (prezzo < 0)
			printf("Errore, inserisci un prezzo maggiore di 0\n");
	} while (prezzo < 0);
	insertABR(&radice, marca, nome, prezzo, quantita, taglie);
	return radice;
}

void liberaUtenti(Utente* head)
{
	Utente* tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void liberaAdmin(Admin* head)
{
	Admin* tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void liberaListaDiAttesa(ListaDiAttesa* head)
{
	ListaDiAttesa* tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void login(Utente* head, CapiDiAbbigliamento* radice, ListaDiAttesa *L, Admin *A)
{
	char log[10];
	printf("Benvenuto nel login. Vuoi accedere come utente o come admin?\n(Digita testualmente utente o admin)\n");
	do
	{
		scanf("%s", &log);
		toLower(log);
		if ((strcmp(log, "admin") != 0) && (strcmp(log, "utente") != 0))
			printf("Errore di inserimento, riprova.\n(Ricorda di digitare testualmente utente o admin)\n");
	} while ((strcmp(log, "admin") != 0) && (strcmp(log, "utente") != 0));
	if ((strcmp(log, "admin") == 0))
	{
		char nick[1000];
		char password[1000];
		char scelta[5];
		Admin* a = NULL;
		do
		{
			printf("Inserisci nickname:\n");
			scanf("%s", &nick);
			printf("Inserisci password:\n");
			scanf("%s", &password);
			a = ricercaAdmin(A, nick, password);
			if (a == NULL)
				printf("Utente non trovato, riprova il login.\n");
		} while (a == NULL);
		do
		{
			printf("\nCosa vuoi fare?\n-Visualizzare i prodotti (digita prodotti)\n-Aggiungere un nuovo capo di abbigliamento (Digita aggiungi)\n-Eliminare un capo di abbigliamento (Digita elimina)\n-Visualizzare gli utenti iscritti al sistema (Digita utenti)\n-Eliminare un utente dal sistema (digita banna)\n-Ritorna al login (digita exit)\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if (strcmp(scelta, "exit") == 0)
					login(head, radice, L, A);
				if ((strcmp(scelta, "aggiungi") != 0) && (strcmp(scelta, "elimina") != 0) && (strcmp(scelta, "utenti") != 0) && (strcmp(scelta, "banna") != 0) && (strcmp(scelta, "prodotti") != 0))
					printf("Errore di inserimento, riprova\n");
			} while ((strcmp(scelta, "aggiungi") != 0) && (strcmp(scelta, "elimina") != 0) && (strcmp(scelta, "utenti") != 0) && (strcmp(scelta, "banna") != 0) && (strcmp(scelta, "exit") != 0) && (strcmp(scelta, "prodotti") != 0));
			if (strcmp(scelta, "utenti") == 0)
				visualizzaUtenti(head);
			if (strcmp(scelta, "banna") == 0)
				head = eliminaUtente(head);
			if (strcmp(scelta, "elimina") == 0)
			{
				char nome[1000];
				CapiDiAbbigliamento* p = NULL;
				printf("Inserisci il nome del prodotto da eliminare\n");
				scanf("%s", &nome);
				p = ricercaABR(radice, nome);
				if (!p)
					printf("Prodotto non esistente.\n");
				else
					radice = cancellaProdotto(radice, p->nome);
			}
			if (strcmp(scelta, "prodotti") == 0)
				inorderVisit(radice);
			if (strcmp(scelta, "aggiungi") == 0)
				radice = addProdotto(radice);
		} while (strcmp(scelta, "exit") != 0);
	}
	else if (strcmp(log, "utente") == 0)
	{
		char nick[1000];
		char password[1000];
		char scelta[20];
		Utente* u = NULL;
		do
		{
			printf("Inserisci nickname:\n");
			scanf("%s", &nick);
			printf("Inserisci password:\n");
			scanf("%s", &password);
			u = ricercaUtente(head, nick, password);
			if (u == NULL)
				printf("Utente non trovato, riprova il login.\n");
		} while (u == NULL);
		do
		{
			printf("\nCosa vuoi fare?\n-Ricaricare conto virtuale (Digita ricarica)\n-Svuotare conto virtuale (Digita svuota)\n-Cercare e acquistare prodotto (Digita acquista)\n-Per tornare al login digita exit\n");
			do
			{
				scanf("%s", &scelta);
				toLower(scelta);
				if (strcmp(scelta, "exit") == 0)
					login(head, radice, L, A);
				if ((strcmp(scelta, "ricarica") != 0) && (strcmp(scelta, "svuota") != 0) && (strcmp(scelta, "acquista") != 0))
					printf("Errore di inserimento, riprova.\n(Ricorda di digitare testualmente: ricarica, svuota o acquista)\n");
			} while ((strcmp(scelta, "ricarica") != 0) && (strcmp(scelta, "svuota") != 0) && (strcmp(scelta, "acquista") != 0) && (strcmp(scelta, "exit") != 0) );
			if (strcmp(scelta, "ricarica") == 0)
				ricaricaContoUtente(u);
			else if (strcmp(scelta, "svuota") == 0)
				svuotaContoUtente(u);
			else if (strcmp(scelta, "acquista") == 0)
				acquista(radice, head, L);
		} while (strcmp(scelta, "exit") != 0);
	}



}

void menu(Utente* head, CapiDiAbbigliamento *radice, ListaDiAttesa *L, Admin *A)
{
	char log[10] = {};
	printf("Benvenuto! Vuoi fare il login o registrarti?\n(Digita testualmente login o registrazione)\n");
	do
	{
		scanf("%s", &log);
		toLower(log);
		if ( (strcmp(log, "login") != 0) && (strcmp(log, "registrazione") != 0))
		{
			printf("Errore di inserimento, riprova.\n(Ricorda di digitare testualmente login o registrazione)\n");
		}
	} while ( (strcmp(log, "login") != 0) && (strcmp(log, "registrazione") != 0) );
	if (strcmp(log, "login") == 0)
		login(head, radice, L, A);
	else if (strcmp(log, "registrazione") == 0)
	{
		char s[10] = "si";
		printf("Benvenuto alla registrazione di un nuovo utente!\n");
		head = addUtente(head);
		do
		{
			printf("\nRegistrazione effettuata. Vuoi effettuare il login?\n(Digita si/no)\n");
			scanf(" %s", s);
			toLower(s);
			if( (strcmp(s, "si") != 0) && (strcmp(s, "sì") != 0) && (strcmp(s, "no") != 0))
				printf("Errore! Digita si/no");
		} while ( (strcmp(s, "si") != 0) && (strcmp(s, "sì") != 0) && (strcmp(s, "no") != 0) );
		if ((strcmp(s, "si") == 0) || (strcmp(s, "sì") == 0))
		{
			login(head, radice, L, A);
		}
			
	}
}

void liberaAlberoBinario(CapiDiAbbigliamento* radice)
{
	if (!radice)
		return;
	liberaAlberoBinario(radice->right);
	liberaAlberoBinario(radice->left);
	free(radice);
}