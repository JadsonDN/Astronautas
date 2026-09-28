# Diário da atividade

Escreva com as suas palavras. Frases curtas bastam. Não cole a conversa inteira
com a IA. Cole só os pedidos que você enviou.

## Ambiente

- Versão do OpenCode (`opencode --version`): 1.18.33
- Modelo usado:  opencode zen -- Big Pickle

## Parte 1: antes de programar

- O que cada classe guarda: 
  astronauta guarda uma lista de todos os astronautas alem de guardar todos os dados dos astronautas, e se esta vivo e tambem disponivel. ja no voo guarda as informaçoes dos voos alem de um vetor com todos os cpfs dos astronaltas e ocorre as checagens de adiçao ou exclusao dos seus cpfs. A agencia é o coraçao do codgo, tendo dois vetores de armazemamento de astronautas e de voos, funçoes para lidar com as demandas gerais go projeto, e onde fica os avisos de erro ou de acerto.
- O que acontece em `LANCAR_VOO`, em palavras: a funçao que literalmente lança o voo, checando os estados do voo e de todos os cpfs ligados a astronautas registrados nesse voo, e mudando os seus estados. 
- Uma dúvida que eu tinha antes de começar: eu estive me duvida se era para todas as classes serem implementadas dentro de main.cpp, por conta das notas que me fizeram entender isso, fiz dessa forma, mas acredito agora que essa nao era a ideia.

## Parte 1: uso de IA para entender algo

- O que perguntei (ou "não usei"): perguntei sobre os vectors e suas funçoes existentes, e tirei algumas duvidas sobre metodos estaticos.
- O que aprendi: aprend sobre a funcinalidade dos metodos estaticos e como funiona o cpfs.erase(cpfs.begin() + i) que me deixou com duvida.

## Primeiro contato: revisão sem editar

- As três melhorias que a IA sugeriu, em uma linha cada:
- A que escolhi e por quê:
- O que mudou no código, e se os seis testes continuaram passando:
- O que entendi que não sabia antes:

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

- Primeira mensagem (o pedido do plano):
- O plano que a IA apresentou, resumido: basicamente nao acrecentar nenhum include novo, nao mexer em astronauta e em voo, alem de acracentear LISTAR_ASTRONAUTAS e HISTORICO como metodos, e acrecentalos nas condiçoes do main.
- Mudei algo no plano antes de liberar? nao.
- Resultado de `testar.sh missao1` e de `testar.sh parte1`:
"
$ bash testes/testar.sh missao1
OK    01_listar_astronautas
OK    02_historico

2 de 2 testes passaram.
$ bash testes/testar.sh parte1
OK    01_cadastros
OK    02_passageiros_planejados
OK    03_lancamento_finalizacao
OK    04_explosao_e_mortes
OK    05_operacoes_invalidas
OK    06_cenario_completo

6 de 6 testes passaram.
"
- Precisei refazer? O que mudou no pedido: nao precisei refazer.

## Missão 2: SALVAR e CARREGAR

- Primeira mensagem:"dado o meu codgo ate agora em main.cpp como se poderia adicionar uma funçao de salvar e uma de carregar os dados de um arquivo .txt" queria ter uma ideia de qual seria a abordagem sugerida pela ia, e se ela iria conseguir analisar por si propria com esse nivel de abstraçao no pedido.
- O plano, resumido:
#include <fstream> no topo, para ter ofstream e ifstream adicionado.
Em Astronauta, criar void restaurar(bool v, bool d) que escreve direto em vivo e disponivel, ja que hoje não têm outro jeito de voltar do arquivo.
Em Voo, criar void restaurarEstado(string novoEstado) pois o estado é private e só muda por lancar()/explodir()/finalizar() mas a lista de CPFs já tem adicionarAstronauta, que é público e não valida nada, então serve para recarregar.
Em Agencia, criar string salvar(string nomeArquivo) e string carregar(string nomeArquivo) que gravam/leem o arquivo inteiro e devolvem as mensagens OK:/ERRO:; no carregar, se o ifstream não abrir, devolve o ERRO e não limpa nada.
E em main(), criar os ramos SALVAR e CARREGAR, lendo o nome com cin >>.

- O formato do arquivo (cole cinco linhas do `dados_teste.txt`):
"
A 111 30 1 1 Ana Maria
A 222 35 0 0 Bruno Costa
A 333 28 1 1 Carla Souza
V 10 1 111 finalizado com sucesso
V 20 1 222 finalizado com explosao
V 30 1 333 planejado
"
- Resultado de `testar.sh missao2` e de `testar.sh parte1`:
"
$ bash testes/testar.sh missao2
OK    01_salvar
OK    02_carregar
OK    03_arquivo_inexistente
3 de 3 testes passaram.

