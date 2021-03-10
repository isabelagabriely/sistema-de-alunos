#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//   registro dos alunos
typedef struct {
  int ra;
  char nome[50];
  int idade;
  char curso[20];
} REGISTRO;

//   elementos
typedef struct aux {
  REGISTRO *aluno;
  struct aux *prox;
} ELEMENTO;

//   lista
typedef struct {
  ELEMENTO *inicio;
} LISTA;

//   funcoes
void menu ();
void inicializarLista (LISTA *l);

int inserirAluno (LISTA *l);
REGISTRO* buscarAluno (LISTA *l, int RA);
int quantidadeAlunos (LISTA *l);
REGISTRO* excluirAluno (LISTA *l, int RA);
int excluirAlunos (LISTA *l, char curso[], ELEMENTO *apagar);
void listarAlunos (LISTA *l);
void listarCurso (LISTA *l, char curso[]);
int salvarArquivo (LISTA *l);
void lerArquivo ();
int ordenarLista (LISTA *l, int sinaliza);


int main () {

  LISTA l;
  inicializarLista (&l);
  int sinaliza = -1;

	while (1) {
	  menu ();
	
	  int x;
	  printf ("O que vamos fazer?\n");
	  scanf ("%d", &x);
	  
	  while (x<=0 || x>11) {
	  	printf ("\n:(\nVoce nao inseriu um valor valido.\nDigite novamente\n");
	  	scanf ("%d", &x);
	  }
	
	// Inserir um novo aluno. A insercao deve ser feita na ordem do RA.
	  if (x == 1) {
	    system("cls");
	    if (inserirAluno (&l) == 1)
	    	printf (":)\n\n");
	  }
	
	// Pesquisar um aluno pelo RA.
	  else if (x == 2) {
	    system("cls");
	    int RA;
	    printf ("Digite o RA: ");
	    scanf ("%d", &RA);
	    REGISTRO *resposta = buscarAluno (&l, RA);
	    
	    if (resposta == NULL) 
	    	printf (":(\nNao encontramos aluno com esse RA\n\n");
	    else 
	    printf ("%-6d %-10s %-6d %-10s\n\n", resposta->ra, resposta->nome, resposta->idade, resposta->curso);
	  }
	
	// Dizer quantos alunos estao cadastrados.
	  else if (x == 3) {
	    system("cls");
	    printf ("%d alunos registrados no sistema :)\n\n", quantidadeAlunos (&l));
	  }
	
	// Excluir um aluno.
	  else if (x == 4) {
	  	system("cls");
	    int RA;
	    printf ("Digite o RA: ");
	    scanf ("%d", &RA);
	    REGISTRO *resposta = excluirAluno (&l, RA);
	    
	    if (resposta == NULL) 
	    	printf (":(\nNao encontramos aluno com esse RA\n\n");
	    else 
	    printf ("%-6d %-10s %-6d %-10s\nnao esta mais conosco :(\n\n", resposta->ra, resposta->nome, resposta->idade, resposta->curso);
	  }
	
	// Excluir todos os alunos de um curso.
	  else if (x == 5) {
	    system("cls");
	    char curso[20];
	    printf ("Digite o curso: ");
	    scanf ("%s", curso);
	    ELEMENTO *apagar = (ELEMENTO*) malloc (sizeof(ELEMENTO));
	    if (excluirAlunos (&l, curso, apagar) == -1)
	    	printf (":(\nNao encontramos alunos registrado nesse curso\n\n");
	    	
	    else
	    	printf ("Nao ha mais alunos registrados nesse curso\n\n");
	    
	  }
	
	// Listar todos os alunos.
	  else if (x == 6) {
	    system("cls");
	    listarAlunos (&l);
	    printf ("\n");
	  }
	
	// Listar todos os alunos que pertencem a determinado curso.
	  else if (x == 7) {
	    system("cls");
	    char curso[20];
	    printf ("Digite o curso: ");
	    scanf ("%s", curso);
	    listarCurso (&l, curso);
	    printf ("\n");
	  }
	
	// Salvar os dados para um arquivo.
	  else if (x == 8) {
	    system("cls");
	    if (salvarArquivo (&l) == 1)
	    	printf (":)\n\n");
	  }
	
	// Ler os dados de um arquivo.
	  else if (x == 9) {
	    system("cls");
	    lerArquivo ();
	    printf ("\n");
	  }
	
	// Permitir a reordenacao na ordem do nome.
	  else if (x == 10) {
		if (sinaliza == 0)
			printf ("A lista de alunos já está ordenada pelo nome.\n\n");
		
		else if (sinaliza == 1 || sinaliza == -1)
	    	ordenarLista (&l, sinaliza);
	  }
	
	// Permitir a reordenacao na ordem do RA.
	  else if (x == 11) {
		if (sinaliza == 1 || sinaliza == -1)
		  	printf ("A lista de alunos já está ordenada pelo RA.\n\n");

		else if (sinaliza == 0)
	  		ordenarLista (&l, sinaliza);
	  }
	  	
  		int i=0;
	  	while (i!=1) {
	  		
	  		printf("0-SAIR\n");
	  		printf ("1-VOLTAR AO MENU\n");
	  		
  	  		scanf ("%d", &i);
	  
	 	 	if (i==0) {
	 	 		system ("cls");
	 	 		printf ("tchauzinho :)\n");
		  		return;
		  	}
	  		
		  	else if (i!=1){
		  		system ("cls");
		  		if (i>1)
		  			printf ("Voce ta estrapolando, digite um valor valido\n");
		  		else if (i<0)
		  			printf ("Agora voce pegou baixo, digite um valor valido\n");
		  	}
		}
	  system ("cls");	
	}
}

