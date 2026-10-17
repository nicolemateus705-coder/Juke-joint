#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <list>
#include <map>
#include <string>

#include "FilaReproducao.hpp"
#include "Musica.hpp"
#include "Playlist.hpp"

class Biblioteca {
public:
    enum Resultado {
        SUCESSO,
        MUSICA_INEXISTENTE,
        PLAYLIST_INEXISTENTE,
        ENTRADA_INVALIDA,
        MUSICA_JA_NA_PLAYLIST,
        MUSICA_NAO_ESTA_NA_PLAYLIST
    };

    Biblioteca();

    Resultado cadastrarMusica(const std::string& titulo, const std::string& artista,
                              int minutos, int segundos, const std::string& album,
                              int& idGerado);
    Resultado consultarMusica(int id, Musica& saida) const;
    const std::map<int, Musica>& listarMusicas() const;
    Resultado removerMusica(int id, FilaReproducao& fila);

    Resultado criarPlaylist(const std::string& nome, int& idGerado);
    Resultado removerPlaylist(int id);
    const std::map<int, Playlist>& listarPlaylists() const;
    Resultado listarMusicasDaPlaylist(int idPlaylist, std::list<int>& saida) const;

    Resultado adicionarMusicaNaPlaylist(int idPlaylist, int idMusica);
    Resultado removerMusicaDaPlaylist(int idPlaylist, int idMusica);

private:
    bool textoValido(const std::string& texto) const;
    bool duracaoValida(int minutos, int segundos) const;
    bool musicaExiste(int id) const;

    std::map<int, Musica> musicas;
    std::map<int, Playlist> playlists;
    int proximoIdMusica;
    int proximoIdPlaylist;
};

#endif
