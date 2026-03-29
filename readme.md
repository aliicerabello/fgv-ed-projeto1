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

O projeto foi desenvolvido com foco em eficiência nas operações mais frequentes e sem uso da STL, conforme restrição proposta.

---

## 📦 Organização Interna dos Dados

Os dados são organizados por meio de um vetor de salas (`Room`), onde cada sala possui uma lista encadeada de reservas (`Reservation`).

### Estrutura geral:
ReservationSystem
│
├── Room[0]
│ ├── room_capacity
│ └── Reservation → Reservation → ...
│
├── Room[1]
│ ├── room_capacity
│ └── Reservation → ...
│
└── ...

- Cada `Room` representa uma sala
- Cada `Reservation` representa uma reserva
- As reservas são armazenadas em listas encadeadas por sala

---

## ⚙️ Funcionamento

- A capacidade da sala é verificada diretamente no campo `room_capacity`, evitando iterações desnecessárias.
- Caso a capacidade seja suficiente, verifica-se a disponibilidade de horário.
- A inserção é feita no início da lista → custo `O(1)`
- O cancelamento percorre a lista até encontrar a reserva

---

## 📈 Complexidade

| Operação           | Complexidade |
|------------------|------------|
| `reserve()`       | O(m × n)   |
| `cancel()`        | O(m × n)   |
| inserção          | O(1)       |
| `printSchedule()` | O(n²)      |

Onde:
- `m` = número de salas  
- `n` = número de reservas por sala  

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
  - 💡 possível melhoria: tabela hash (`O(1)`)

---

## 🛠️ Compilação

```bash
g++ -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -std=c++17 main.cpp ReservationSystem.cpp ReservationRequest.cpp -o sistema