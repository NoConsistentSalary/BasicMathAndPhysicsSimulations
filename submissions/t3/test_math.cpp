

#include <iostream>
#include "Tester.h"





//////////////////////////////////////////////////////

void runAllTestCases()
{
    Tester::runTestcasesV2();
    Tester::runTestcasesV3();
    Tester::runTestcasesV4();

    Tester::runTestcasesM3();
    Tester::runTestcasesM4();

}

//////////////////////////////////////////////////////

int main()
{


    runAllTestCases();

    return 0;
}

/*			Tehtavananto
Palautustiedostot: submissions/t3/test_math.cpp, submissions/t3/math.h, submissions/t3/math.cpp

Kopioi tiedosto: assignments/my_math.h omaan projektiisi (kansioon: submissions/t3/math.h)
ja lis�� se CMakeListiin niin, ett� headerinvoi incluudata cpp tiedostosta.

Koodaa headerin m��rittelyjen mukaiset toiminnot tiedostoon submissions/t3/math.cpp
ja testaa toiminta testisovelluksen (submissions/t3/test_math.cpp) avulla.Voit my�s tehd� oman n�k�isesi headerin
(sellainen matikkakirjasto kuin haluat), p��asia ett� on oleelliset funktiot koodattuna, niit� tarvitaan my�hemmin.


Luo testisovelluskeen testicaset matematiikka toiminnallisuuden testaamiseen. Mik�li jokin testicase feilaa, sovelluksen pit��
palauttaa negatiivinen paluuarvo (jotta pipeline menee punaiseksi).
Esim. Ohjelmoi funktio "bool testVec2Addition(const vec2& vecInputA, const vec2& vecInputB, const vec2& expectedOutput)" Funktio toimii niin,
ett� se kutsuu vec2 pluslaskufunktiota annetiulla parametreilla A ja B (eli funktiota, jota halutaan testata, Unity Under Test) ja palauttaa true,
jos pluslaskun tulos on sama kuin expectedOutput.
Kutsu main-funktiossa testifunktiota eri arvoilla ja testaa, ett� toimiihan pluslasku oikein. Tyyliin n�in:


printf("Testing {2, 3} + {5, 8} == {7, 11} ");
if(testVec2Addition({2, 3}, {5, 8}, {7, 11}) == false) {
      printf("FAIL!\n");
      return -1;
}
printf("PASS!\n");

Tee 10-200 testicasea, jotka testaa matematiikkakirjaston toimintaa (minimiss��n 10, mutta jos keksii jonkin hienon "systeemin" testicasejen helppoon kirjoittamiseen ja saa tehty� > 200 casea, niin siit� plussaa luvassa).
Lis�� gitlabin pipelineen build stagen lis�ksi my�s test stage, jossa k��nn�ksen lis�ksi ajetaan test_math sovellus ja testilogi tallennetaan build artifakteihin. Ohessa test-stage, jonka lis��minen pipelineen pit�isi toiminnallisuuden. Alla annettu koodi valmiiksi.

Pisteytys: 2 p funktiot koodattu. 4 p testicasen m��r� ja kattavuus.

###################################################################################
# Test job
test-job:
  stage: test
  tags:
    - build_server
    - linux
  script:
    - mkdir build
    - cd build
    - cmake ../
    - cmake --build . -- -j24
    - ./test_math > test_log.txt
  artifacts:
    paths:
      - build/test_log.txt
*/
