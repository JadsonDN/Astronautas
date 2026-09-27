#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

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
        } 
        void morrer(){
            if(vivo){
                vivo = false;
                disponivel = false;
            }
        } // fica morto e indisponivel
        void restaurar(bool v, bool d){
            vivo = v;
            disponivel = d;
        } // so para recarregar do arquivo
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
            for(int i=0; i<(int)cpfs.size(); i++){
                if(cpfs[i] == cpf){
                    return true;
                }
            }
            return false;
        }
        void adicionarAstronauta(string cpf){
            cpfs.push_back(cpf);
        }
        void removerAstronauta(string cpf){
            for(int i=0; i<(int)cpfs.size(); i++){
                if(cpfs[i] == cpf){
                    cpfs.erase(cpfs.begin() + i);
                    return;
                }
            }
        }
        void lancar(){
            estado = "em curso";
        }
        void explodir(){
            estado = "finalizado com explosao";
        }
        void finalizar(){
            estado = "finalizado com sucesso";
        }
        void restaurarEstado(string novoEstado){
            estado = novoEstado;
        } // so para recarregar do arquivo
};

class Agencia {
    private:
        vector<Astronauta> astronautas;
        vector<Voo> voos;
        int buscarAstronauta(string cpf){
            for(int i=0; i<(int)astronautas.size(); i++){
                if(astronautas[i].getCpf() == cpf){
                    return i;
                }
            }
            return -1;
        } // posicao no vector, ou -1
        int buscarVoo(int codigo){
            for(int i=0; i<(int)voos.size(); i++){
                if(voos[i].getCodigo() == codigo){
                    return i;
                }
            }
            return -1;
        } // posicao no vector, ou -1
        int buscarVooEmCurso(string cpf){
            for(int i=0; i<(int)voos.size(); i++){
                if(voos[i].getEstado() == "em curso" && voos[i].temAstronauta(cpf)){
                    return i;
                }
            }
            return -1;
        }
        int contarVoosLancados(string cpf){
            int total = 0;
            for(int j=0; j<(int)voos.size(); j++){
                if(voos[j].getEstado() != "planejado" && voos[j].temAstronauta(cpf)){
                    total++;
                }
            }
            return total;
        }
    public:
        string cadastrarAstronauta(string cpf, string nome, int idade){
            if(buscarAstronauta(cpf) != -1){
                return "ERRO: astronauta com CPF " + cpf + " ja cadastrado";
            }
            astronautas.push_back(Astronauta(cpf, nome, idade));
            return "OK: astronauta " + cpf + " cadastrado";
        }
        string cadastrarVoo(int codigo){
            if(buscarVoo(codigo) != -1){
                return "ERRO: voo " + to_string(codigo) + " ja cadastrado";
            }
            voos.push_back(Voo(codigo));
            return "OK: voo " + to_string(codigo) + " cadastrado";
        }
        string adicionarAstronauta(string cpf, int codigo){
            int buscaA = buscarAstronauta(cpf);
            if(buscaA == -1){
                return "ERRO: astronauta " + cpf + " nao cadastrado";
            }
            int buscaV = buscarVoo(codigo);
            if(buscaV == -1){
                return "ERRO: voo " + to_string(codigo) + " nao cadastrado";
            }
            if(voos[buscaV].getEstado() != "planejado"){
                return "ERRO: voo " + to_string(codigo) + " nao esta planejado";
            }
            if(!astronautas[buscaA].estaVivo()){
                return "ERRO: astronauta " + cpf + " esta morto";
            }
            if(voos[buscaV].temAstronauta(cpf)){
                return "ERRO: astronauta " + cpf + " ja esta no voo " + to_string(codigo);
            }
            voos[buscaV].adicionarAstronauta(cpf);
            return "OK: astronauta " + cpf + " adicionado ao voo " + to_string(codigo);
        } // nao chama embarcar() aqui: disponibilidade so e consumida no lancamento
        string removerAstronauta(string cpf, int codigo){
            int buscaA = buscarAstronauta(cpf);
            if(buscaA == -1){
                return "ERRO: astronauta " + cpf + " nao cadastrado";
            }
            int buscaV = buscarVoo(codigo);
            if(buscaV == -1){
                return "ERRO: voo " + to_string(codigo) + " nao cadastrado";
            }
            if(voos[buscaV].getEstado() != "planejado"){
                return "ERRO: voo " + to_string(codigo) + " nao esta planejado";
            }
            if(!voos[buscaV].temAstronauta(cpf)){
                return "ERRO: astronauta " + cpf + " nao esta no voo " + to_string(codigo);
            }
            voos[buscaV].removerAstronauta(cpf);
            return "OK: astronauta " + cpf + " removido do voo " + to_string(codigo);
        }
        string lancarVoo(int codigo){
            int buscaV = buscarVoo(codigo);
            if(buscaV == -1){
                return "ERRO: voo " + to_string(codigo) + " nao cadastrado";
            }
            if(voos[buscaV].getEstado() != "planejado"){
                return "ERRO: voo " + to_string(codigo) + " nao esta planejado";
            }
            if(voos[buscaV].getQuantidadeAstronautas() == 0){
                return "ERRO: voo " + to_string(codigo) + " nao possui astronautas";
            }
            for(int i=0; i<voos[buscaV].getQuantidadeAstronautas(); i++){
                string cpf = voos[buscaV].getCpf(i);
                int buscaA = buscarAstronauta(cpf);
                if(!astronautas[buscaA].estaVivo()){
                    return "ERRO: astronauta " +cpf+ " esta morto";
                }
                if(!astronautas[buscaA].estaDisponivel()){
                    return "ERRO: astronauta " +cpf+ " esta indisponivel";
                }
            } 
            voos[buscaV].lancar();
            for(int i=0; i<voos[buscaV].getQuantidadeAstronautas(); i++){
                int buscaA = buscarAstronauta(voos[buscaV].getCpf(i));
                astronautas[buscaA].embarcar();
            } 
            return "OK: voo " + to_string(codigo) + " lancado";
        }
        string explodirVoo(int codigo){
            int buscaV = buscarVoo(codigo);
            if(buscaV == -1){
                return "ERRO: voo " + to_string(codigo) + " nao cadastrado";
            }
            if(voos[buscaV].getEstado() != "em curso"){
                return "ERRO: voo " + to_string(codigo) + " nao esta em curso";
            }
            voos[buscaV].explodir();
            for(int i=0; i<voos[buscaV].getQuantidadeAstronautas(); i++){
                int buscaA = buscarAstronauta(voos[buscaV].getCpf(i));
                astronautas[buscaA].morrer();
            } 
            return "OK: voo " + to_string(codigo) + " explodiu";
        }
        string finalizarVoo(int codigo){
            int buscaV = buscarVoo(codigo);
            if(buscaV == -1){
                return "ERRO: voo " + to_string(codigo) + " nao cadastrado";
            }
            if(voos[buscaV].getEstado() != "em curso"){
                return "ERRO: voo " + to_string(codigo) + " nao esta em curso";
            }
            voos[buscaV].finalizar();
            for(int i=0; i<voos[buscaV].getQuantidadeAstronautas(); i++){
                int buscaA = buscarAstronauta(voos[buscaV].getCpf(i));
                astronautas[buscaA].desembarcar();
            } 
            return "OK: voo " + to_string(codigo) + " finalizado com sucesso";
        }
        void listarVoos(){
            cout << "LISTA DE VOOS" << endl;
            vector<string> estados = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosao"};
            for(int e=0; e<(int)estados.size(); e++){ 
                cout << "== " << estados[e] << " ==" << endl;
                bool algum = false;
                for(int i=0; i<(int)voos.size(); i++){ 
                    if(voos[i].getEstado() == estados[e]){
                        algum = true;
                        cout << "Voo " << voos[i].getCodigo() << ": ";
                        int qtd = voos[i].getQuantidadeAstronautas();
                        if(qtd == 0){
                            cout << "sem astronautas";
                        } else {
                            for(int j=0; j<qtd; j++){
                                string cpf = voos[i].getCpf(j);
                                int buscaA = buscarAstronauta(cpf);
                                cout << cpf << " " << astronautas[buscaA].getNome(); 
                                if(j < qtd - 1){
                                    cout << ", ";
                                }
                            }
                        }
                        cout << endl;
                    }
                }
                if(!algum){
                    cout << "(nenhum)" << endl;
                } 
            }
        }
        void listarMortos(){
            cout << "ASTRONAUTAS MORTOS" << endl;
            bool temMorto = false;
            for(int i=0; i<(int)astronautas.size(); i++){ 
                if(!astronautas[i].estaVivo()){
                    temMorto = true;
                    cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " - voos:";
                    bool participou = false;
                    for(int j=0; j<(int)voos.size(); j++){
                        if(voos[j].getEstado() != "planejado" && voos[j].temAstronauta(astronautas[i].getCpf())){
                            cout << " " << voos[j].getCodigo();
                            participou = true;
                        }
                    }
                    if(!participou){
                        cout << " nenhum";
                    }
                    cout << endl;
                }
            }
            if(!temMorto){
                cout << "(nenhum)" << endl;
            } 
        }
        void listarAstronautas(){
            cout << "LISTA DE ASTRONAUTAS" << endl;
            vector<string> grupos = {"disponiveis", "em voo", "mortos"};
            for(int g=0; g<(int)grupos.size(); g++){ 
                cout << "== " << grupos[g] << " ==" << endl;
                bool algum = false;
                for(int i=0; i<(int)astronautas.size(); i++){ 
                    int emVoo = buscarVooEmCurso(astronautas[i].getCpf());
                    int grupo = 0;
                    if(!astronautas[i].estaVivo()){
                        grupo = 2;
                    } else if(emVoo != -1){
                        grupo = 1;
                    }
                    if(grupo != g){
                        continue;
                    }
                    algum = true;
                    cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                         << " (" << astronautas[i].getIdade() << " anos)";
                    if(grupo == 1){
                        cout << " - voo " << voos[emVoo].getCodigo();
                    }
                    cout << endl;
                }
                if(!algum){
                    cout << "(nenhum)" << endl;
                } 
            }
        }
        void historico(string cpf){
            int buscaA = buscarAstronauta(cpf);
            if(buscaA == -1){
                cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
                return;
            }
            cout << "HISTORICO DE " << cpf << " " << astronautas[buscaA].getNome() << endl;
            bool algum = false;
            for(int j=0; j<(int)voos.size(); j++){ 
                if(voos[j].getEstado() != "planejado" && voos[j].temAstronauta(cpf)){
                    algum = true;
                    cout << "voo " << voos[j].getCodigo() << ": " << voos[j].getEstado() << endl;
                }
            }
            if(!algum){
                cout << "(nenhum voo)" << endl;
            } 
        }
        void relatorio(){
            int planejados = 0, emCurso = 0, sucesso = 0, explosao = 0;
            for(int i=0; i<(int)voos.size(); i++){
                string estado = voos[i].getEstado();
                if(estado == "planejado"){
                    planejados++;
                } else if(estado == "em curso"){
                    emCurso++;
                } else if(estado == "finalizado com sucesso"){
                    sucesso++;
                } else {
                    explosao++;
                }
            }
            int cadastrados = (int)astronautas.size();
            int vivos = 0, mortos = 0;
            for(int i=0; i<(int)astronautas.size(); i++){
                if(astronautas[i].estaVivo()){
                    vivos++;
                } else {
                    mortos++;
                }
            }
            int melhor = -1;
            int experiencia = 0;
            for(int i=0; i<(int)astronautas.size(); i++){
                int atual = contarVoosLancados(astronautas[i].getCpf());
                if(atual > experiencia){
                    experiencia = atual;
                    melhor = i;
                }
            }
            cout << "RELATORIO" << endl;
            cout << "voos planejados: " << planejados << endl;
            cout << "voos em curso: " << emCurso << endl;
            cout << "voos finalizados com sucesso: " << sucesso << endl;
            cout << "voos finalizados com explosao: " << explosao << endl;
            cout << "astronautas cadastrados: " << cadastrados << endl;
            cout << "astronautas vivos: " << vivos << endl;
            cout << "astronautas mortos: " << mortos << endl;
            cout << "astronauta mais experiente: ";
            if(experiencia == 0){
                cout << "(nenhum)" << endl;
            } else {
                cout << astronautas[melhor].getCpf() << " " << astronautas[melhor].getNome()
                    << " (voos lancados: " << experiencia << ")" << endl;
            }
            cout << "taxa de sucesso: ";
            int finalizados = sucesso + explosao;
            if(finalizados == 0){
                cout << "(nenhum voo finalizado)" << endl;
            } else {
                cout << (sucesso * 100 / finalizados) << "%" << endl;
            }
        }
        string salvar(string nomeArquivo){
            ofstream arq(nomeArquivo);
            if(!arq.is_open()){
                return "ERRO: nao foi possivel salvar em " + nomeArquivo;
            }
            // A cpf idade vivo disponivel nome
            for(int i=0; i<(int)astronautas.size(); i++){
                arq << "A " << astronautas[i].getCpf() << " " << astronautas[i].getIdade() << " ";
                arq << (astronautas[i].estaVivo() ? 1 : 0) << " ";
                arq << (astronautas[i].estaDisponivel() ? 1 : 0) << " ";
                arq << astronautas[i].getNome() << endl;
            }
            // V codigo quantidade cpfs estado
            for(int j=0; j<(int)voos.size(); j++){
                int qtd = voos[j].getQuantidadeAstronautas();
                arq << "V " << voos[j].getCodigo() << " " << qtd;
                for(int k=0; k<qtd; k++){
                    arq << " " << voos[j].getCpf(k);
                }
                arq << " " << voos[j].getEstado() << endl;
            }
            arq.close();
            if(!arq){
                return "ERRO: nao foi possivel salvar em " + nomeArquivo;
            }
            return "OK: dados salvos em " + nomeArquivo;
        }
        string carregar(string nomeArquivo){
            ifstream arq(nomeArquivo);
            if(!arq.is_open()){
                return "ERRO: nao foi possivel carregar de " + nomeArquivo;
            } // arquivo nao abriu: os dados atuais continuam como estavam
            astronautas.clear();
            voos.clear();
            char tipo;
            while(arq >> tipo){
                if(tipo == 'A'){
                    string cpf, nome;
                    int idade, vivo, disponivel;
                    arq >> cpf >> idade >> vivo >> disponivel;
                    getline(arq >> ws, nome);
                    astronautas.push_back(Astronauta(cpf, nome, idade));
                    int ultimo = (int)astronautas.size() - 1;
                    astronautas[ultimo].restaurar(vivo == 1, disponivel == 1);
                } else if(tipo == 'V'){
                    int codigo, qtd;
                    string estado;
                    arq >> codigo >> qtd;
                    vector<string> cpfs;
                    for(int i=0; i<qtd; i++){
                        string cpf;
                        arq >> cpf;
                        cpfs.push_back(cpf);
                    }
                    getline(arq >> ws, estado);
                    Voo voo(codigo);
                    voo.restaurarEstado(estado);
                    for(int i=0; i<(int)cpfs.size(); i++){
                        voo.adicionarAstronauta(cpfs[i]);
                    }
                    voos.push_back(voo);
                }
            }
            arq.close();
            return "OK: dados carregados de " + nomeArquivo;
        }
};

int main() {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY); 
#endif
    Agencia agencia;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome); // o nome vem por ultimo e pode ter espacos
            cout << agencia.cadastrarAstronauta(cpf, nome, idade) << endl;
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << agencia.cadastrarVoo(codigo) << endl;
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << agencia.adicionarAstronauta(cpf, codigo) << endl;
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << agencia.removerAstronauta(cpf, codigo) << endl;
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << agencia.lancarVoo(codigo) << endl;
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            cout << agencia.explodirVoo(codigo) << endl;
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << agencia.finalizarVoo(codigo) << endl;
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();
        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.historico(cpf);
        } else if (comando == "RELATORIO") {
            agencia.relatorio();
        } else if (comando == "SALVAR") {
            string arquivo;
            cin >> arquivo;
            cout << agencia.salvar(arquivo) << endl;
        } else if (comando == "CARREGAR") {
            string arquivo;
            cin >> arquivo;
            cout << agencia.carregar(arquivo) << endl;
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}