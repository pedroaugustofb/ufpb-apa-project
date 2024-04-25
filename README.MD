# Sistema de Alocação de Jobs em Servidores na Nuvem

## Descrição do Problema

Este projeto visa desenvolver um sistema de alocação de jobs em servidores na nuvem, otimizando a distribuição e execução de tarefas de forma eficiente e econômica para a empresa. O problema e suas especificações podem ser encontrados em detalhes [neste documento](https://sig-arq.ufpb.br/arquivos/2024121132b7e163354563f0e1b1397dd/Projeto_Final_2023_2_.pdf).

## Como Executar o Projeto

Para complar o projeto, utilize o comando:

`g++ main.cpp entities/*.cpp components/*.cpp -o main`

Para executar o projeto no terminal, utilize o seguinte comando:

`& ./'main.exe' <file path>`

Se tiver muitos arquivos de entrada poderá utilizar Bun Runtime para rodar todos os scripts de uma vez só através de:

`bun main.ts`

example:

`& ./'main.exe' 'input/input.txt'`

## Contexto

Quando um cliente submete uma requisição, um job é criado e adicionado a uma fila de espera. Periodicamente, o sistema da empresa coleta todos os jobs e os distribui entre os servidores disponíveis na nuvem.

## Objetivo

O objetivo principal deste sistema é alocar cada job em um dos servidores, respeitando suas capacidades e minimizando o custo total para a empresa.

## Considerações

- Sejam N o número de jobs e M o número de servidores disponíveis.
- Cada job requer um tempo T de execução no servidor S e gera um custo C.
- Cada servidor S possui uma capacidade B, especificando o tempo máximo que pode ser contratado.
- Jobs não alocados em servidores na nuvem serão executados localmente com um custo fixo P.

## Objetivo Formal

Alocar cada job em um dos servidores, sem exceder suas capacidades, e minimizar o custo total para a empresa.

A resposta detalhada será registrada no arquivo `response.txt` em `/response/response.txt`.
