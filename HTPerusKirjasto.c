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
/* Tehtävä HT Perustaso, HTPerusKirjasto.c */
/* eof */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"



int valikko() {
    int iValinta;

    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();

    return iValinta;
}

void kysyTiedosto(char *pNimi, char *pKysy) {
    printf("%s ", pKysy);
    scanf("%s", pNimi);
    return;
}

TIEDOT* lueTiedosto(char *pNimi, TIEDOT *pA) {
    FILE *tiedosto;
    char aRivi[KOKO];

    if ((tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    int iKierros1 = 0; // tiedoston 1. riviä ei tallenneta linkitettyyn listaan
    while (fgets(aRivi, KOKO, tiedosto) != NULL) {

        if (iKierros1 != 0) {
            pA = lisaaListaan(aRivi, pA); //lisätään rivin tiedot omassa aliohjelmassaan linkitettyyn listaan
        }
        iKierros1 = 1;
    }
    fclose(tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return pA;
}

TIEDOT *lisaaListaan(char *pRivi, TIEDOT *pA) {
    TIEDOT *pUusi, *ptr;
    char *pAika, *pViikko, *pKulutus, *pAurinko, *pTuuli;
    char *pVesi, *pYdin, *pYhteis, *pLampo;

    pAika = strtok(pRivi, ";");
    pViikko = strtok(NULL, ";");
    pKulutus = strtok(NULL, ";");
    pAurinko = strtok(NULL, ";");
    pTuuli = strtok(NULL, ";");
    pVesi = strtok(NULL, ";");
    pYdin = strtok(NULL, ";");
    pYhteis = strtok(NULL, ";");
    pLampo = strtok(NULL, "\n");

    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }

    strcpy(pUusi->aika, pAika);
    pUusi->viikko = atoi(pViikko);
    pUusi->kulutus = atoi(pKulutus);
    pUusi->aurinko = atoi(pAurinko);
    pUusi->tuuli = atoi(pTuuli);
    pUusi->vesi = atoi(pVesi);
    pUusi->ydin = atoi(pYdin);
    pUusi->yhteis = atoi(pYhteis);
    pUusi->lampo = atoi(pLampo);
    
    pUusi->pSeuraava = NULL;
    if (pA == NULL) {
        pA = pUusi;
    }
    else {
        ptr = pA;
        while (ptr->pSeuraava != NULL) {
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
    }
    return pA;
}

TULOS *analysoiTiedot(TIEDOT *pTiedot, TULOS *pTulos) {
    TIEDOT *ptr = pTiedot;
    
    
    int iLukumaara = 0;
    double dYhteissumma = 0;
    double dKeskiarvo;
    char aAika[KOKO];

    if ((pTulos = (TULOS*)malloc(sizeof(TULOS))) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }

    for (int i = 0; i < 12; i++) { //alustetaan kuukausille oikeat numerot ja niiden tuotantomäärät nollaksi laskemista varten
        pTulos->kuukaudet[i].kk = i+1;
        pTulos->kuukaudet[i].tuotanto = 0;
    }
    
    pTulos->suurinkulutus = ptr->kulutus;
    pTulos->pieninkulutus = ptr->kulutus; 
    strcpy(pTulos->suurinaika, ptr->aika);
    strcpy(pTulos->pieninaika, ptr->aika);

    while (ptr != NULL) {
        iLukumaara = iLukumaara + 1;
        dYhteissumma = dYhteissumma + ptr->kulutus;
    if (ptr->kulutus > pTulos->suurinkulutus) {
            pTulos->suurinkulutus = ptr->kulutus;
            strcpy(pTulos->suurinaika, ptr->aika);
        }
        if (ptr->kulutus < pTulos->pieninkulutus) {
            pTulos->pieninkulutus = ptr->kulutus;
            strcpy(pTulos->pieninaika, ptr->aika);
        }
        strcpy(aAika, ptr->aika);
        strtok(aAika, ".");
        char *pKk = strtok(NULL, ".");
        int iLuku = atoi(pKk);
        pTulos->kuukaudet[iLuku - 1].tuotanto = pTulos->kuukaudet[iLuku - 1].tuotanto + (ptr->aurinko + ptr->tuuli + ptr->vesi + ptr->ydin + ptr->yhteis + ptr->lampo);
        ptr = ptr->pSeuraava;
    }

    dKeskiarvo = dYhteissumma / iLukumaara;
    pTulos->lkm = iLukumaara;
    pTulos->yhteiskulutus = dYhteissumma;
    pTulos->keskiarvo = dKeskiarvo;

    printf("Analysoitu %d mittaustulosta.\n", pTulos->lkm);
    printf("Kokonaiskulutus oli yhteensä %.0f kWh.\n", pTulos->yhteiskulutus);
    printf("Kuukausittaiset tuotannot analysoitu.\n"); 

    return pTulos;
}

void kirjoitaTulokset(FILE *tiedosto, TULOS *pTulos) {

    float fKerroin = 0.000001; // tällä muunnos kWh->GWh

    fprintf(tiedosto, "Tilastotiedot %d mittaustuloksesta:\n", pTulos->lkm);
    fprintf(tiedosto, "Kulutus oli yhteensä %.0f kWh,", pTulos->yhteiskulutus);
    fprintf(tiedosto, " ja keskimäärin %.1f kWh.\n", pTulos->keskiarvo);
    fprintf(tiedosto, "Suurin kulutus, %d kWh,", pTulos->suurinkulutus);
    fprintf(tiedosto, " tapahtui %s.\n", pTulos->suurinaika);
    fprintf(tiedosto, "Pienin kulutus, %d kWh,", pTulos->pieninkulutus);
    fprintf(tiedosto, " tapahtui %s.\n\n", pTulos->pieninaika);

    fprintf(tiedosto, "Pvm;Tuotanto (GWh)\n");

    for (int i = 0; i < 12; i++) {
        fprintf(tiedosto, "Kk %d;%.2f\n", pTulos->kuukaudet[i].kk, (double)pTulos->kuukaudet[i].tuotanto*fKerroin);
    }

    return;
}

void kirjoitaTiedosto(TULOS *pTulos, char *pNimi) {
    FILE* tiedosto;

    kirjoitaTulokset(stdout, pTulos); //kirjoitetaan tulokset konsoliin
    
    if ((tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    kirjoitaTulokset(tiedosto, pTulos); //kirjoitetaan tulokset tiedostoon
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    fclose(tiedosto);

    return;
}

TIEDOT *vapautaMuistitieto(TIEDOT *pA) {
    TIEDOT *ptr = pA;

    while (ptr != NULL) {
        pA = ptr->pSeuraava;
        free(ptr);
        ptr = pA;
    }  
    return pA;
}

TULOS *vapautaMuistitulos(TULOS *pAlkutulos) {
    free(pAlkutulos);
    return pAlkutulos;
}