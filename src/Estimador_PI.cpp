/*
Atividades baseadas no documento em: 
https://github.com/josenalde/flux-embedded-design/blob/main/exercises/atividade_3.ipynb

  CPU Model name:             AMD Ryzen 5 5600G with Radeon Graphics
      Core(s):                6
      Thread(s) por core:     2 
      
  Caches (sum of all):
    L1d:                    192 KiB (6 instances)
    L1i:                    192 KiB (6 instances)
    L2:                     3 MiB (6 instances)
    L3:                     16 MiB (1 instance)
    
  OS NAME="Ubuntu"
  VERSION="24.04.2 LTS (Noble Numbat)"
  
  - Elaborar versão do código incluindo seção crítica controlada por MUTEX dentro do loop
  - Elaborar versão do código incluindo seção crítica controlada por MUTEX fora do loop, 
        com variável privada da soma de contribuição de cada thread
  
  - Rodar versão do código serial, sem paralelismo, ou seja, com 1 thread
    criar tabela comparativa das letras a) e b) para o caso de 1 thread por core e de 2 threads por core. 
      Exemplo: se a CPU tem 4 cores e até 2 threads por core, fazer para T=4 e T=8. 
              Se tem 08 cores, fazer para T=8 e T=16. 
    Na tabela deixar claro qual a CPU em que está rodando a aplicação (no linux comando lscpu), 
    detalhando número de cores/threads, níveis de cache e tamanho de cada cache (L1, L2, L3). 
    Pode ser usado o método presente nos arquivos acima para calcular o tempo, usando clock() do C, 
    ou o chrono do C++ ou o omp_get_wtime() do omp.h. A tabela resumo deve ter aparência como neste exemplo, 
    comparando o caso SERIAL com os dois casos PARALELOS: formatar número de saída com 12 casas decimais, 
    com cout.precision(12) e na hora de exibir uma variável, suponha x, fazer cout << fixed << x;

  Apresentar na tabela a coluna com o PI calculado e a coluna com o tempo médio de 10 execuções para cada caso.
  
*/

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

using namespace std;

//definição de variaveis globais
#define MaxThread 12 //numero máximo de threads do CPU

//inicializa o mutex com atributos padrão
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//Função das threads
void* pi_estimator(void* id){
  long my_rank = (long) id; //typecast
  double factor;
  long long i;
  //long long my_n = n/MaxThread;
  //long long my_first_i = my_n*my_rank;
  //long long my_last_i = my_first_i + my_n;

  //if (my_first_i % 2 == 0) /* my first i is even */
      factor = 1.0;
  //else /* my first i is odd */
      factor = -1.0;

  //for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
          //sum += factor/(2i+1);
  //}

  return NULL; //evita warning
}

int main(){
  pthread_t threads[MaxThread];
  int err;

  for(long i=0; i<MaxThread; i++){
    err = pthread_create(&threads[i], NULL, pi_estimator, (void*)i);

  }

  return 0;
}