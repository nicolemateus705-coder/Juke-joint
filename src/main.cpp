#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "Biblioteca.hpp"
#include "FilaReproducao.hpp"
#include "Musica.hpp"

namespace {

void imprimirMusica(const Musica& musica) {
    std::cout << "[" << musica.getId() << "] " << musica.getTitulo() << " - "
              << musica.getArtista() << " - " << musica.getMinutos() << ":"
              << std::setfill('0') << std::setw(2) << musica.getSegundos()
              << std::setfill(' ') << " - " << musica.getAlbum() << std::endl;
}

void mostrarErro(Biblioteca::Resultado resultado) {
    switch (resultado) {
        case Biblioteca::MUSICA_INEXISTENTE:
            std::cout << "Erro: música não encontrada." << std::endl;
            break;
        case Biblioteca::PLAYLIST_INEXISTENTE:
            std::cout << "Erro: playlist não encontrada." << std::endl;
            break;
        case Biblioteca::ENTRADA_INVALIDA:
            std::cout << "Erro: dados inválidos. Título, artista, álbum e "
                      << "duração são obrigatórios." << std::endl;
            break;
        case Biblioteca::MUSICA_JA_NA_PLAYLIST:
            std::cout << "Erro: a música já está nesta playlist." << std::endl;
            break;
        case Biblioteca::MUSICA_NAO_ESTA_NA_PLAYLIST:
            std::cout << "Erro: a música não está nesta playlist." << std::endl;
            break;
        default:
            break;
    }
}

void mostrarMusicaAtual(const FilaReproducao& fila) {
    Musica atual;
    if (fila.getMusicaAtual(atual)) {
        std::cout << "Música atual: ";
        imprimirMusica(atual);
    } else {
        std::cout << "Nenhuma música selecionada." << std::endl;
    }
}

bool lerTexto(const std::string& rotulo, std::string& texto) {
    std::cout << rotulo;
    if (!std::getline(std::cin, texto)) {
        std::cout << std::endl << "Fim da entrada." << std::endl;
        return false;
    }
    return true;
}

bool lerInteiro(const std::string& rotulo, int& valor) {
    std::string linha;
    while (true) {
        std::cout << rotulo;
        if (!std::getline(std::cin, linha)) {
            std::cout << std::endl << "Fim da entrada." << std::endl;
            return false;
        }
        std::istringstream entrada(linha);
        int v;
        char sobra;
        if ((entrada >> v) && !(entrada >> sobra)) {
            valor = v;
            return true;
        }
        std::cout << "Valor inválido. Digite apenas um número inteiro." << std::endl;
    }
}

void mostrarMenu() {
    std::cout << std::endl
              << "=== Juke Joint ===" << std::endl
              << " 1) Cadastrar música" << std::endl
              << " 2) Listar músicas" << std::endl
              << " 3) Consultar música por ID" << std::endl
              << " 4) Remover música" << std::endl
              << " 5) Criar playlist" << std::endl
              << " 6) Listar playlists" << std::endl
              << " 7) Excluir playlist" << std::endl
              << " 8) Adicionar música à playlist" << std::endl
              << " 9) Remover música da playlist" << std::endl
              << "10) Mostrar músicas de playlist" << std::endl
              << "11) Adicionar música ao fim da fila" << std::endl
              << "12) Adicionar música ao início da fila" << std::endl
              << "13) Remover música da fila" << std::endl
              << "14) Avançar" << std::endl
              << "15) Voltar" << std::endl
              << "16) Mostrar música atual" << std::endl
              << " 0) Sair" << std::endl;
}

} // namespace

