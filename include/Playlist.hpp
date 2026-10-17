#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>
#include <list>
#include <set>

class Playlist {
public:
    Playlist(int id, const std::string& nome);

    int getId() const;
    const std::string& getNome() const;

    void adicionarMusica(int idMusica);
    void removerMusica(int idMusica);
    const std::list<int>& listarMusicas() const;
    bool contemMusica(int idMusica) const;

private:
    int id;
    std::string nome;
    std::list<int> musicas;
    std::set<int> musicasSet;
};

#endif
