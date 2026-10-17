#include "Musica.hpp"

Musica::Musica()
    : id(0), titulo(""), artista(""), minutos(0), segundos(0), album("") {
}

Musica::Musica(int id, const std::string& titulo, const std::string& artista,
               int minutos, int segundos, const std::string& album)
    : id(id), titulo(titulo), artista(artista),
      minutos(minutos), segundos(segundos), album(album) {
}

int Musica::getId() const {
    return id;
}

std::string Musica::getTitulo() const {
    return titulo;
}

std::string Musica::getArtista() const {
    return artista;
}

int Musica::getMinutos() const {
    return minutos;
}

int Musica::getSegundos() const {
    return segundos;
}

std::string Musica::getAlbum() const {
    return album;
}

bool Musica::operator==(const Musica& outra) const {
    return id == outra.id;
}
