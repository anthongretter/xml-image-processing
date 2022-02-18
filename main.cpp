// Anthon Porath Gretter e Rian Block Serena

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

class Stack {

    public:
        Stack(){
            max_size = DEFAULT_SIZE;
            data = new std::string[max_size];
            top = -1;
        };

        explicit Stack(int size){
            max_size = size;
            data = new std::string[max_size];
            top = -1;
        };

        ~Stack(){
            delete [] data;
        };

        std::string peak(){
            return data[top];
        };
        std::string pop(){
            if(isEmpty()){
                throw std::out_of_range("pilha vazia");
            }
            top -=1;
            return data[top+1];
        };

        int push(std::string value){
            if(isFull()){
                return -1;
            }
            top += 1;
            data[top] = value;
            return top;
        };

        bool isEmpty(){
            return top == -1;
        };

        bool isFull(){
            return top == max_size-1;
        }

    private:
        std::string* data;
        int const DEFAULT_SIZE = 10;
        int max_size;
        int top;
};


class Queue {
    public:

        Queue(){
            size_ = 0;
            max_size_ = DEFAULT_SIZE;
            data = new std::pair<int,int>[max_size_];
            begin_ = 0;
            end_ = 0;
        };

        explicit Queue(int max){
            size_ = 0;
            max_size_ = max;
            data = new std::pair<int,int>[max_size_];
            begin_ = 0;
            end_ = 0;
        };

        ~Queue(){
            delete [] data;
        };

        void clear(){
            while (!empty()) {
                pop();
            }
        };
        bool full(){
            return (size_ == max_size_);
        };
        bool empty(){
            return (size_ == 0);
        };
        void push(std::pair<int,int> value){
            if (full()) {
                throw std::out_of_range("fila cheia");
            }
            data[begin_] = value;
            begin_++;
            size_++;
            if (begin_ == static_cast<int>(max_size_)) {
                begin_ = 0;
            }
        };
        std::pair<int,int> pop(){
            if (empty()) {
                throw std::out_of_range("fila vazia");
            }
            std::pair<int,int> last_in_line = data[end_];
            end_++;
            size_--;
            if (end_ == static_cast<int>(max_size_)) {
                end_ = 0;
            }
            return last_in_line;

        };
        std::pair<int,int> back(){
            if (empty()) {
                throw std::out_of_range("fila vazia");
            }
            return data[begin_-1];
        };


    private:
        std::pair<int,int>* data;

        std::size_t size_;
        std::size_t max_size_;
        int begin_;  // indice do inicio (para fila circular)
        int end_;  // indice do fim (para fila circular)
        static const auto DEFAULT_SIZE = 500;

};


namespace xml {

std::string get_content(const std::string& origin, const std::string& begin, const std::string& end, size_t& start) {
    size_t start_pos = origin.find(begin, start);
	size_t close_pos = origin.find(end, start_pos);

    start = close_pos;

	start_pos += begin.length();
	return origin.substr(start_pos, close_pos - start_pos);
}

std::string get_content(const std::string& origin, const std::string& begin, const std::string& end) {
    size_t start_pos = origin.find(begin, 0);
	size_t close_pos = origin.find(end, start_pos);

	start_pos += begin.length();
	return origin.substr(start_pos, close_pos - start_pos);
}


bool validate(const std::string& xml) {
    Stack stack;
    size_t i = 0u;

    while ( i < xml.length() )
    {
        // Calcula o íncio e final da próxima tag do arquivo
        size_t start_position = xml.find('<', i);
        size_t end_position = xml.find('>', start_position);

        // Caso o find do início falhe, chegamos ao final do arquivo
        if ( start_position == std::string::npos ) break;

        // Caso a posição do final falhe, temos um erro no arquivo
        if ( end_position == std::string::npos ) return false;
            
        // Utiliza substring para buscar a tag completa
        std::string tag = xml.substr(start_position, end_position + 1 - start_position);
            
        // Incrementa a posição de busca inicial para a posição seguinte ao final da tag atual
        i = end_position + 1;

        // Caso seja uma tag de abertura, insere na stack com uma / no início
        // que será utilizada depois para comparação
        if ( tag[1] != '/' ) {
            stack.push(tag.insert(1, "/"));
        } else {
            // Se tiver uma tag de fechamento com a stack vazia
            // significa que não havia uma tag de abertura, arquivo inválido
            if ( stack.isEmpty() ) return false;
            // Se a tag de fechamento for igual ao topo da stack, desempilha o topo
            else if ( stack.peak() == tag ) stack.pop();
            // Do contrário, erro no arquivo
            else return false;  
        }
    }

    return stack.isEmpty();
}

}



