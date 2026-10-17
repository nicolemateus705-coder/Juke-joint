#include "Biblioteca.hpp"

#include <utility>

Biblioteca::Biblioteca()
    : proximoIdMusica(1), proximoIdPlaylist(1) {
}

Biblioteca::Resultado Biblioteca::cadastrarMusica(const std::string& titulo,
                                                  const std::string& artista,
                                                  int minutos, int segundos,
                                                  const std::string& album,
                                                  int& idGerado) {
    idGerado = 0;

    if (!textoValido(titulo) || !textoValido(artista) || !textoValido(album)
        || !duracaoValida(minutos, segundos)) {
        return ENTRADA_INVALIDA;
    }

    int id = proximoIdMusica++;
    musicas.insert(std::make_pair(id, Musica(id, titulo, artista, minutos, segundos, album)));
    idGerado = id;
    return SUCESSO;
}

Biblioteca::Resultado Biblioteca::consultarMusica(int id, Musica& saida) const {
    std::map<int, Musica>::const_iterator it = musicas.find(id);
    if (it == musicas.end()) {
        return MUSICA_INEXISTENTE;
    }
    saida = it->second;
    return SUCESSO;
}

const std::map<int, Musica>& Biblioteca::listarMusicas() const {
    return musicas;
}

Biblioteca::Resultado Biblioteca::removerMusica(int id, FilaReproducao& fila) {
    std::map<int, Musica>::iterator it = musicas.find(id);
    if (it == musicas.end()) {
        return MUSICA_INEXISTENTE;
    }

    std::map<int, Playlist>::iterator p = playlists.begin();
    for (; p != playlists.end(); ++p) {
        p->second.removerMusica(id);
    }

    fila.removerMusica(id);
    if (fila.getIdAtual() == id) {
        fila.limparMusicaAtual();
    }
    musicas.erase(it);
    return SUCESSO;
}

Biblioteca::Resultado Biblioteca::criarPlaylist(const std::string& nome, int& idGerado) {
    idGerado = 0;

    if (!textoValido(nome)) {
        return ENTRADA_INVALIDA;
    }

    int id = proximoIdPlaylist++;
    playlists.insert(std::make_pair(id, Playlist(id, nome)));
    idGerado = id;
    return SUCESSO;
}

Biblioteca::Resultado Biblioteca::removerPlaylist(int id) {
    std::map<int, Playlist>::iterator it = playlists.find(id);
    if (it == playlists.end()) {
        return PLAYLIST_INEXISTENTE;
    }
    playlists.erase(it);
    return SUCESSO;
}

const std::map<int, Playlist>& Biblioteca::listarPlaylists() const {
    return playlists;
}

Biblioteca::Resultado Biblioteca::listarMusicasDaPlaylist(int idPlaylist,
                                                          std::list<int>& saida) const {
    std::map<int, Playlist>::const_iterator it = playlists.find(idPlaylist);
    if (it == playlists.end()) {
        return PLAYLIST_INEXISTENTE;
    }
    saida = it->second.listarMusicas();
    return SUCESSO;
}

Biblioteca::Resultado Biblioteca::adicionarMusicaNaPlaylist(int idPlaylist, int idMusica) {
    std::map<int, Playlist>::iterator pl = playlists.find(idPlaylist);
    if (pl == playlists.end()) {
        return PLAYLIST_INEXISTENTE;
    }
    if (!musicaExiste(idMusica)) {
        return MUSICA_INEXISTENTE;
    }
    if (pl->second.contemMusica(idMusica)) {
        return MUSICA_JA_NA_PLAYLIST;
    }

    pl->second.adicionarMusica(idMusica);
    return SUCESSO;
}

Biblioteca::Resultado Biblioteca::removerMusicaDaPlaylist(int idPlaylist, int idMusica) {
    std::map<int, Playlist>::iterator pl = playlists.find(idPlaylist);
    if (pl == playlists.end()) {
        return PLAYLIST_INEXISTENTE;
    }
    if (!pl->second.contemMusica(idMusica)) {
        return MUSICA_NAO_ESTA_NA_PLAYLIST;
    }

    pl->second.removerMusica(idMusica);
    return SUCESSO;
}

bool Biblioteca::textoValido(const std::string& texto) const {
    return texto.find_first_not_of(" \t\r\n") != std::string::npos;
}

bool Biblioteca::duracaoValida(int minutos, int segundos) const {
    return minutos >= 0 && segundos >= 0 && segundos <= 59;
}

bool Biblioteca::musicaExiste(int id) const {
    return musicas.find(id) != musicas.end();
}