void inicializarLista (LISTA *l) {
  l->inicio = NULL;
}

void menu () {

  printf("\t\t\t\t\t LISTA DE ALUNOS\n\n\n");

  printf ("1. Inserir aluno novo.\n");
  printf ("2. Buscar aluno.\n");
  printf ("3. Acessar quantidade de alunos.\n");
  printf ("4. Excluir aluno.\n");
  printf ("5. Excluir alunos de um curso.\n");
  printf ("6. Listar alunos.\n");
  printf ("7. Listar alunos de um curso.\n\n\n");

  printf ("\tOpcoes de arquivo\n\n");
  printf ("8. Salvar dados em arquivo.\n");
  printf ("9. Ler dados do arquivo.\n\n\n");

  printf ("\tOpcoes de ordenacao\n\n");
  printf ("10. Ordenar por nome.\n");
  printf ("11. Ordenar por RA.\n\n");

}

// Inserir um novo aluno. A insercao deve ser feita na ordem do RA.
int inserirAluno (LISTA *l) {

  REGISTRO *aluno = (REGISTRO*) malloc (sizeof(REGISTRO));
  printf ("RA: ");
  scanf ("%d", &aluno->ra);
  printf ("Nome: ");
  scanf ("%s", aluno->nome);
  printf ("Idade: ");
  scanf ("%d", &aluno->idade);
  printf ("Curso: ");
  scanf ("%s",aluno->curso);

  ELEMENTO *novo = (ELEMENTO*) malloc (sizeof(ELEMENTO));
  novo->aluno = aluno;

  ELEMENTO *anterior = NULL;
  ELEMENTO *posicao = l->inicio;

  while (posicao!= NULL && novo->aluno->ra > posicao->aluno->ra) {
    anterior = posicao;
    posicao = posicao->prox;
  }

  novo->prox = posicao;

  if (anterior == NULL) 
    l->inicio = novo;

  else 
    anterior->prox = novo;

  return 1;
}

// Pesquisar um aluno pelo RA.
REGISTRO* buscarAluno (LISTA *l, int RA) {

  ELEMENTO *posicao = l->inicio;

  while (posicao != NULL && posicao->aluno->ra != RA) 
    posicao = posicao->prox;

  if (posicao != NULL && posicao->aluno->ra == RA)
    return posicao->aluno;

  return NULL;
}

// Dizer quantos alunos estao cadastrados.
int quantidadeAlunos (LISTA *l) {
  
  ELEMENTO *posicao = l->inicio;
  int tamanho = 0;

  while (posicao != NULL) {
    tamanho++;
    posicao = posicao->prox;
  }

  return tamanho;
}

// Excluir um aluno.
REGISTRO* excluirAluno (LISTA *l, int RA) {

  ELEMENTO *anterior = NULL;
  ELEMENTO *posicao = l->inicio;

  REGISTRO *excluido = (REGISTRO*) malloc (sizeof (REGISTRO));

  while (posicao != NULL && posicao->aluno->ra != RA) {
  	anterior = posicao;
    posicao = posicao->prox;
  }

  if (posicao != NULL && posicao->aluno->ra == RA) {
    excluido = posicao->aluno;

    if (anterior == NULL)
      l->inicio = posicao->prox;

    else
      anterior->prox = posicao->prox;

    free(posicao);

    return excluido;
  }

  return NULL;
}

// Excluir todos os alunos de um curso.
int excluirAlunos (LISTA *l, char curso[], ELEMENTO *apagar) {

  ELEMENTO *anterior = NULL;
  ELEMENTO *posicao = l->inicio;
  int cont=0;

  while (posicao != NULL) {
    if (strcmp (posicao->aluno->curso, curso) == 0) {
    	cont++;

      if (anterior == NULL)
        l->inicio = posicao->prox;

      else
        anterior->prox = posicao->prox;
      
      apagar = posicao;
      posicao = posicao->prox;
      free(apagar);
    }
    
    else {
    	anterior = posicao;
		posicao = posicao->prox;
	}
  }
  	if (cont == 0)
  		return -1;
  	else
  		return 1;
}

// Listar todos os alunos.
void listarAlunos (LISTA *l) {

  ELEMENTO *posicao = l->inicio;

  while (posicao != NULL) {
    printf ("%-6d %-10s %-6d %-10s\n", posicao->aluno->ra, posicao->aluno->nome, posicao->aluno->idade, posicao->aluno->curso);
	posicao = posicao->prox;
  }
}