namespace matrix {

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

// libera memoria da matriz
void delete_matrix(int height, int** matrix) {
    for (int i = 0; i < height; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

// popula a matriz com um conteudo
int** pop_matrix(int height, int width, int** &matrix, const std::string& content) {
    int i = 0, j = 0;

    for ( const char& c : content ) {

        // ignora espaços
        if ( std::isspace(c) ) continue;

        // ignora quebras
        if (c == '\n') continue;

        // popula matriz
        matrix[i][j] = c - '0';

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
    return matrix;
}

int related_components(int height, int width, int** E) {
	int** R = new_matrix(height, width);
	using pixel = std::pair<int,int>;
	int label = 1;

    // fila
    Queue waiting_line;

	// para cada pixel na matriz de entrada
	for ( int i = 0; i < height; ++i ) {
		for ( int j = 0; j < width; ++j ) {

			// caso ele nao tenha sido rotulado e for diferente de zero
			// entao temos um novo componente conexo
			if ( !R[i][j] && E[i][j] ) {
                
				// rotula o pixel e o coloca na fila de processamento
				R[i][j] = label;
				waiting_line.push({i,j});  // (x,y)

				// processa cada pixel conexo aos que estao na fila
				while ( !waiting_line.empty() ) {
                    pixel p = waiting_line.pop();
					const auto x = p.first;
					const auto y = p.second;

					// repete para a vizinhanca-4, quando existir, for
					// diferente de zero e ainda nao tiver sido processada
					if ( y > 0 && !R[x][y-1] && E[x][y-1] ) {
						R[x][y-1] = label;
						waiting_line.push({x,y-1});
					}
					if ( y < (width - 1) && !R[x][y+1] && E[x][y+1] ) {
						R[x][y+1] = label;
						waiting_line.push({x,y+1});
					}
					if ( x > 0 && !R[x-1][y] && E[x-1][y] ) {
						R[x-1][y] = label;
						waiting_line.push({x-1,y});
					}
					if ( x < (height - 1) && !R[x+1][y] && E[x+1][y] ) {
						R[x+1][y] = label;
						waiting_line.push({x+1,y});
					}
				}

				label++;
			}
		}
    }

	delete_matrix(height, R);
	return label - 1;  // retorna o ultimo rotulo efetivamente atribuido
}

}



int main() {
    using namespace matrix;
    using namespace xml;
    
    // entrada
    char xmlfilename[100];
    std::cin >> xmlfilename;

    // arquivo xml
    std::ifstream xmlfile (xmlfilename);

    // "traduzindo" xml para o formato string
    std::stringstream stream;
    stream << xmlfile.rdbuf();
    std::string xmlstring = stream.str();

    // valida o xml
    if ( not validate(xmlstring) ) {
        std::cout << "error\n";
        return -1;
    }

    // posicao que comeca a procurar proxima imagem no arquivo
    size_t pos_start_searching = 0;
    while ( pos_start_searching < xmlstring.length() ) {
        // imagem em string
        const std::string img = get_content(xmlstring, "<img>", "</img>", pos_start_searching);
        if ( pos_start_searching >= xmlstring.length() ) break;

        // nome, sua altura e largura da imagem
        const std::string name = get_content(img, "<name>", "</name>");
        int height = std::stoi(get_content(img, "<height>", "</height>"));
        int width = std::stoi(get_content(img, "<width>", "</width>"));

        // cria matriz e depois popula com os dados da imagem
        int** img_matrix = new_matrix(height, width);
        img_matrix = pop_matrix(height, width, img_matrix, get_content(img, "<data>", "</data>"));

        // plota nome da imagem e número de componentes conexos
        std::cout << name << ' ' << related_components(height, width, img_matrix) << std::endl;

        // libera mem
        delete_matrix(height, img_matrix);
    }

    return 0;
}
