#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Parte 1: escreva aqui as classes Astronauta, Voo e Agencia.
// Depois, em cada comando, apague a linha do cout com "TODO" e descomente
// a chamada ao metodo da Agencia.
class Astronauta {
    private:
        string cpf;
        string nome;
        int idade;
        bool vivo;
        bool disponivel;
    public:
        Astronauta(string cpf, string nome, int idade){
            this->cpf = cpf;
            this->nome = nome;
            this->idade = idade;
            this->vivo = true;
            this->disponivel = true;
        }
        string getCpf(){
            return cpf;
        }
        string getNome(){
            return nome;
        }
        int getIdade(){
            return idade;
        }
        bool estaVivo(){
            return vivo;
        }
        bool estaDisponivel(){
            return disponivel;
        }
        void embarcar(){
            if(disponivel){
                disponivel = false;
            }
        } // fica indisponivel
        void desembarcar(){
            if(vivo){
                disponivel = true;
            }
        } // volta a ficar disponivel, se estiver vivo
        void morrer(){
            if(vivo){
                vivo = false;
                disponivel = false;
            }
        }; // fica morto e indisponivel
};
class Voo {
    private:
        int codigo;
        string estado;
        vector<string> cpfs;
    public:
        Voo(int codigo){
            this->codigo = codigo;
            this->estado = "planejado";
            cpfs = {};
        }
        int getCodigo(){
            return codigo;
        }
        string getEstado(){
            return estado;
        }
        int getQuantidadeAstronautas(){
            return cpfs.size();
        }
        string getCpf(int posicao){
            return cpfs[posicao];
        }
        bool temAstronauta(string cpf){
            for(int i=0; i<cpfs.size();i++){
                if(cpfs[i] == cpf){
                    return true;
                }
            }
            return false;
        }
        void adicionarAstronauta(string cpf){
            if(temAstronauta(cpf) == false){
                cpfs.push_back(cpf);
            }
        }
        bool removerAstronauta(string cpf){
            if(temAstronauta(cpf)){
                for(int i=0; i<cpfs.size();i++){
                    if(cpfs[i] == cpf){
                        cpfs.erase(cpfs.begin() + i);
                        return true;
                    }
                }
            }
            else{
                return false;
            }
        } // false se o CPF nao estava no voo
        void lancar(){
            estado = "em curso";
        }
        void explodir(){
            estado = "finalizado com explosao";
        }
        void finalizar(){
            estado = "finalizado com sucesso";
        }
};
class Agencia {
    private:
        vector<Astronauta> astronautas;
        vector<Voo> voos;
        int buscarAstronauta(string cpf); // posicao no vector, ou -1
        int buscarVoo(int codigo); // posicao no vector, ou -1
    public:
        void cadastrarAstronauta(string cpf, string nome, int idade);
        void cadastrarVoo(int codigo);
        void adicionarAstronauta(string cpf, int codigo);
        void removerAstronauta(string cpf, int codigo);
        void lancarVoo(int codigo);
        void explodirVoo(int codigo);
        void finalizarVoo(int codigo);
        void listarVoos();
        void listarMortos();
};
int main() {
    // TODO: criar a Agencia aqui, por exemplo:  Agencia agencia;
    string comando;

    while (cin >> comando) {   // le uma palavra; para no FIM ou quando a entrada acaba
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);   // o nome vem por ultimo e pode ter espacos
            cout << "TODO " << comando << endl;
            // TODO: agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            cout << "TODO " << comando << endl;
            // TODO: agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            cout << "TODO " << comando << endl;
            // TODO: agencia.listarMortos();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}
