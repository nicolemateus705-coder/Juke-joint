#ifndef FILA_REPRODUCAO_HPP
#define FILA_REPRODUCAO_HPP

#include <cstddef>
#include <list>

#include "Musica.hpp"

class FilaReproducao {
public:
    FilaReproducao();

    void adicionarNoInicio(const Musica& musica);
    void adicionarNoFim(const Musica& musica);
    void removerMusica(int idMusica);
    bool contemMusica(int idMusica) const;

    void avancar();
    void voltar();

    bool getMusicaAtual(Musica& saida) const;
    int getIdAtual() const;
    void limparMusicaAtual();

private:
    std::list<Musica>::iterator itNaPosicao(std::size_t pos);
    std::list<Musica>::const_iterator itNaPosicao(std::size_t pos) const;
    bool selecaoEstaNaFila() const;

    std::list<Musica> musicas;
    int idAtual;
    std::size_t posAtual;
    bool temAtual;
};

#endif
