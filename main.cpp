#include "pilha.cpp"
#include "fila.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool validar(const std::string& conteudo) {
    Stack pilha;

    size_t i = 0u;

    while (i < conteudo.length())
    {
        // Calcula o íncio e final da próxima tag do arquivo
        size_t start_position = conteudo.find('<', i);
        size_t end_position = conteudo.find('>', start_position);

        // Caso o find do início falhe, chegamos ao final do arquivo
        if (start_position == std::string::npos) break;

        // Caso a posição do final falhe, temos um erro no arquivo
        if (end_position == std::string::npos) return false;
            
        // Utiliza substring para buscar a tag completa
        std::string tag = conteudo.substr(start_position, end_position + 1 - start_position);
            
        // Incrementa a posição de busca inicial para a posição seguinte ao final da tag atual
        i = end_position + 1;

        // Caso seja uma tag de abertura, insere na pilha com uma / no início
        // que será utilizada depois para comparação
        if (tag[1] != '/') {
            pilha.push(tag.insert(1, "/"));
        } else {
            // Se tiver uma tag de fechamento com a pilha vazia
            // significa que não havia uma tag de abertura, arquivo inválido
            if (pilha.isEmpty()) return false;
            // Se a tag de fechamento for igual ao topo da pilha, desempilha o topo
            else if(pilha.top() == tag) pilha.pop();
            // Do contrário, erro no arquivo
            else return false;  
        }
    }

    return pilha.isEmpty();
}

int componentes_conexos(const std::string& conteudo) {
    Queque
}

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada

    std::ifstream xmlfile (("dataset/{0}.xml", xmlfilename));
    std::stringstream stream;

    stream << xmlfile.rdbuf();
    std::string conteudo = stream.str();

    if(not validar(conteudo)) {
        std::cout << "error\n";
        return 1;
    }

    

    return 0;
}