$ bash testes/testar.sh parte1
OK    01_cadastros
OK    02_passageiros_planejados
OK    03_lancamento_finalizacao
OK    04_explosao_e_mortes
OK    05_operacoes_invalidas
OK    06_cenario_completo
6 de 6 testes passaram.
"
- Precisei refazer? O que mudou no pedido: nao precisei refazer

## Missão 3: RELATORIO

- Primeira mensagem: poderia analisar como seria implementado um novo comando RELATORIO seguindo esses termos...
- O plano, resumido: 
  Sem include novo.
  Em Agencia, novo método privado contarVoosLancados(cpf) que conta voos com estado diferente de "planejado" que contenham o CPF, mesma regra que historico usa.
  Em Agencia, novo método público void relatorio() que imprime RELATORIO, 4 contadores de voo, 3 de astronautas, o mais experiente (troca só com >, e (nenhum) se a experiência máxima for 0) e a taxa sucesso * 100 / (sucesso + explosao), com (nenhum voo finalizado) quando não houver finalizados.
  Em main(), um ramo RELATORIO que só chama agencia.relatorio().
  Nada muda em salvar()/carregar() nem em Voo/Astronauta, porque a experiência é calculada, não guardada — por isso os testes 04 e 05 passam. Depois: compilar e rodar testar.sh missao3 e testar.sh parte1.
- Resultado de `testar.sh missao3` e de `testar.sh parte1`:
"
$ bash testes/testar.sh missao3
OK    01_relatorio_vazio
OK    02_relatorio_cenario
OK    03_relatorio_empate
OK    04_salvar_para_relatorio
OK    05_relatorio_apos_carregar

5 de 5 testes passaram.
$ bash testes/testar.sh parte1
OK    01_cadastros
OK    02_passageiros_planejados
OK    03_lancamento_finalizacao
OK    04_explosao_e_mortes
OK    05_operacoes_invalidas
OK    06_cenario_completo

6 de 6 testes passaram.
"
- Precisei refazer? O que mudou no pedido: nao precisei tudo fluiu muito bem.

## Missão 4: livre

- O que escolhi e por quê: escolhi a implementaçao de um comandante, pois acho q é algo que faria sentido existir nesse codgo.
- O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos
  (escritos antes de pedir):
"
OK: astronauta 111 cadastrado
OK: astronauta 222 cadastrado
OK: astronauta 333 cadastrado
OK: voo 10 cadastrado
OK: voo 20 cadastrado
OK: astronauta 111 adicionado ao voo 10
OK: voo 10 lancado
OK: voo 10 finalizado com sucesso
OK: astronauta 111 adicionado ao voo 20
OK: voo 20 lancado
OK: voo 20 finalizado com sucesso
CAPITAO DE 111 Ana Maria (voos com sucesso: 2)
222 Bruno Costa nao e capitao (voos com sucesso: 0)
OK: voo 30 cadastrado
OK: astronauta 111 adicionado ao voo 30
OK: astronauta 222 adicionado ao voo 30
ERRO: astronauta 999 nao cadastrado
ERRO: voo 99 nao cadastrado
ERRO: astronauta 333 nao esta no voo 30
OK: capitao do voo 30 e 111 Ana Maria (experiente)
ERRO: astronauta 111 ja e capitao do voo 30
OK: voo 30 lancado
ERRO: voo 30 nao esta planejado
OK: voo 30 finalizado com sucesso  
"
- Primeira mensagem: "gostaria de adicionar uma nova funcionalidade no codgo, a de captao, em que toda todo voo precisa de um captao para ser lançado, para se tornar um captao é preciso ter no minimo 2 voos realizados, e no caso de ter 2 captoes possiveis para o mesmo voo, o desempate sera pela taxa de sucesso de cada um, e se ninguem tiver experiencia para isso, o captao e escolido entre a tripulaçao do voo de acordo com critrios que vou detalhar, e em caso do sucesso dessa miçao com o pactao escolhido, esse individuo ja pudesse ser classificado como captao mesmo nao tendo ido a dois voos no minimo"
- O que veio, comparado com o que eu esperava: veio tudo certinho, so com um pedido a mais de implementaçao
- `testar.sh parte1` continuou passando? passou.
- Aceitei, ajustei ou descartei? Por quê: aceitei pois ficou uma boa implementaçao e todos os testes continuaram passando

## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo: toda a parte do salvar e carregar, pois tenho beemm pouca esperiencia e pratica com mexer em arquivos direto no codgo.
- Onde ela errou ou fez algo que eu não pedi: so ocorreu dois porblemas: uma vez que ela criou uma pasta mesmo eu deixando bem claro que nao queria esse comportamento, e uma alucinaçao em que eu perguntei sobre um topico, mas ela incluiu algo totalmente diferente na explicaçao que nao tinha nada haver e focou nisso.
- O que eu faria diferente da próxima vez: faria na parte 1 as notificaçoes junto com a implementaçao do codgo, nao fiz isso e no final tive q refazer agencia quase toda para fazer as mensagens funcionarem 
