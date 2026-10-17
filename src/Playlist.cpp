#include "Playlist.hpp"

Playlist::Playlist(int id, const std::string& nome)
    : id(id), nome(nome) {
}

int Playlist::getId() const {
    return id;
}

const std::string& Playlist::getNome() const {
    return nome;
}

void Playlist::adicionarMusica(int idMusica) {
    if (musicasSet.find(idMusica) == musicasSet.end()) {
        musicasSet.insert(idMusica);
        musicas.push_back(idMusica);
    }
}

void Playlist::removerMusica(int idMusica) {
    if (musicasSet.find(idMusica) != musicasSet.end()) {
        musicasSet.erase(idMusica);
        musicas.remove(idMusica);
    }
}

const std::list<int>& Playlist::listarMusicas() const {
    return musicas;
}

bool Playlist::contemMusica(int idMusica) const {
    return musicasSet.find(idMusica) != musicasSet.end();
}
