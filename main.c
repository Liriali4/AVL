#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "avl.c"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int menuRepeticao(const char* acao) {
    int escolha;
    printf("\nDeseja:\n");
    printf("1. Continuar %s\n", acao);
    printf("2. Voltar ao menu principal\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

int main() {
	
	setlocale(LC_ALL,"");
	
    No* arvore = NULL;
    int opcao, valor;
    int repetir;

    do {
        printf("\n\n--- MENU PRINCIPAL---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Imprimir Pré-Ordem\n");
        printf("4. Pesquisar\n");
        printf("5. Encontrar Sucessor\n");
        printf("6. Contar Primos\n");
        printf("7. Limpar a tela\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    printf("Valor a inserir: ");
                    scanf("%d", &valor);
                    arvore = inserirNo(arvore, valor);
                    printf("Inserido com sucesso!\n");

                    repetir = menuRepeticao("inserindo");

                } while (repetir == 1);
                break;

            case 2:
                do {
                	
                	if (arvore == NULL) {
    					printf("\nNão é possível remover valores pois árvore está vazia!\n");
					}else{
                    	printf("Valor a remover: ");
                    	scanf("%d", &valor);
                    	arvore = remover(arvore, valor);
					}
					repetir = menuRepeticao("removendo");

                } while (repetir == 1);
                break;

            case 3:
                do {
					if (arvore == NULL) {
    					printf("  A árvore está vazia, insira valores para puder fazer uma impressão!\n");    	
	            	}else{
                    	printf("Pré-Ordem: ");
                    	imprimirPreOrdem(arvore);
                	    printf("\n");
					}
					repetir = menuRepeticao("imprimindo");

                } while (repetir == 1);
                break;

            case 4:
                do {
                	if (arvore == NULL) {
    					printf("\nNão é possível pesquisar valores pois árvore está vazia!\n");
					}else{
                    	printf("Valor a pesquisar: ");
                    	scanf("%d", &valor);
                    	if (pesquisar(arvore, valor))
                        	printf("Valor encontrado!\n");
                    	else
                        	printf("Valor não encontrado.\n");
					}
					
					repetir = menuRepeticao("pesquisando");
                } while (repetir == 1);
                break;

            case 5:
                do {
                	if (arvore == NULL) {
    					printf("\nNão é possível encontrar sucessor pois árvore está vazia!\n");
					}else{
	                    printf("Valor para encontrar sucessor: ");
	                    scanf("%d", &valor);
	    		        int chave_sucessor = encontrarSucessor(arvore, valor);
						if (chave_sucessor != -1)
						    printf("Sucessor: %d\n", chave_sucessor);
						else
					    	printf("Sucessor não encontrado\n");
					}
					repetir = menuRepeticao("buscando pelo sucessor");
                } while (repetir == 1);
                break;

            case 6:
                do {
                	if (arvore == NULL) {
    					printf("\nNão é possível contar os números primos pois árvore está vazia!\n");
					}else{	                
	                    printf("Número de nos primos: %d\n", contarPrimos(arvore));
					}
					repetir = menuRepeticao("imprimindo");
                } while (repetir == 1);
                break;
			case 7:
                limparTela();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

