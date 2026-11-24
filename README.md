# lpa-trabalho-b2
Sistema de Gestão de Estacionamento em C
## Casos de teste (opções 1 a 4 — Thiago)

| Teste | Entrada / operação | Resultado esperado | Resultado observado | Situação |
|-------|--------------------|--------------------|---------------------|----------|
| T02 – Cadastro válido | Opção 1: ID `abf09a8`, descrição "ford ka preto ano 2010 com blindagem e vidro fosco", categoria 1, F3/C4 | Veículo cadastrado; ID normalizado para maiúsculas | "Veiculo ABF09A8 cadastrado na vaga F3/C4." | Aprovado |
| T03 – Duplicidade sem distinção de caixa | Opção 1 com ID `ABF09A8` (já cadastrado como `abf09a8`) | Cadastro recusado por duplicidade, sem pedir os demais dados | "Ja existe um veiculo com esse identificador." | Aprovado |
| Consulta por ID | Opção 2 com ID `abf09a8` (minúsculo) | Mostra ID, descrição, categoria e posição | "ID: ABF09A8 \| Descricao: ... \| Categoria: Carro \| Posicao: F3/C4" | Aprovado |
| T06 – Atualização | Opção 3 com ID `abf09a8`, nova descrição "ford ka rozinha", Enter na categoria | Descrição muda, sem duplicar o registro | Consulta posterior mostra "ford ka rozinha", categoria Carro e F3/C4 mantidos | Aprovado |
| T07 – Movimentação | Opção 4 com ID `abf09a8`, destino F1/C1 | Veículo movido para a vaga livre | Mensagem de veículo movido exibida | Aprovado |

> Os testes T05 (crescimento dinâmico), T08 (remoção) e T09 (lotação) dependem das opções 5 a 8 e ficam na seção do outro integrante.

## Declaração individual — Thiago Gontijo Mazotti

**(a) Funcionalidades em que atuei:** opções 1 a 4 do menu (cadastrar, consultar, atualizar e mover veículo), com as validações de entrada e a atualização do mapa de vagas. Branch: `feature-menu-matriz`.

**(b) Usei IA generativa?** Sim

**(c) Ferramenta e uso:** Claude (Anthropic). Usei para ajuda com a configuração do VS Code e do compilador gcc, para  para explicações e correção de erros de compilação.
Li, testei e adaptei o código antes de usar.

**(d) Código externo adaptado:** Não.

|-------|--------------------|--------------------|---------------------|----------|

## Casos teste (opções 5 a 8 - Matheus)

| Teste | Entrada / operação | Resultado esperado | Resultado observado | Situação |
|-------|--------------------|--------------------|---------------------|----------|
| T05 (crescimento dinâmico) | Opção 1 com três entradas distintas| Os três veículos são cadastrados e a memória dobra com o uso do realloc | Ao colocar três entradas aparece uma mensagem dizendo que a capacidade foi ampliada. Quando usamos a opção 6 para listar, as três entradas aparecem | Aprovado |
| T08 (remoção) | Opção 1 para incluir vaga a um veículo, depois opção 5 para remover| O veículo desaparecerá do registro do sistema e a vaga é liberada| Ao colocar um veículo ASDF123 numa vaga F1/C1 depois remover ele, aparece uma mensagem dizendo que o veículo foi removido, ao buscar no mapa aparece que a vaga tá liberada, ao colocar um outro veículo WASD123 na mesma vaga e listar os veículos cadastrados, aparece o novo veículo, não o antigo nesse lugar | Aprovado |
| T09 (lotação) | Opção 1 com 21 entradas | A vigésima primeira vaga será rejeitada | Ao colocar 21 entradas aparece uma mensagem dizendo que o estacionamento tá lotado, nos limitando a 20 vagas | Aprovado |

## Declaração individual — Matheus de Assis Faria

**(a) Funcionalidades em que atuei:** Opções de 5 a 8 do menu (Remover, Listar, Exibir mapa, Exibir relatório), atualizei o código já existente do thiago.

**(b) Usei IA generativa?** Sim

**(c) Ferramenta e uso:** Claude (Anthropic). Usei para ajuda com o compilador gcc, para  para explicações e validação de requisitos.

**(d) Código externo adaptado:** Não.