int main() {
    Biblioteca biblioteca;
    FilaReproducao fila;
    bool encerrar = false;

    while (!encerrar) {
        mostrarMenu();

        int opcao;
        if (!lerInteiro("Opção: ", opcao)) {
            break;
        }

        switch (opcao) {
            case 0:
                encerrar = true;
                std::cout << "Até logo!" << std::endl;
                break;

            case 1: {
                std::string titulo;
                std::string artista;
                std::string album;
                int minutos;
                int segundos;
                if (!lerTexto("Título: ", titulo) ||
                    !lerTexto("Artista: ", artista) ||
                    !lerInteiro("Minutos: ", minutos) ||
                    !lerInteiro("Segundos: ", segundos) ||
                    !lerTexto("Álbum: ", album)) {
                    encerrar = true;
                    break;
                }
                int idGerado = 0;
                Biblioteca::Resultado r = biblioteca.cadastrarMusica(
                    titulo, artista, minutos, segundos, album, idGerado);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Música cadastrada com ID " << idGerado
                              << "." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 2: {
                const std::map<int, Musica>& musicas = biblioteca.listarMusicas();
                if (musicas.empty()) {
                    std::cout << "Nenhuma música cadastrada." << std::endl;
                    break;
                }
                std::map<int, Musica>::const_iterator it = musicas.begin();
                for (; it != musicas.end(); ++it) {
                    imprimirMusica(it->second);
                }
                break;
            }

            case 3: {
                int id;
                if (!lerInteiro("ID da música: ", id)) {
                    encerrar = true;
                    break;
                }
                Musica musica;
                Biblioteca::Resultado r = biblioteca.consultarMusica(id, musica);
                if (r == Biblioteca::SUCESSO) {
                    imprimirMusica(musica);
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 4: {
                int id;
                if (!lerInteiro("ID da música: ", id)) {
                    encerrar = true;
                    break;
                }
                Biblioteca::Resultado r = biblioteca.removerMusica(id, fila);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Música removida da biblioteca." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 5: {
                std::string nome;
                if (!lerTexto("Nome da playlist: ", nome)) {
                    encerrar = true;
                    break;
                }
                int idGerado = 0;
                Biblioteca::Resultado r = biblioteca.criarPlaylist(nome, idGerado);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Playlist criada com ID " << idGerado
                              << "." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 6: {
                const std::map<int, Playlist>& playlists = biblioteca.listarPlaylists();
                if (playlists.empty()) {
                    std::cout << "Nenhuma playlist cadastrada." << std::endl;
                    break;
                }
                std::map<int, Playlist>::const_iterator it = playlists.begin();
                for (; it != playlists.end(); ++it) {
                    std::cout << "[" << it->second.getId() << "] "
                              << it->second.getNome() << std::endl;
                }
                break;
            }

            case 7: {
                int id;
                if (!lerInteiro("ID da playlist: ", id)) {
                    encerrar = true;
                    break;
                }
                Biblioteca::Resultado r = biblioteca.removerPlaylist(id);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Playlist excluída." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 8: {
                int idPlaylist;
                int idMusica;
                if (!lerInteiro("ID da playlist: ", idPlaylist) ||
                    !lerInteiro("ID da música: ", idMusica)) {
                    encerrar = true;
                    break;
                }
                Biblioteca::Resultado r =
                    biblioteca.adicionarMusicaNaPlaylist(idPlaylist, idMusica);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Música adicionada à playlist." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 9: {
                int idPlaylist;
                int idMusica;
                if (!lerInteiro("ID da playlist: ", idPlaylist) ||
                    !lerInteiro("ID da música: ", idMusica)) {
                    encerrar = true;
                    break;
                }
                Biblioteca::Resultado r =
                    biblioteca.removerMusicaDaPlaylist(idPlaylist, idMusica);
                if (r == Biblioteca::SUCESSO) {
                    std::cout << "Música removida da playlist." << std::endl;
                } else {
                    mostrarErro(r);
                }
                break;
            }

            case 10: {
                int idPlaylist;
                if (!lerInteiro("ID da playlist: ", idPlaylist)) {
                    encerrar = true;
                    break;
                }
                std::list<int> ids;
                Biblioteca::Resultado r =
                    biblioteca.listarMusicasDaPlaylist(idPlaylist, ids);
                if (r != Biblioteca::SUCESSO) {
                    mostrarErro(r);
                    break;
                }
                if (ids.empty()) {
                    std::cout << "A playlist está vazia." << std::endl;
                    break;
                }
                std::list<int>::const_iterator it = ids.begin();
                for (; it != ids.end(); ++it) {
                    Musica musica;
                    if (biblioteca.consultarMusica(*it, musica)
                        == Biblioteca::SUCESSO) {
                        imprimirMusica(musica);
                    }
                }
                break;
            }

            case 11: {
                int id;
                if (!lerInteiro("ID da música: ", id)) {
                    encerrar = true;
                    break;
                }
                Musica musica;
                Biblioteca::Resultado r = biblioteca.consultarMusica(id, musica);
                if (r != Biblioteca::SUCESSO) {
                    mostrarErro(r);
                    break;
                }
                fila.adicionarNoFim(musica);
                std::cout << "Música adicionada ao fim da fila." << std::endl;
                break;
            }

            case 12: {
                int id;
                if (!lerInteiro("ID da música: ", id)) {
                    encerrar = true;
                    break;
                }
                Musica musica;
                Biblioteca::Resultado r = biblioteca.consultarMusica(id, musica);
                if (r != Biblioteca::SUCESSO) {
                    mostrarErro(r);
                    break;
                }
                fila.adicionarNoInicio(musica);
                std::cout << "Música adicionada ao início da fila." << std::endl;
                break;
            }

            case 13: {
                int id;
                if (!lerInteiro("ID da música: ", id)) {
                    encerrar = true;
                    break;
                }
                if (!fila.contemMusica(id)) {
                    std::cout << "Erro: a música não está na fila."
                              << std::endl;
                    break;
                }
                fila.removerMusica(id);
                std::cout << "Música removida da fila." << std::endl;
                break;
            }

            case 14:
                fila.avancar();
                mostrarMusicaAtual(fila);
                break;

            case 15:
                fila.voltar();
                mostrarMusicaAtual(fila);
                break;

            case 16:
                mostrarMusicaAtual(fila);
                break;

            default:
                std::cout << "Opção inválida. Escolha um número entre 0 e 16."
                          << std::endl;
                break;
        }
    }

    return 0;
}
