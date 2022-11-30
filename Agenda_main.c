#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char Dia[3];
    char Mes[3];
    char Ano[5];
} Data_hoje;

typedef struct Aniversario
{
    char dia[3];
    char mes[3];
    char ano[5];
} Aniversario;

typedef struct Fone
{
    char ddd[4];
    char telefone[16];
} Fone;

typedef struct Endereco
{
    char pais[4];
    char estado[3];
    char cidade[31];
    char bairro[51];
    char rua[51];
    char numero[6];
    char complemento[51];
    char cep[11];
} Endereco;

typedef struct Contato
{
    char nome[51];
    char email[81];
    Fone fone;
    Aniversario aniversario;
    Endereco endereco;
    
} Contato;

//Estrutura para armazenar os contatos em uma lista encadeada;
typedef struct Agenda 
{
    Contato *contato;
    struct Agenda *proximo;
} Agenda;

//Protótipos das funções:
Agenda* inserir_contato(Contato contato, Agenda *agenda);
Agenda* remove_contato(Contato contato, Agenda *agenda);
Agenda* pesquisar_contato(char nome[51], Agenda *agenda);
Contato seleciona_contato(Agenda *agenda);
Contato novo_contato(void);
Data_hoje entrada(char msg[]);
void aniversariantes_mes(Data_hoje *dt, Agenda *agenda);
void aniversariantes_dia(Data_hoje *dt, Agenda *agenda);
void imprimir(Agenda *agenda);
void imprime_contato(Contato contato);
void limpa_agenda(Agenda *agenda);

int main (void)
{
    Agenda *lista = (Agenda*) malloc(sizeof(Agenda));
    lista->contato = NULL;
    lista->proximo = NULL;

    int opcao;
    char nome[51], msg;
    Contato auxiliar;
    Agenda *filtrada;
    Data_hoje hoje;

    do
    {
        printf("\n1 - Adicionar\n2 - Remover\n3 - Pesquisar\n4 - Aniversariantes do mês\n5 - Aniversariantes do dia\n6 - Imprimir\n7 - Sair\n->");
        scanf("%d%*c", &opcao);

        switch (opcao)
        {
        case 1: // Adicionar novo contato
            auxiliar = novo_contato();
            lista = inserir_contato(auxiliar, lista);
            break;
        
        case 2: // Remover contato
            printf("\nDigite o nome desejado: ");
            scanf("%[^\n]%*c", nome);

            filtrada = pesquisar_contato(nome, lista);

            auxiliar = seleciona_contato(filtrada);

            if (strcmp(auxiliar.nome, "VOID") == 0) {
                break;
            }

            lista = remove_contato(auxiliar, lista);

            printf("\nContato removido com sucesso!\n");
            break;
        
        case 3: // Pesquisar contatos pelo o nome
            printf("\nDigite o nome desejado: ");
            scanf("%[^\n]%*c", nome);

            filtrada = pesquisar_contato(nome, lista);

            imprimir(filtrada);
            limpa_agenda(filtrada);

            break;
            
        case 4: // Aniversariantes do mes
            hoje = entrada("Data de hoje");
            printf("\nAniversariantes do mês %s:\n", hoje.Mes);
            aniversariantes_mes(&hoje, lista);
            break; 

        case 5: //Aniversariantes do dia
            hoje = entrada("Data de hoje");
            printf("\nAniversariantes do dia %s/%s: \n", hoje.Dia, hoje.Mes);
            aniversariantes_dia(&hoje, lista);
            break;

        case 6: // Imprime a lista de contatos na ordem de inclusão
            imprimir(lista);
            break;

        case 7: // Encerra o programa
            printf("\nEncerrando o programa\n");
            limpa_agenda(lista);
            return 0;

        default:
            printf("\nSelecione uma opção válida!\n");
            break;
        }

    } while(1 == 1);
  
    return 0;
}

// Funções:

Agenda* inserir_contato(Contato contato, Agenda *agenda)
{
    // Verifica se já existe um contato salvo nesta agenda
    // Se o contato for nulo, apenas salva nessa agenda
    if (agenda->contato == NULL) {
        Contato *novo_contato = (Contato*) malloc(sizeof(Contato));
        *novo_contato = contato;
        agenda->contato = novo_contato;
        return agenda;
    } 
    else
    {
        //Se já existir um contato salvo, cria uma nova agenda (Nó) para salvar este contato
        Agenda *nova_agenda = (Agenda*) malloc(sizeof(Agenda)); // Cria uma nova agenda (nó) com memória alocada
        Contato *novo_contato = (Contato*) malloc(sizeof(Contato)); // Cria um novo contato com memória alocada
        *novo_contato = contato;
        nova_agenda->contato = novo_contato;
        nova_agenda->proximo = agenda;
        // Retorna a nova lista atualizada com o novo contato
        return nova_agenda; 
    }

}

