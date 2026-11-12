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

**(b) Usei IA generativa?** não

**(c) Ferramenta e uso:** nenhuma

**(d) Código externo adaptado:** Não.