Descrição do problema:

see more em: https://sig-arq.ufpb.br/arquivos/2024121132b7e163354563f0e1b1397dd/Projeto_Final_2023_2_.pdf
to run project in terminal: g++ main.cpp entities/job.cpp entities/server.cpp -o main && ./main

Contexto:

- Quando cliente submete uma requisição, um job é criado e adicionado a uma fila.
- Algumas vezes por dia, o sistema da empresa coleta todos os jobs e distruibui entre servidores na nuvem.

Então, objetivo:

Dado conjunto de jobs, algoritmo deve decidir a melhor alocação dos jobs nos servidores disponíveis.

considerações:

- Seja N o número de jobs e M o número de servidores disponíveis.
- Cada job requer um tempo T de execução para ser executado no servidor S.
- Cada job gera um custo C para ser executado.
- Cada servidor S possui uma capacidade B, que específica a quantidade máxima de tempo que pode ser contratada.
- Para cada job não alocado em um servidor na nuvem, será rodado localmente com um custo fixo P.

Objetivo formal: Alocar cada job em um dos servidores, sem violar a capacidade dos mesmos, e de forma a minimizar o custo total para a empresa.

- A resposta deve ser escrita no arquivo `response.txt` em `/response/response.txt`