Agenda* remove_contato(Contato contato, Agenda *agenda)
{
    // printf("A: %s -- P: %s", agenda->contato->email, agenda->proximo->contato->email);
    if (strcmp(agenda->contato->nome, contato.nome) == 0 && strcmp(agenda->contato->email, contato.email) == 0 && strcmp(agenda->contato->fone.telefone, contato.fone.telefone) == 0)
    {
        Agenda *aux = agenda->proximo;
        free(agenda);
        return aux;

    } 
    else
    {
        agenda->proximo = remove_contato(contato, agenda->proximo);
        return agenda;
    }

}

Contato novo_contato(void)
{
    Contato pessoa;
    printf("\n\n------- Novo Contato -------\n");
    printf("Digite o nome: ");
    scanf("%[^\n]%*c", pessoa.nome);
    printf("Digite o e-mail: ");
    scanf("%[^\n]%*c", pessoa.email);

    printf("------- Aniversário -------\n");
    printf("Digite o dia (XX Exemplo: 01 -> dia primeiro): ");
    scanf("%[^\n]%*c", pessoa.aniversario.dia);
    printf("Digite o mês (XX Exemplo: 01 -> Janeiro): ");
    scanf("%[^\n]%*c", pessoa.aniversario.mes);
    printf("Digite o ano (XXXX Exemplo: 2022): ");
    scanf("%[^\n]%*c", pessoa.aniversario.ano);

    printf("\n------- Telefone -------\n");
    printf("Digite o DDD: ");
    scanf("%[^\n]%*c", pessoa.fone.ddd);
    printf("Digite o telefone: ");
    scanf("%[^\n]%*c", pessoa.fone.telefone);

    printf("\n------- Endereço -------\n");
    printf("Digite o país (XXX Exemplo: BRA -> Brasil): ");
    scanf("%[^\n]%*c", pessoa.endereco.pais);
    printf("Digite o estado (XX Exemplo: SC -> Santa Catarina): ");
    scanf("%[^\n]%*c", pessoa.endereco.estado);
    printf("Digite a cidade (Máx. 30 caracteres): ");
    scanf("%[^\n]%*c", pessoa.endereco.cidade);
    printf("Digite o bairro (Máx. 50 caracteres): ");
    scanf("%[^\n]%*c", pessoa.endereco.bairro);
    printf("Digite a rua (Máx. 50 caracteres): ");
    scanf("%[^\n]%*c", pessoa.endereco.rua);
    printf("Digite o número (Máx. 5 dígitos): ");
    scanf("%[^\n]%*c", pessoa.endereco.numero);
    printf("Digite o complemento (Máx. 50 caracteres): ");
    scanf("%[^\n]%*c", pessoa.endereco.complemento);
    printf("Digite o CEP (Máx. 10 caracteres): ");
    scanf("%[^\n]%*c", pessoa.endereco.cep);
    
    return pessoa;
}

Agenda* pesquisar_contato(char nome[51], Agenda *agenda)
{
    // Cria agenda auxiliar para receber os contatos encontrados com o mesmo nome  
    Agenda *aux = (Agenda*) malloc(sizeof(Agenda));
    
    int achados = 0;

    // Percorre toda a agenda que foi passada e verifica o nome dos contatos com o nome desejado
    // caso o nome seja igual adiciona na agenda auxiliar 
    while (agenda != NULL && agenda->contato != NULL)
    {
        if (strcmp(nome, agenda->contato->nome) == 0) // Nome igual ao do contato
        {
            // Adiciona contato na agenda auxiliar 
            aux = inserir_contato((Contato) *agenda->contato, aux);
            // Incrementa a quantidade de contatos encontrados
            achados++;
        }
        // Atualiza para o próximo espaço da agenda
        agenda = agenda->proximo;
    }

    // Se não for encontrado nenhum contato  
    if (!achados)
    {
        // Indica que nenhum contato foi encontrado
        printf("\nNenhum contato encontrado!\n");
        // Limpa agenda e desaloca memória
        free(aux);
        // Retorna nulo pois nada foi encontrado
        return NULL;
    } else
    {
        // indica quantos contatos foram encontrados e retorna agenda auxiliar
        printf("\nForam encontrados %i contatos\n", achados);
        return aux;
    }

    // Não deve chegar neste ponto
    return NULL;
}

