histogram
=========

newhist    tworzy nowy (pusty) histogram

print      wypisuje zawartosc histogramu wskazanego przez set1
printall   wypisuje zawartosc wszystkich histogramow
howmany    wypisuje licznosc histogramow

set1 [indeks]       ustawia pierwszy indeks pomocniczy
set2 [indeks]       ustawia drugi indeks pomocniczy

addh       dodaje histogramy (wskazane przez sum1 i sum2, wynik wrzuca jako nowy histogram)
subh       odejmuje histogramy (j/w)
mulh       mnozy histogramy - generuje przeciecie (j/w)

addval [klucz] [wartosc]     dodaje wartosc do histogamu wskazanego przez set1
subval [klucz] [wartosc]     odejmuje wartosc od histogramu wskazanego przez set1
setval [klucz] [wartosc]     ustawia wartosc w histogramie wskazanym przez set1
getval [klucz]               wypisuje wartosc

debug      wypisuje wiadomosc diagnostyczna
quit       wychodzi z programu

