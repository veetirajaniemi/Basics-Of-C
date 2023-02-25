/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Veeti Rajaniemi 
* Opiskelijanumero: 0599190
* Päivämäärä: 21.03.2022
* Palauttamalla tämän työn arvioitavaksi vakuutan, että
* 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin
* 2) En ole antanut tätä koodia kenenkään muun käyttöön
*
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa:
* - Eetu Knutars neuvoi kuukausi-tietuetaulukon oikeassa rakenteessa ja sen
* sisällyttämisessä tulostietueeseen sekä tulostamiseen double-muodon kanssa.  
* - Eetu Peltola neuvoi tiedoston kirjoittamisessa tyyliohjeen mukaisesti
* käyttämällä stdout-parametria.
*/
/*************************************************************************/
/* Tehtävä HT Perustaso, HTPerusTaso.c */
/* eof */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HTPerusKirjasto.h"


int main(void) {
    int iValinta;
    char aLuettava[KOKO];
    char aKirjoitettava[KOKO];
    TIEDOT *pAlkut = NULL;
    TULOS *pTulos = NULL;
    char aKysyluku[KOKO] = "Anna luettavan tiedoston nimi:";
    char aKysykirj[KOKO] = "Anna kirjoitettavan tiedoston nimi:";

    do {
        iValinta = valikko();

        if (iValinta == 1) {
            kysyTiedosto(aLuettava, aKysyluku);
            if (pAlkut != NULL) { // tyhjennetään lista tarvittaessa ennen tietojen lukemista
                pAlkut = vapautaMuistitieto(pAlkut);
            }
            pAlkut = lueTiedosto(aLuettava, pAlkut);
        }

        else if (iValinta == 2) {

            if (pAlkut == NULL) { 
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
                
            }
            else {
                if (pTulos != NULL) { // tyhjennetään tulokset tarvittaessa ennen analyysia
                    pTulos = vapautaMuistitulos(pTulos);
                }
                pTulos = analysoiTiedot(pAlkut, pTulos);
            }
        }

        else if (iValinta == 3) {
            if (pTulos == NULL) {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
            else {
                kysyTiedosto(aKirjoitettava, aKysykirj);
                kirjoitaTiedosto(pTulos, aKirjoitettava);
            }
        }

        else if (iValinta == 0) {
            pAlkut = vapautaMuistitieto(pAlkut);
            pTulos = vapautaMuistitulos(pTulos);
            pAlkut = NULL;
            pTulos = NULL;
            break;
        }

        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }

        printf("\n");

    } while (iValinta != 0);
    
    printf("\nKiitos ohjelman käytöstä.\n");
    return(0);
}