// Lista os contatos com código e solicita seleção do usuário
// se seleção inválida retorna contato com nome == "VOID"
Contato seleciona_contato(Agenda *agenda)
{
    int selecao = 0;
    int cod = 1;
    Agenda *inicio = agenda;

    Contato vazio;
    strcpy(vazio.nome, "VOID");

    while (agenda != NULL)
    {
        printf("\n\n-> CÓDIGO: %i <-", cod);
        imprime_contato((Contato) *agenda->contato);

        agenda = agenda->proximo;
        cod++;
    }

    printf("\n\nDigite o código do contato desejado: ");
    scanf("%i%*c", &selecao);

    if (selecao > cod && selecao < 1)
    {
        return vazio;
    }

    // Busca contato na memória
    Contato desejado;
    for (int i = 0; i < selecao; i++)
    {
        desejado = (Contato) *inicio->contato;
        inicio = inicio->proximo;
    }
    
    return desejado;
}

//Imprime a lista passada por parâmetro por recursão
void imprimir(Agenda *agenda)
{
    if (agenda == NULL)
    {
        return;
    }
    // Se não existir nenhum contato adicionado anteriormente, imprime o atual
    if (agenda->proximo == NULL)
    {
        // Mas se o próximo for nulo e o contato for nulo, não existem contatos salvos na lista
        if (agenda->contato == NULL) 
        {
            printf("\nNenhum contato na lista!\n");
            return;
        }
        // Imprime contato
        imprime_contato((Contato) *agenda->contato);
    } else
    {
        // Se existir um contato adicionado antes que esse manda imprimir ele
        imprimir(agenda->proximo);
        imprime_contato((Contato) *agenda->contato);
    }
    printf("\n---------------------------\n");
}

// Imprime o contato formatado
void imprime_contato(Contato contato)
{
    printf("\n---------------------------\n");
    printf("Nome: %s", contato.nome);
    printf("\t\t\t\tNasc.: %s/%s/%s\n", contato.aniversario.dia, contato.aniversario.mes, contato.aniversario.ano);
    printf("E-mail: %s\t\t\t\tTelefone: (%s) %s\n", contato.email, contato.fone.ddd, contato.fone.telefone);
    printf("Endereço:\n");
    printf("País: %s\tEstado: %s\tCidade: %s\n", contato.endereco.pais, contato.endereco.estado, contato.endereco.cidade);
    printf("Bairro: %s\t\t\tRua: %s\n", contato.endereco.bairro, contato.endereco.rua);
    printf("CEP: %s", contato.endereco.cep);
}

// Libera memória alocada para a lista
// libera primeiro o contato armazenado
// e depois a agenda
void limpa_agenda(Agenda *agenda)
{
    // Se existir um contato a mais libera primeiro o próximo
    // evitando esquecimento de ponteiros
    if (agenda->proximo != NULL) 
    {
        limpa_agenda(agenda->proximo);
    }

    // Libera memórias
    free(agenda);

}

//Função para receber a data atual
Data_hoje entrada(char msg[])
{
    Data_hoje dt;
    printf("Digite o dia (XX Exemplo: 01 -> dia primeiro): ");
    scanf("%[^\n]%*c", dt.Dia);
    printf("Digite o mês (XX Exemplo: 01 -> Janeiro): ");
    scanf("%[^\n]%*c", dt.Mes);
    printf("Digite o ano (XXXX Exemplo: 2022): ");
    scanf("%[^\n]%*c", dt.Ano);
    return (dt);
}

// Funçao Aniversariantes do mês
void aniversariantes_mes(Data_hoje *dt, Agenda *agenda)
{
    Data_hoje data = (Data_hoje) *dt;
    
    if(agenda == NULL)
    {
        return;
    }
    else 
    {
        Contato contato = (Contato) *agenda->contato;

        if(strcmp(data.Mes, contato.aniversario.mes) == 0)
        {
            printf("%s\n", contato.nome);
        }

        aniversariantes_mes(dt, agenda->proximo);
        return;
    }

}

// Funçao Aniversariantes do dia
void aniversariantes_dia(Data_hoje *dt, Agenda *agenda)
{
    Data_hoje data = (Data_hoje) *dt;

    if(agenda == NULL)
    {
        return;
    }
    else
    {
        Contato contato = (Contato) *agenda->contato;

        if(strcmp(data.Dia, contato.aniversario.dia) == 0 && strcmp(data.Mes, contato.aniversario.mes) == 0)
        {
            printf("%s\n", contato.nome);
        }
        aniversariantes_dia(dt, agenda->proximo);
        return;
    }
}
