#include "FilaReproducao.hpp"

#include <iterator>

FilaReproducao::FilaReproducao()
    : idAtual(0), posAtual(0), temAtual(false) {
}

void FilaReproducao::adicionarNoInicio(const Musica& musica) {
    if (!temAtual) {
        musicas.push_front(musica);
        idAtual = musica.getId();
        posAtual = 0;
        temAtual = true;
        return;
    }

    bool selecaoValidaAntes = selecaoEstaNaFila();
    musicas.push_front(musica);
    if (!selecaoValidaAntes && musica.getId() == idAtual) {
        posAtual = 0;
    } else {
        posAtual++;
    }
}

void FilaReproducao::adicionarNoFim(const Musica& musica) {
    if (!temAtual) {
        musicas.push_back(musica);
        idAtual = musica.getId();
        posAtual = 0;
        temAtual = true;
        return;
    }

    bool selecaoValidaAntes = selecaoEstaNaFila();
    musicas.push_back(musica);
    if (!selecaoValidaAntes && musica.getId() == idAtual) {
        posAtual = musicas.size() - 1;
    }
}

void FilaReproducao::removerMusica(int idMusica) {
    std::list<Musica>::iterator it = musicas.begin();
    std::size_t pos = 0;
    while (it != musicas.end()) {
        if (it->getId() == idMusica) {
            if (pos < posAtual) {
                posAtual--;
            }
            it = musicas.erase(it);
        } else {
            ++it;
        }
        ++pos;
    }
}

void FilaReproducao::avancar() {
    if (!selecaoEstaNaFila()) {
        return;
    }
    posAtual = (posAtual + 1) % musicas.size();
    idAtual = itNaPosicao(posAtual)->getId();
}

void FilaReproducao::voltar() {
    if (!selecaoEstaNaFila()) {
        return;
    }
    if (posAtual == 0) {
        return;
    }
    posAtual--;
    idAtual = itNaPosicao(posAtual)->getId();
}

bool FilaReproducao::getMusicaAtual(Musica& saida) const {
    if (!selecaoEstaNaFila()) {
        return false;
    }
    saida = *itNaPosicao(posAtual);
    return true;
}

int FilaReproducao::getIdAtual() const {
    return idAtual;
}

void FilaReproducao::limparMusicaAtual() {
    temAtual = false;
    idAtual = 0;
    posAtual = 0;
}

std::list<Musica>::iterator FilaReproducao::itNaPosicao(std::size_t pos) {
    std::list<Musica>::iterator it = musicas.begin();
    std::advance(it, pos);
    return it;
}

std::list<Musica>::const_iterator FilaReproducao::itNaPosicao(std::size_t pos) const {
    std::list<Musica>::const_iterator it = musicas.begin();
    std::advance(it, pos);
    return it;
}

bool FilaReproducao::selecaoEstaNaFila() const {
    if (!temAtual) {
        return false;
    }
    if (posAtual >= musicas.size()) {
        return false;
    }
    return itNaPosicao(posAtual)->getId() == idAtual;
}
