#include "ReservationRequest.cpp"
#include "ReservationSystem.cpp"
#include <iostream>
using namespace std;

int main(){

    // === SETUP DO SISTEMA ===
    // 5 salas: capacidades 20, 30, 30, 40, 50
    int capacities[5] = {20, 30, 30, 40, 50};
    ReservationSystem sistema(5, capacities);

    cout << "=== TESTE 1: Reservas basicas ===" << endl;
    // r1: 35 alunos -> deve pular salas 0(20), 1(30), 2(30) e cair na sala 3(40)
    ReservationRequest r1("Algebra Linear", "segunda", 9, 11, 35);
    // r2: 50 alunos -> deve ir para sala 4(50)
    ReservationRequest r2("Calculo I", "terca", 9, 11, 50);
    // r3: 10 alunos -> deve ir para sala 0(20), a primeira disponivel
    ReservationRequest r3("Computacao", "terca", 11, 13, 10);
    cout << "Algebra Linear (seg 9-11, 35 alunos): " << sistema.reserve(r1) << " (esperado: 1)" << endl;
    cout << "Calculo I (ter 9-11, 50 alunos):      " << sistema.reserve(r2) << " (esperado: 1)" << endl;
    cout << "Computacao (ter 11-13, 10 alunos):    " << sistema.reserve(r3) << " (esperado: 1)" << endl;

    cout << "\n=== TESTE 2: Conflito de horario ===" << endl;
    // mesmo dia e horário sobreposto que Algebra Linear na sala 3
    ReservationRequest r4("Estatistica", "segunda", 10, 12, 35);
    // horário adjacente (não deve conflitar: 11 >= 11)
    ReservationRequest r5("Fisica", "segunda", 11, 13, 35);
    cout << "Estatistica (seg 10-12, 35 alunos):   " << sistema.reserve(r4) << " (esperado: 1, outra sala)" << endl;
    cout << "Fisica (seg 11-13, 35 alunos):        " << sistema.reserve(r5) << " (esperado: 1, adjacente ok)" << endl;

    cout << "\n=== TESTE 3: Sem sala disponivel ===" << endl;
    // 51 alunos -> nenhuma sala comporta
    ReservationRequest r6("Filosofia", "quinta", 8, 10, 51);
    cout << "Filosofia (qui 8-10, 51 alunos):      " << sistema.reserve(r6) << " (esperado: 0)" << endl;

    cout << "\n=== TESTE 4: Limites de horario ===" << endl;
    // horário no limite: 7h até 21h
    ReservationRequest r7("Historia", "sexta", 7, 9, 10);
    ReservationRequest r8("Geografia", "sexta", 19, 21, 10);
    cout << "Historia (sex 7-9, 10 alunos):        " << sistema.reserve(r7) << " (esperado: 1)" << endl;
    cout << "Geografia (sex 19-21, 10 alunos):     " << sistema.reserve(r8) << " (esperado: 1)" << endl;

    cout << "\n=== TESTE 5: Mesmo dia, salas diferentes ===" << endl;
    // enche todas as salas na quarta das 14-16
    ReservationRequest r9 ("Quimica",    "quarta", 14, 16, 20);
    ReservationRequest r10("Biologia",   "quarta", 14, 16, 30);
    ReservationRequest r11("Portugues",  "quarta", 14, 16, 30);
    ReservationRequest r12("Ingles",     "quarta", 14, 16, 40);
    ReservationRequest r13("Filosofia2", "quarta", 14, 16, 50);
    ReservationRequest r14("Sociologia", "quarta", 14, 16, 10); // deve falhar: todas ocupadas
    cout << "Quimica    (qua 14-16): " << sistema.reserve(r9)  << " (esperado: 1)" << endl;
    cout << "Biologia   (qua 14-16): " << sistema.reserve(r10) << " (esperado: 1)" << endl;
    cout << "Portugues  (qua 14-16): " << sistema.reserve(r11) << " (esperado: 1)" << endl;
    cout << "Ingles     (qua 14-16): " << sistema.reserve(r12) << " (esperado: 1)" << endl;
    cout << "Filosofia2 (qua 14-16): " << sistema.reserve(r13) << " (esperado: 1)" << endl;
    cout << "Sociologia (qua 14-16): " << sistema.reserve(r14) << " (esperado: 0)" << endl;

    cout << "\n=== TESTE 6: Cancelamento ===" << endl;
    cout << "Cancelar Calculo I:   " << sistema.cancel("Calculo I")   << " (esperado: 1)" << endl;
    cout << "Cancelar Calculo I:   " << sistema.cancel("Calculo I")   << " (esperado: 0, ja cancelado)" << endl;
    cout << "Cancelar Modelagem:   " << sistema.cancel("Modelagem")   << " (esperado: 0, nunca existiu)" << endl;

    cout << "\n=== TESTE 7: Reserva apos cancelamento ===" << endl;
    // Calculo I foi cancelado, entao terca 9-11 na sala 4 ficou livre
    ReservationRequest r15("Matematica Discreta", "terca", 9, 11, 50);
    cout << "Matematica Discreta (ter 9-11, 50):   " << sistema.reserve(r15) << " (esperado: 1)" << endl;

    cout << "\n=== GRADE FINAL ===" << endl;
    sistema.printSchedule();

    return 0;
}