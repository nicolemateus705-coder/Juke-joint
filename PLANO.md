# Plano de implementação — Juke Joint

## Objetivo

Implementar uma biblioteca musical em C++11 com interface de texto no terminal, mantendo a lógica do sistema separada da interface. A implementação será dividida em etapas pequenas, com compilação e testes ao final de cada uma.

## Classes e responsabilidades

### 1. Musica

Representa uma música e armazena seu identificador numérico, título, artista, duração e álbum. Deve fornecer acesso aos dados e definir `operator==` para comparar músicas pelo identificador, permitindo usar `find` para localizar objetos dessa classe.

### 2. Playlist

Representa uma playlist com identificador próprio, nome e referências às músicas cadastradas. Deve permitir adicionar e remover músicas, impedir que a mesma música apareça mais de uma vez e listar as músicas da playlist.

### 3. FilaReproducao

Gerencia a ordem de reprodução e a música atual. Deve permitir adicionar músicas no começo ou no fim, remover músicas, avançar e voltar na fila e consultar a música atual. A classe será independente de `Biblioteca`, mas deverá oferecer operações que permitam à biblioteca remover da fila as músicas excluídas do cadastro.

### 4. Biblioteca

Gerencia as músicas cadastradas e as playlists. Deve gerar identificadores únicos para músicas e playlists, permitir consultar músicas pelo ID, listar músicas e playlists e coordenar as exclusões para manter as playlists e a fila consistentes.

### 5. Interface em main.cpp

Apresenta o menu, lê os dados do usuário e mostra mensagens de resultado. Não deve concentrar as regras de negócio: essas regras ficam nas classes do sistema.

## Uso da STL

- `map<int, Musica>` em `Biblioteca`: associa o identificador da música ao objeto correspondente e permite consultar músicas pelo ID.
- `list<int>` em `Playlist`: mantém a ordem das referências às músicas.
- `set<int>` em `Playlist`: permite verificar se uma música já foi adicionada à playlist.
- `list<Musica>` em `FilaReproducao`: mantém as músicas na ordem de reprodução.
- `find` aplicado a objetos `Musica`: localiza uma música na fila, usando `operator==` para comparar os identificadores.

## Etapas de implementação

### Etapa 1 — Classe Musica
Criar `include/Musica.hpp` e `src/Musica.cpp`, com os atributos, construtores, métodos de acesso e comparação por ID. Testar a criação de músicas e a comparação entre elas.

### Etapa 2 — Classe Playlist
Criar `include/Playlist.hpp` e `src/Playlist.cpp`. Implementar o cadastro das referências, a prevenção de duplicatas e a remoção de músicas. Testar adições repetidas e remoções.

### Etapa 3 — Classe FilaReproducao
Criar `include/FilaReproducao.hpp` e `src/FilaReproducao.cpp`. Implementar adição no começo e no fim, remoção de todas as ocorrências, consulta da música atual, avanço e retorno. Testar fila vazia, fila com uma música, avanço após a última música e retorno quando a primeira está selecionada.

### Etapa 4 — Classe Biblioteca
Criar `include/Biblioteca.hpp` e `src/Biblioteca.cpp`. Implementar cadastro, listagem, consulta por ID, geração de identificadores e gerenciamento das playlists. Ao excluir uma música, remover suas referências das playlists e suas ocorrências da fila, além de limpar a música atual quando necessário. Testar IDs não reutilizados, títulos repetidos, nomes de playlists repetidos e exclusões.

### Etapa 5 — Interface de terminal
Implementar `src/main.cpp` com um menu para as funcionalidades descritas em `DESCRICAO.md`. Tratar entradas inválidas sem encerrar o programa inesperadamente. Manter entrada e saída de dados fora das classes de lógica.

### Etapa 6 — Integração e testes finais
Compilar todos os arquivos usando o comando registrado no `README.md`. Criar arquivos de entrada em `exemplos/` para testar operações normais e casos de erro. Conferir as regras da descrição e verificar as alterações no Git antes de registrar o commit da etapa.

## Organização dos arquivos

- `include/Musica.hpp`
- `src/Musica.cpp`
- `include/Playlist.hpp`
- `src/Playlist.cpp`
- `include/FilaReproducao.hpp`
- `src/FilaReproducao.cpp`
- `include/Biblioteca.hpp`
- `src/Biblioteca.cpp`
- `src/main.cpp`
- `exemplos/`

Cada etapa será implementada, compilada e testada antes de avançar para a seguinte. Cada etapa concluída terá seu próprio commit.