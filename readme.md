# 🏫 Reservation System

![C++](https://img.shields.io/badge/language-C++-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Status](https://img.shields.io/badge/status-academic--project-lightgrey)

Sistema de gerenciamento de reservas de salas desenvolvido em C++.

---

## 📌 Descrição

O sistema permite realizar reservas e cancelamentos de salas com base em:

- capacidade da sala
- disponibilidade de horário
- nome da disciplina

As reservas são organizadas internamente por sala, utilizando estruturas de dados eficientes para operações frequentes.

---

## 🧠 Estrutura de Dados

A principal estrutura utilizada é a **lista encadeada**.

- Cada `Room` possui:
  - capacidade (`room_capacity`)
  - ponteiro para o início de uma lista de reservas

- Cada `Reservation`:
  - representa uma reserva
  - aponta para a próxima (`next`)

👉 Assim, cada sala mantém sua própria lista de reservas.

---

## ⚙️ Funcionamento

- A capacidade da sala é verificada diretamente no campo `room_capacity`, evitando iterações desnecessárias.
- Se a capacidade for suficiente, verifica-se a disponibilidade de horário.
- A inserção de reservas é feita no **início da lista** → custo `O(1)`.
- O cancelamento percorre as listas até encontrar a reserva correspondente.

---

## 📈 Complexidade

| Operação          | Complexidade |
|-------------------|--------------|
| `reserve()`       | O(m × n)     |
| `cancel()`        | O(m × n)     |
| inserção          | O(1)         |
| `printSchedule()` | O(n²)        |

Onde:
- `m` = número de salas  
- `n` = número de reservas por sala  

A ordenação é feita apenas no `printSchedule()` usando **Bubble Sort**.

---

## 🔄 Alternativas Consideradas

- **Array fixo por sala**
  - Mais simples
  - ❌ exige limite máximo de reservas

- **Lista duplamente encadeada**
  - Facilita remoção
  - ❌ maior uso de memória

- **Inserção ordenada**
  - Mantém lista organizada
  - ❌ aumenta custo de `reserve()`

---

## ⚖️ Trade-offs

- Lista encadeada simples:
  - ✔️ inserção rápida  
  - ❌ não mantém ordem  

- Ordenação no `printSchedule()`:
  - ✔️ eficiente no uso geral  
  - ❌ custo alto na impressão  

- `ReservationRequest` por valor:
  - ❌ cópias desnecessárias  
  - ✔️ poderia ser `const &`  

- Busca por nome da disciplina:
  - ✔️ simples  
  - ❌ custo O(m × n)  
  - 💡 possível melhoria: uso de tabela hash (`O(1)`)

---

## 🛠️ Compilação

```bash
g++ -Wall -Wextra -Werror -std=c++17 main.cpp ReservationSystem.cpp ReservationRequest.cpp -o sistema