# PROJETO DE SISTEMAS OPERACIONAIS

## OBJETIVOS
- Monitorar e apresentar as características e propriedades de todos os processos em execução no sistema operacional.
- Monitorar e apresentar as informações do uso de memória dos processos.

## REQUISITOS GERAIS
1. As informações atuais de cada processo devem ser apresentadas ao usuário e atualizadas em intervalos regulares de tempo (ex.: a cada 5 segundos).
2. A escolha das informações a serem mostradas ao usuário fica a critério da equipe, priorizando as mais pertinentes e relevantes para um administrador de sistemas. A avaliação será baseada na completude e complexidade das informações apresentadas.
3. O Dashboard deve permitir:
   - Mostrar informações globais do sistema.
   - Mostrar informações individualizadas para cada processo.
   - Similar à funcionalidade de monitores de sistema do Windows ou Linux.
4. As informações apresentadas devem ser processadas pelo Dashboard, evitando a exibição de saídas de texto "cruas" ou "raw" retornadas por serviços, funções, APIs ou comandos do sistema operacional.
5. As informações não devem ser obtidas através de comandos do shell (ex.: `ls`, `ps`, `du`, etc.). Devem ser utilizadas chamadas de sistema ou outros meios fornecidos pelo sistema operacional (ex.: diretórios no Linux, tabela de partições do disco, etc.).
6. A linguagem de implementação do Dashboard é livre, mas a obtenção das informações dos processos deve ser feita via API do sistema operacional.



# CLASSES -
1 - Classe responsavel por chamadas das funcoes de sistemas
   - Metodos:
      - Quantidade de processos rodando;
      - Qunatidade de processos de cada aplicacao
      - Tempo ocioso do processador
      - Quantidade de treads de cada processo
      - Tempo de uso;
      - Lista de processos existentes, juntamente com os respectivos usuarios
      - informacoes sobre as treads de cada processo