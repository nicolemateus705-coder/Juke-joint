# Juke Joint — Biblioteca Musical

## 1. Nome e ideia

O Juke Joint é um sistema de biblioteca musical desenvolvido em C++ que permite cadastrar e organizar músicas, criar playlists e controlar uma fila de reprodução por meio de uma interface de texto no terminal. O objetivo é facilitar o gerenciamento de uma coleção musical e permitir que o usuário organize as músicas de acordo com suas preferências.

## 2. O que o sistema armazena

O sistema armazena músicas, playlists, uma fila de reprodução e a música atual.

Cada música possui um identificador numérico único, gerado automaticamente pelo sistema, além de título, artista, duração e álbum. A duração é representada em minutos e segundos.

As playlists armazenam referências às músicas cadastradas. A fila de reprodução organiza as músicas que o usuário deseja reproduzir, enquanto a música atual é controlada separadamente da fila.

## 3. O que o usuário pode fazer

O usuário pode cadastrar músicas, consultar as músicas existentes e visualizar suas informações. Também pode criar, listar e excluir playlists, além de adicionar músicas cadastradas às playlists e remover músicas delas.

O sistema permite adicionar músicas ao início ou ao final da fila de reprodução, remover músicas da fila, avançar e voltar entre as músicas e consultar qual música está selecionada como atual.

## 4. Regras do sistema

- Cada música recebe um identificador numérico único gerado automaticamente.
- Os identificadores de músicas excluídas não são reutilizados.
- Músicas diferentes podem ter o mesmo título.
- Título, artista, duração e álbum são obrigatórios. Espaços no início e no fim do texto não contam como conteúdo para validar campos obrigatórios.
- A duração deve ser informada em minutos e segundos, com os segundos entre 00 e 59. A duração zero é permitida.
- Uma playlist só pode conter músicas que estejam cadastradas na biblioteca.
- A mesma música não pode aparecer mais de uma vez na mesma playlist.
- Playlists diferentes podem ter o mesmo nome.
- Cada música deve ser selecionada por seu identificador numérico, e não apenas pelo título.
- Excluir uma playlist não exclui as músicas cadastradas nem altera a fila de reprodução.
- Ao excluir uma música da biblioteca, todas as suas ocorrências são removidas das playlists e da fila.
- Se a música excluída for a música atual, a seleção atual é limpa.
- Ao remover uma música da fila, todas as ocorrências dessa música são removidas.
- A música atual é controlada separadamente da fila de reprodução.
- Se ainda não houver uma música atual e o usuário adicionar a primeira música à fila, essa música passa a ser a atual automaticamente.
- Ao avançar depois da última música da fila, a seleção retorna à primeira música.
- Se houver apenas uma música na fila, avançar mantém essa música como atual.
- Ao voltar quando a primeira música está selecionada, ela permanece como atual.
- Se a fila estiver vazia, as operações de avançar e voltar não fazem nada.
- Um identificador inexistente não corresponde a nenhuma música cadastrada, e a operação solicitada não deve ser executada.

## 5. Quando algo dá errado

O sistema deve verificar os dados informados durante o cadastro de músicas. Se algum campo obrigatório estiver vazio ou se a duração estiver em formato inválido, o cadastro deve ser rejeitado.

Quando o usuário consultar ou tentar remover uma música usando um identificador inexistente, o sistema deve informar que a música não foi encontrada e não executar a operação.

O sistema também deve impedir que músicas não cadastradas sejam adicionadas às playlists e informar quando uma música não pertencer à playlist ou à fila no momento de uma tentativa de remoção. Essas situações não devem provocar alterações indevidas nos dados armazenados.

Se o usuário informar uma opção de menu inválida, o sistema deve exibir uma mensagem de erro e solicitar outra opção, sem encerrar o programa.

## 6. Classes que imagino

- **Musica:** representa uma música e armazena seu identificador, título, artista, duração e álbum.
- **Playlist:** representa uma playlist e gerencia as músicas que fazem parte dela, respeitando a regra de não permitir músicas repetidas.
- **Biblioteca:** gerencia as músicas cadastradas e as playlists, além das operações de cadastro, consulta e exclusão.
- **Fila de reprodução:** organiza as músicas na ordem escolhida pelo usuário e permite adicionar, remover, avançar e voltar na fila.

A música atual deve ser controlada separadamente da fila. As classes serão responsáveis pelas regras e pela lógica do sistema, enquanto a interface de texto ficará responsável por receber as opções do usuário e apresentar os resultados no terminal.

## 7. Exemplo de uso

Ao iniciar o sistema, o usuário pode cadastrar duas músicas informando título, artista, duração e álbum. O sistema gera automaticamente um identificador para cada música.

Em seguida, o usuário pode criar uma playlist, adicionar uma das músicas cadastradas e visualizar as músicas da playlist. Depois, pode adicionar músicas ao início ou ao final da fila, consultar a música atual e avançar ou voltar entre as músicas de acordo com as regras definidas.

Se ainda não houver uma música atual, a primeira música adicionada à fila será selecionada automaticamente. O usuário também pode criar playlists com nomes iguais, pois cada playlist será tratada separadamente.

Se o usuário excluir uma música da biblioteca, ela também será removida das playlists e da fila. Caso essa música seja a atual, a seleção atual será limpa.