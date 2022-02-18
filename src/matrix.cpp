#include "queue.cpp"
#include <stdio.h>
#include <string>


// cria nova matriz, alocando memória e com valores zerados
int** new_matrix(int height, int width) {
    int** matrix = new int*[height];
    for ( int i = 0; i < height; i++ ) {
        matrix[i] = new int[width];
        for ( int j = 0; j < width; j++ )
            matrix[i][j] = 0;
    }

    return matrix;
}

// popula a matriz com um conteudo
void pop_matrix(int height, int width, int** matrix, const std::string& content) {
    int i = 0, j = 0;

    for ( const char& c : content ) {

        // ignora espaços
        if ( std::isspace(c) ) continue;

        // popula matriz
        matrix[i][j] = (int) c;

        // proxima coluna
        j++;

        // checa se acabou a linha e troca a linha
        if ( j >= width ) {
            j = 0;
            i++;

            // checa se acabaram as linhas
            if ( i >= height )
                break;
        }
    }
}

int related_components(int height, int width, int** E) {
	int** R = new_matrix(height, width);
	int label = 1;

    // fila
    Queue queue;

    // facilita um bocado essa linha :)
	using pixel = std::pair<int,int>;

	// para cada pixel na matriz de entrada
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			// caso ele nao tenha sido rotulado e for diferente de zero
			// entao temos um novo componente conexo
			if (!R[i][j] && E[i][j]) {
                
				// rotula o pixel e o coloca na fila de processamento
				R[i][j] = label;
				queue.push({j,i});  // (x,y)

				// processa cada pixel conexo aos que estao na fila
				while (!queue.isEmpty()) {
					const auto p = queue.pop();
					const auto x = p.first;
					const auto y = p.second;

					// repete para a vizinhanca-4, quando existir, for
					// diferente de zero e ainda nao tiver sido processada
					if (x - 1 >= 0 && !R[y][x-1] && E[y][x-1]) {
						R[y][x-1] = label;
						queue.push({x-1,y});
					}
					if (x + 1 < width && !R[y][x+1] && E[y][x+1]) {
						R[y][x+1] = label;
						queue.push({x+1,y});
					}
					if (y - 1 >= 0 && !R[y-1][x] && E[y-1][x]) {
						R[y-1][x] = label;
						queue.push({x,y-1});
					}
					if (y + 1 < height && !R[y+1][x] && E[y+1][x]) {
						R[y+1][x] = label;
						queue.push({x,y+1});
					}
				}

				label++;
			}
		}
	}

	delete_matrix(height, R);
	return label - 1;  // retorna o ultimo rotulo efetivamente atribuido
}


// libera memoria da matriz
void delete_matrix(int height, int** matrix) {
    for (int i = 0; i < height; ++i)
        delete[] matrix[i];
    delete[] matrix;
}
