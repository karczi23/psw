# Port

## Treść zadania:
Do portu zawijają statki, cumują w nim przez jakiś czas i go
opuszczają. Każdy statek zarówno w celu wejścia do portu, jak i
wyjścia z niego musi dostać pewną liczbę holowników, zależną od jego
masy. Musi być też dla niego miejsce w doku. Zarówno liczba miejsc w
doku, jak i liczba holowników są ustalone i ograniczone.
Cel zadania: synchronizacja statków (doki i holowniki to zasoby)

## Sposób implementacji:
Do wykonania zadania użyte zosttały mutexy oraz wątki z biblioteki `thread`. Liczba doków i holowników jednocześnie możliwych do użycia oraz liczba statków (wątków(, które muszą zostać obslużone jest zdefiniowana na początku pliku. Przy każdej próbie odczytu i modyfikacji zmiennych odpowiedzialnych za wartość obecnie dostępnych doków/holowników blokowowane są odpowiednie mutexy

## Kompilacja i uruchomienie:
W terminalu:
`g++ -Wall port.cpp`

Następnie uruchomienie pliku `a.out`
