#ifndef MUSICA_HPP
#define MUSICA_HPP

#include <string>

class Musica {
public:
    Musica();
    Musica(int id, const std::string& titulo, const std::string& artista,
           int minutos, int segundos, const std::string& album);

    int getId() const;
    std::string getTitulo() const;
    std::string getArtista() const;
    int getMinutos() const;
    int getSegundos() const;
    std::string getAlbum() const;

    bool operator==(const Musica& outra) const;

private:
    int id;
    std::string titulo;
    std::string artista;
    int minutos;
    int segundos;
    std::string album;
};

#endif
