

int** new_matrix(int heigth, int width) {
    int** matrix = new int*[heigth];
    for (int i = 0; i < heigth; i++) {
        matrix[i] = new int[width];
        for (int j = 0; i < width; i++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void delete_matrix(int** matrix)