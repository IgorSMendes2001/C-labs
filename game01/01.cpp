#include <iostream>

using namespace std;

// ESTRUTURA DA FASE
struct Fase {
    int linhas;
    int colunas;
    char** grade;    // Ponteiro para ponteiro (Matriz Dinâmica)
    bool temChave;
    int pX, pY;      // Coordenadas do jogador
};

// FUNÇÃO PARA CRIAR O MAPA USANDO PONTEIROS
// Aqui alocamos memória na Heap para a nossa matriz
char** alocarMapa(int l, int c) {
    char** m = new char*[l]; // Aloca o array de ponteiros (linhas)
    for (int i = 0; i < l; i++) {
        m[i] = new char[c];  // Aloca o array de caracteres (colunas)
    }
    return m;
}

// FUNÇÃO PARA LIMPAR A MEMÓRIA (Importante para evitar Memory Leak)
void liberarMapa(char** m, int l) {
    for (int i = 0; i < l; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// FUNÇÃO PARA DESENHAR O JOGO
void renderizar(Fase* f) {
    // Comando para limpar o console no ambiente Linux/Replit
    system("clear");

    cout << "--- FASE 1: ENCONTRE A CHAVE (K) E VÁ PARA A PORTA (D) ---" << endl;
    
    for (int i = 0; i < f->linhas; i++) {
        for (int j = 0; j < f->colunas; j++) {
            // Acessando a matriz via ponteiro
            cout << f->grade[i][j] << " ";
        }
        cout << endl;
    }

    if (f->temChave) cout << "\n[Status: Voce pegou a chave!]" << endl;
    else cout << "\n[Status: Procurando a chave...]" << endl;
    
    cout << "Comandos: W (cima), S (baixo), A (esquerda), D (direita) + Enter: ";
}

int main() {
    // Inicialização da Fase 1
    Fase nivel1;
    nivel1.linhas = 7;
    nivel1.colunas = 7;
    nivel1.temChave = false;
    nivel1.pX = 1; 
    nivel1.pY = 1;
    nivel1.grade = alocarMapa(nivel1.linhas, nivel1.colunas);

    // Preenchendo o cenário inicial
    for (int i = 0; i < nivel1.linhas; i++) {
        for (int j = 0; j < nivel1.colunas; j++) {
            if (i == 0 || i == 6 || j == 0 || j == 6) nivel1.grade[i][j] = '#'; // Paredes
            else nivel1.grade[i][j] = '.'; // Espaço vazio
        }
    }

    // Posicionando elementos com ponteiros
    nivel1.grade[nivel1.pX][nivel1.pY] = 'P'; // Player
    nivel1.grade[3][3] = '#';                 // Obstáculo central
    nivel1.grade[3][4] = '#';                 // Obstáculo central
    nivel1.grade[5][5] = 'K';                 // Key (Chave)
    nivel1.grade[1][5] = 'D';                 // Door (Porta)

    char movimento;
    while (true) {
        renderizar(&nivel1);
        cin >> movimento; // No Replit, você digita e dá Enter

        int proxX = nivel1.pX;
        int proxY = nivel1.pY;

        if (movimento == 'w') proxX--;
        if (movimento == 's') proxX++;
        if (movimento == 'a') proxY--;
        if (movimento == 'd') proxY++;

        // LÓGICA DE COLISÃO USANDO A GRADE (PONTEIRO)
        char destino = nivel1.grade[proxX][proxY];

        if (destino == '#') {
            continue; // Bateu na parede ou obstáculo
        }

        if (destino == 'K') {
            nivel1.temChave = true;
        }

        if (destino == 'D') {
            if (nivel1.temChave) {
                renderizar(&nivel1);
                cout << "\nPARABENS! Voce abriu a porta e passou para a Fase 2!" << endl;
                break;
            } else {
                continue; // Porta trancada
            }
        }

        // Atualização da posição na memória
        nivel1.grade[nivel1.pX][nivel1.pY] = '.'; // Limpa onde o player estava
        nivel1.pX = proxX;
        nivel1.pY = proxY;
        nivel1.grade[nivel1.pX][nivel1.pY] = 'P'; // Coloca o player no novo endereço
    }

    // IMPORTANTE: Liberar a memória antes de fechar o programa
    liberarMapa(nivel1.grade, nivel1.linhas);

    return 0;
}