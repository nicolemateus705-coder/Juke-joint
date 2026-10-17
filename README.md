# Juke Joint — Biblioteca Musical

Atividade da Unidade 2 de Linguagem de Programação I.

O Juke Joint é um sistema de terminal desenvolvido em C++11 para gerenciar uma biblioteca musical, organizar playlists e controlar uma fila de reprodução. A descrição completa do sistema está em `DESCRICAO.md`, e o planejamento da implementação está em `PLANO.md`.

## Funcionalidades

- Cadastrar músicas com título, artista, duração e álbum.
- Listar todas as músicas cadastradas e consultar uma música pelo ID.
- Remover músicas da biblioteca.
- Criar, listar e excluir playlists.
- Adicionar e remover músicas das playlists e consultar suas músicas.
- Adicionar músicas ao início ou ao final da fila de reprodução.
- Remover músicas da fila de reprodução.
- Avançar para a próxima música, voltar à música anterior e consultar a música atual.
- Validar entradas e apresentar mensagens de erro para dados inválidos, IDs inexistentes e músicas repetidas em uma playlist.

Ao excluir uma música da biblioteca, o sistema também a remove das playlists e da fila de reprodução. Se ela estiver selecionada como música atual, essa seleção é limpa.

## Arquivos

```text
.
├── AGENTS.md
├── DESCRICAO.md
├── ENUNCIADO.md
├── PLANO.md
├── README.md
├── exemplos/
│   ├── casos_erro.in
│   └── fluxo_normal.in
├── include/
│   ├── Biblioteca.hpp
│   ├── FilaReproducao.hpp
│   ├── Musica.hpp
│   └── Playlist.hpp
└── src/
    ├── Biblioteca.cpp
    ├── FilaReproducao.cpp
    ├── Musica.cpp
    ├── Playlist.cpp
    └── main.cpp
```

## Compilar e executar

Para compilar o programa, execute no terminal, a partir da pasta raiz do projeto:

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
```

Em seguida, execute o sistema:

```bash
./sistema
```

O programa apresenta um menu com as operações disponíveis. Para encerrar, escolha a opção `0`.

## Testar com os exemplos

O diretório `exemplos/` contém arquivos de entrada para testar o funcionamento do sistema.

Para executar o exemplo de fluxo normal:

```bash
./sistema < exemplos/fluxo_normal.in
```

Para executar o exemplo com casos de erro:

```bash
./sistema < exemplos/casos_erro.in
```

O arquivo `fluxo_normal.in` simula operações de cadastro e consulta de músicas, criação e utilização de playlist e controle da fila de reprodução.

O arquivo `casos_erro.in` contém entradas inválidas e operações com IDs inexistentes, permitindo verificar as mensagens de erro apresentadas pelo sistema.

## Onde uso a STL

O projeto utiliza containers da Standard Template Library (STL) para armazenar e organizar músicas, playlists e a fila de reprodução.

| Onde | O quê | Por quê |
| --- | --- | --- |
| `Biblioteca` | `std::map<int, Musica>` | Armazena as músicas associadas aos seus IDs, permitindo consultas e remoções pela chave. |
| `Biblioteca` | `std::map<int, Playlist>` | Armazena as playlists pelos seus IDs, permitindo identificá-las mesmo quando possuem o mesmo nome. |
| `Playlist` | `std::list<int>` | Guarda os IDs das músicas na ordem em que foram adicionadas à playlist. |
| `Playlist` | `std::set<int>` | Permite verificar se um ID já está na playlist e impedir músicas repetidas. |
| `FilaReproducao` | `std::list<Musica>` | Armazena as músicas da fila e permite adicionar elementos no início ou no final, além de removê-los. |

## Como usei a IA

- **Modelo usado:** Big Pickle, pelo OpenCode.
- **Um pedido que deu certo, e por que você acha que deu certo:** Solicitei a implementação das classes separadamente, seguindo o plano de implementação. Isso ajudou a desenvolver e testar cada parte antes de integrá-la ao sistema.
- **Um pedido que deu errado, o que veio errado e como você mudou o pedido:** Durante a implementação da fila de reprodução, o comportamento da música atual ao removê-la da fila não correspondia ao esperado. Pedi uma revisão da lógica e testes específicos para verificar o comportamento antes de aceitar a correção.
- **Uma coisa que a IA sugeriu e você recusou, e por quê:** Mantive a implementação limitada às funcionalidades previstas na descrição e no plano, evitando acrescentar recursos que não eram necessários para a atividade.