/* ATIVIDADE KARATSUBA */
/*
  Arquivo: ManoelaMartediKaratsuba.c
  Autor: Manoela Martedi
  Data: 15/11/24 18:12
  Descricao: este programa implementa o algoritmo de karatsuba
  para a atividade 4 de EDNL
*/

#include <stdio.h>
#include <math.h>

unsigned long long numDigitos(unsigned long long); // para calcular o número de dígitos em um número
unsigned int chamadas = 0;

unsigned long long karatsuba (unsigned long long x, unsigned long long y) {
    chamadas ++;
    
    unsigned long long 
    result, n, pot, a, b, c, d, p, q, ac, bd, pq, adbc;

    if (x < 10 || y < 10) {
        result = x*y;
    } else {
        n = fmax(numDigitos(x), numDigitos(y)); // assumindo que n é pot de 2
        
        pot = pow(10, n/2);         // pot = 10^{n/2}
        a = x / pot; b = x % pot;   // dividir dígitos de x pela metade em a e b
        c = y / pot; d = y % pot;   // dividir dígitos de y pela metade em c e d

        p = a+b; q = c+d;
        ac = karatsuba(a, c);
        bd = karatsuba(b, d);
        pq = karatsuba(p, q);

        adbc = pq - ac - bd;        //ad+bc = karatsuba(a+b, c+d) - ac - bd;

        // x * y = ac * 10^{2(n/2)} + (ad * bc) * 10^{n/2} + bd
        result = ac * pow(10, 2*(n/2)) + adbc * pot + bd;
    }

    return result;
}

unsigned long long numDigitos(unsigned long long num) {
    return log10(num) + 1;
}

int main() {
    unsigned long long A, B, C, numChamadas;
    // ---- PARA C = 12345 x 6789 ----
    A = 12345; B = 6789;
    C = karatsuba(A, B);
    printf("\tA = %d\tB = %d\tC = %d\n\tChamadas = %d\n\n", A, B, C, chamadas);

    // ---- PARA C = 1234 x 987654 ----
    chamadas = 0;
    A = 1234; B = 987654;
    C = karatsuba(A, B);
    printf("\tA = %d\tB = %d\tC = %d\n\tChamadas = %d\n\n", A, B, C, chamadas);
}