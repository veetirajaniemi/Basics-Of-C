#/*************************************************************************/
#/* CT60A2500 C-ohjelmoinnin perusteet
#* Tekijä: Veeti Rajaniemi 
#* Opiskelijanumero: 0599190
#* Päivämäärä: 21.03.2022
#* Palauttamalla tämän työn arvioitavaksi vakuutan, että
#* 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin
#* 2) En ole antanut tätä koodia kenenkään muun käyttöön
#*
#* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
#* lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa:
#* - Eetu Knutars neuvoi kuukausi-tietuetaulukon oikeassa rakenteessa ja sen
#* sisällyttämisessä tulostietueeseen sekä tulostamiseen double-muodon kanssa.  
#* - Eetu Peltola neuvoi tiedoston kirjoittamisessa tyyliohjeen mukaisesti
#* käyttämällä stdout-parametria.
#*/
#/*************************************************************************/
# Tehtävä HT Perustaso, Makefile */
# eof */

HT: HTPerustaso.o HTPerusKirjasto.o
		gcc HTPerustaso.o HTPerusKirjasto.o -o HT -std=c99 -pedantic -Wall
HTPerustaso.o: HTPerustaso.c HTPerusKirjasto.h
		gcc HTPerustaso.c -c -std=c99 -pedantic -Wall
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
		gcc HTPerusKirjasto.c -c -std=c99 -pedantic -Wall
          

