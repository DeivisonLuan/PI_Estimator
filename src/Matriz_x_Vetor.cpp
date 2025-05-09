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
#define M 8000000 //numero de linhas
#define N 8 //numero de colunas
double matrix[M][N] = {0};
double vectorX[N] = {0}, vectorY[M] = {0};
double sum = 0.0;

//inicializa o mutex com atributos padrão
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//Função das threads
void* Ax_vector(void* id){
  long thread_id = (long) id; //typecast
  int i, j;
  int local_m = M/MaxThread;
    int my_start = thread_id * local_m;
    int my_end = (thread_id+1) * local_m - 1;
    for (i = my_start; i <= my_end; i++) {
        vectorY[i] = 0.0;
        for (j = 0; j < N; j++)
            vectorY[i] += matrix[i][j] * vectorX[j];
    }
  return NULL; //evita warning
}

void generateMatrix(double *m, int line, int column){
  for (int i = 0; i < line; ++i) {
    for (int j = 0; j < column; ++j){
      *(m + i * column + j) = rand() % 5 + 1;
    }
  }
}

void generateVector(double *v, int lenght){
  for (int i = 0; i < lenght; ++i) {
    v[i] = rand() % 5 + 1;
  }
}



int main(){
  pthread_t threads[MaxThread];
  int err;

  srand(time(NULL)); //inicializa o gerador de numeros aleatórios baseados no tempo atual
  
  generateMatrix(&matrix[0][0],M,N);
  generateVector(vectorX,N);

  pthread_mutex_init(&lock, NULL); // o segundo parâmetro = NULL significa que usará atributos padrão

  clock_t timeStart, timeEnd;
  timeStart = clock(); //marcar o tempo inicial

  for(long i=0; i<MaxThread; i++){
    err = pthread_create(&threads[i], NULL, Ax_vector, (void*)i);
  }
  
  for (int i=0; i<MaxThread; i++) {
    err  = pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&lock);

  timeEnd = clock(); //marca o tempo final
  double execTime = (double)(timeEnd - timeStart)/(double) CLOCKS_PER_SEC;
  cout.precision(12);
  cout << fixed << "Tempo de execução: " << execTime << endl;
  cout << "Numero pi encontrado com " << N << " parcelas somadas: " << sum << endl;
  
  return 0;
}

//usando o race condition não precisa de pthread, rever isso