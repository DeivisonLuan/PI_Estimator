# Estudo de Paralelismo em Sistemas Operacionais de Uso Geral para a disciplina de fluxo e metodologias de projeto de sistemas embarcados do Programa de Pós Graduação em Engenharia Mecatrônica (PPgEMECA/UFRN)

## 📘 Descrição Geral

Este projeto tem como objetivo aplicar conceitos de programação paralela em ambientes Linux (utilizando WSL no Windows 11) para resolver dois problemas computacionalmente intensivos:

1. **Estimativa do número PI** usando múltiplas threads com controle de seção crítica.
2. **Multiplicação de matriz por vetor** com diferentes dimensões, utilizando paralelismo.

Todos os códigos foram desenvolvidos em C++ e compilados no **Ubuntu 24.04 LTS** via **WSL** (Windows Subsystem for Linux), aproveitando o suporte a múltiplos núcleos da CPU AMD Ryzen 5 5600G.

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
- Precisão relativa.

---

## 🧠 Parte 2 – Multiplicação Matriz × Vetor

### 🎯 Objetivo
Realizar a multiplicação entre uma matriz `A[m][n]` e um vetor `v[n]` de forma paralela, para três cenários distintos:

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
| **Compilador**      | `g++` com suporte a C++17 ou superior         |
| **Hardware**        | AMD Ryzen 5 5600G                             |
| **Núcleos**         | 6 físicos, 12 threads                         |
| **Cache**           | L1d: 192 KiB, L2: 3 MiB, L3: 16 MiB           |

---

## 🚀 Instruções para Execução

1. Clone este repositório:

   ```bash
   git clone https://github.com/seu-usuario/seu-repositorio.git
   cd seu-repositorio
   ```

2. Compile os programas:

   ```bash
   g++ -o pi_serial pi_serial.cpp -std=c++17
   g++ -o pi_mutex_dentro pi_mutex_dentro.cpp -pthread -std=c++17
   g++ -o pi_mutex_fora pi_mutex_fora.cpp -pthread -std=c++17

   g++ -o mult_matriz_vetor mult_matriz_vetor.cpp -pthread -std=c++17
   ```

3. Execute cada versão:

   ```bash
   ./pi_serial
   ./pi_mutex_dentro
   ./pi_mutex_fora
   ./mult_matriz_vetor
   ```

---

## 📊 Resultados Esperados

- Comparações entre tempo e precisão da estimativa de PI nas diferentes abordagens.
- Análise do desempenho da multiplicação da matriz × vetor em diferentes configurações de tamanho.
- Discussão sobre escalabilidade, uso de CPU e impacto do paralelismo em cada caso.

---

## 📁 Organização do Repositório

```
.
├── README.md
├── pi_serial.cpp
├── pi_mutex_dentro.cpp
├── pi_mutex_fora.cpp
├── mult_matriz_vetor.cpp
├── scripts/               # (Opcional) Scripts de automação ou análise
└── resultados/            # (Opcional) Tabelas, gráficos e logs
```

---

## ✍️ Autor

- **Nome**: _Seu Nome Aqui_
- **Disciplina**: Sistemas Embarcados / Programação Paralela
- **Professor**: _Nome do professor (se desejar)_
- **Instituição**: _Nome da instituição_

---

## 📝 Licença

Este projeto é apenas para fins educacionais e acadêmicos.
