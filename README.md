# Estudo de Paralelismo em Sistemas Operacionais de Uso Geral para a disciplina de fluxo e metodologias de projeto de sistemas embarcados do Programa de Pós Graduação em Engenharia Mecatrônica (PPgEMECA/UFRN)

## 📘 Descrição Geral

Este projeto tem como objetivo aplicar conceitos de programação paralela em ambientes Linux (utilizando WSL no Windows 11) para resolver dois problemas computacionalmente intensivos:

1. **Estimativa do número PI** usando múltiplas threads com controle de seção crítica.
2. **Multiplicação de matriz por vetor** com diferentes dimensões, utilizando paralelismo.

Todos os códigos foram desenvolvidos em C++ e compilados no **Ubuntu 24.04 LTS** via **WSL** (Windows Subsystem for Linux), aproveitando o suporte a múltiplos núcleos da CPU AMD Ryzen 5 5600G.

As descrições da atividade completa podem ser encontradas em: https://github.com/josenalde/flux-embedded-design/blob/main/exercises/atividade_3.ipynb

---

## 🧠 Parte 1 – Estimativa de PI

### 🎯 Objetivo
Estimar o número PI utilizando métodos paralelos e analisar o impacto do controle de seção crítica com `mutex`.

### 🛠️ Implementações

- **Versão serial**: execução sequencial simples.
- **Versão paralela com `mutex` DENTRO do loop**: cada contribuição é somada dentro de uma seção crítica.
- **Versão paralela com `mutex` FORA do loop**: cada thread acumula sua contribuição local e só entra na seção crítica ao final.

### 🔍 Avaliação

Para cada versão, são comparados:

- Tempo médio de execução.
- Valor estimado de PI.

---

## 🧠 Parte 2 – Multiplicação Matriz × Vetor

### 🎯 Objetivo
Realizar a multiplicação entre uma matriz $A_{m \times n}$ e um vetor $x_{n \times 1}$ de forma paralela, para três cenários distintos:

| Caso | Dimensão da Matriz (m x n) | Dimensão do Vetor | Característica Principal     |
|------|-----------------------------|--------------------|------------------------------|
| a)   | 8.000.000 × 8               | 8 × 1              | Muitas linhas, poucas colunas |
| b)   | 8.000 × 8.000               | 8.000 × 1          | Matriz quadrada grande       |
| c)   | 8 × 8.000.000               | 8.000.000 × 1      | Poucas linhas, muitas colunas |

### 💾 Dados
Todos os valores são números do tipo `double`, gerados aleatoriamente no intervalo **[0, 5]**.

---

## ⚙️ Ambiente de Execução

| Item                | Descrição                                     |
|---------------------|-----------------------------------------------|
| **SO Host**         | Windows 11                                    |
| **SO Execução**     | Ubuntu 24.04.2 LTS via WSL                    |
| **Compilador**      | `g++` versão 14.2                             |
| **Hardware**        | AMD Ryzen 5 5600G                             |
| **Núcleos**         | 6 físicos, 12 threads                         |
| **Cache**           | L1d: 192 KiB, L2: 3 MiB, L3: 16 MiB           |

---

## 🚀 Instruções para Execução

1. Clone este repositório:

   ```bash
   git clone https://github.com/DeivisonLuan/PI_Estimator.git
   cd PI_Estimator
   ```

2. Compile os programas:

   ```bash
   g++ -o Estimador_PI_serial Estimador_PI_serial.cpp 
   g++ -o Estimador_PI_mutex_InLoop Estimador_PI_mutex_InLoop.cpp -pthread 
   g++ -o Estimador_PI_mutex_OutLoop Estimador_PI_mutex_OutLoop.cpp -pthread 

   g++ -o Matriz_x_Vetor_serial Matriz_x_Vetor_serial.cpp 
   g++ -o Matriz_x_Vetor Matriz_x_Vetor.cpp -pthread 
   ```

3. Executando os programas:

   ```bash
   ./nome_do_programa.exe 
   ```

---

## 📊 Resultados Esperados

- Comparações entre tempo e precisão da estimativa de PI nas diferentes abordagens.
- Análise do desempenho da multiplicação da matriz × vetor em diferentes configurações de tamanho.
- Discussão sobre escalabilidade, uso de CPU e impacto do paralelismo em cada caso.

---

## ✍️ Autor

- **Nome**: Deivison Luan Xavier Silva
- **Disciplina**: Fluxo e metodologias de projeto de sistemas embarcados
- **Professor**: Prof. Josenalde
- **Instituição**: UFRN