// Listar todos os alunos que pertencem a determinado curso.
void listarCurso (LISTA *l, char curso[]) {

  ELEMENTO *posicao = l->inicio;

  while (posicao != NULL) {
    if (strcmp (posicao->aluno->curso, curso) == 0) {
      printf ("%-6d %-10s %-6d\n", posicao->aluno->ra, posicao->aluno->nome, posicao->aluno->idade);
    }

    posicao = posicao->prox;
  }
}

// Salvar os dados para um arquivo.
int salvarArquivo (LISTA *l) {

  FILE *f = fopen ("sisteminha.txt", "w");
  ELEMENTO *posicao = l->inicio;

  while (posicao != NULL) {
    fprintf (f, "%-6d %-10s %-6d %-10s\n", posicao->aluno->ra, posicao->aluno->nome, posicao->aluno->idade, posicao->aluno->curso);

    posicao = posicao->prox;
  }

  fclose(f);

  return 1;
}

// Ler os dados de um arquivo.
void lerArquivo () {

  FILE *f = fopen ("sisteminha.txt", "r");
  REGISTRO aluno;

  while (fscanf (f, "%d %s %d %s", &aluno.ra, aluno.nome, &aluno.idade, aluno.curso) != EOF) {
    printf ("%-6d %-10s %-6d %-10s\n", aluno.ra, aluno.nome, aluno.idade, aluno.curso);
  }

  fclose(f);
}

//reoordenacao da lista
typedef struct auxAr {
	REGISTRO *aluno;
	struct auxAr *esq;
	struct auxAr *dir;
} NO;

typedef struct {
	NO *raiz;
} ARVORE;

// reordenacao na ordem do nome.
REGISTRO* inserirArvoreNome (NO *no, NO *novo);

// reordenacao na ordem do RA.
REGISTRO* inserirArvoreRA (NO *no, NO *novo);

int ordenarLista (LISTA *l, int sinaliza) {

	ARVORE a;
	a.raiz = NULL; 

	NO *novo = (NO*) malloc (sizeof(NO));
	novo->aluno = l->inicio->aluno;
	novo->esq = NULL;
	novo->dir = NULL;

	a.raiz = novo;

	ELEMENTO *posLista = l->inicio->prox;

	while (posLista != NULL) {
		NO *novo = (NO*) malloc (sizeof(NO));
		novo->aluno = posLista->aluno;

		if (sinaliza == 1)
			inserirArvoreRA (&a.raiz, &novo);

		else if (sinaliza == 0)
			inserirArvoreNome (&a.raiz, &novo);

		ELEMENTO *apagarLista = posLista;
		posLista = posLista->prox;
		free(apagarLista);
	}

	inicializarLista (l);
	
	copiarArvore (l, &a.raiz);
	liberarArvore (&a, &a.raiz);

	if (sinaliza == 0)
		sinaliza = 1;

	else if (sinaliza == 1)
		sinaliza = 0;

	return sinaliza;
}

copiarArvore (LISTA *l, NO *no) {

	if (no == NULL)
		return NULL;

	copiarArvore (l, no->dir);

	inserirListaNova (l, no->aluno);

	copiarArvore (l, no->esq);
}

void inserirListaNova (LISTA *l, REGISTRO *reg) {
	ELEMENTO *novo = (ELEMENTO*) malloc (sizeof(ELEMENTO));
	novo->aluno = reg;
	novo->prox = NULL;

	if (l->inicio == NULL) {
		l->inicio = novo;
		return;
	}

	ELEMENTO *posicao = l->inicio;
	while (posicao->prox != NULL) 
		posicao = posicao->prox;

	posicao->prox = novo;
}

void liberarArvore (ARVORE *a, NO *no) {
	while (a->raiz != NULL) {
		if (no == NULL)
			return;

		liberarArvore (a, no->esq);
		liberarArvore (a, no->dir);

		if (no == a->raiz)
			a->raiz = NULL;
			
		free(no);
	}
}

// ordem do nome.
REGISTRO* inserirArvoreNome (NO *no, NO *novo) {
	if (no == NULL) 
		return NULL;
	
	else if (strcmp (no->aluno->nome, novo->aluno->nome) == 0) {
		if (no->aluno->ra < novo->aluno->nome)
			no->dir = inserirArvoreNome (no->dir, novo);
		
		else
			no->esq = inserirArvoreNome (no->esq, novo);
	}

	else if (strcmp (no->aluno->nome, novo->aluno->nome) < 0) 
		no->dir = inserirArvoreNome (no->dir, novo);

	else if (strcmp (no->aluno->nome, novo->aluno->nome) > 0)
		no->esq = inserirArvoreNome (no->esq, novo);
}

// ordem do RA.
REGISTRO* inserirArvoreRA (NO *no, NO *novo) {
	if (no == NULL) 
		return NULL;

	else if (no->aluno->ra < novo->aluno->ra)
		no->dir = inserirArvoreRA (no->dir, novo);

	else if (no->aluno->ra > novo->aluno->ra)
		no->esq = inserirArvoreRA (no->esq, novo);
}