#include "stack.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


std::string get_content(const std::string& origin, const std::string& begin, const std::string& end, size_t& start) {
    size_t start_pos = origin.find(begin, start);
	size_t close_pos = origin.find(end, start_pos);

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
