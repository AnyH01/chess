# chess

specifikace zadání
Jedná se o klasickou hru šachy. Hra dodržuje všechna pravidla běžné hry včetně speciálních tahů, což je rošáda, braní mimochodem a proměna pěsce.

V úvodním menu si uživatel bude moct vybrat ze čtyř možností.
1 tutoriál
2 hra dvou hráčů na jednom počítači
3 hra proti počítači
4 konec


Tutoriál
V hlavním menu tutoriálu si hráč vybere, co ho zajímá.
1 tahy figurek
2 speciální tahy
3 zakončení hry
4 návrat do hlavního menu

Podle zvolené močnosti bude hráč přesměrován do konkrétního meníčka, kde si zvolí, co konkrétně se chce naučit.
Vše obsahuje krátký popis a následně praktickou ukázku.

Hra dvou hráčů
Oba hráči hrají z jednoho počítače a vždy se střídat, kdo je aktuálně na tahu. Hra odpovídá normální hře šachů.

Hra proti počítači
Hráč hraje proti jednoduchému AI, které je realizováno pomocí minimax algoritmu. Má možnost si vybrat ze tří úrovní AI, které se liší hloubkou prohledávacího stromu.

Konfigurační soubory
Celá hra se načítá z konfiguračních souborů. Pro tutoriál, hru dvou hráčů a hru proti počítači existují jednotlivé konfigurační soubory.
Pro tutoriál soubor obsahuje předpřipravené zprávy, které se zobrazují hráči.
Pro hru dvou hráčů a proti počítači se ze souboru načítá velikost šachovnice a rozestavení figurek.
