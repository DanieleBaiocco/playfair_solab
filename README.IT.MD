# Cifrario Playfair in C

Questo progetto è un'implementazione da riga di comando del **cifrario Playfair**, una tecnica di cifratura classica che lavora su coppie di lettere anziché su singoli caratteri.

Il programma legge un file chiave configurabile, costruisce una **griglia Playfair 5×5** e usa tale griglia per cifrare o decifrare uno o più file di testo. Il progetto è scritto in **C99** ed è pensato come un'implementazione didattica dei concetti principali del cifrario Playfair: costruzione della griglia a partire da una chiave, elaborazione dei digrammi, regole di sostituzione, preprocessing e gestione dell'input/output tramite file.

## Come funziona il progetto

Il cifrario Playfair lavora su **digrammi**, cioè coppie di caratteri.

Una matrice 5×5 viene costruita a partire da una chiave. Poiché l'alfabeto inglese contiene 26 lettere mentre la matrice dispone di sole 25 celle, una lettera deve essere omessa e associata a un'altra. Nell'esempio incluso nel progetto, l'alfabeto omette la `J`, che viene sostituita dalla `I`.

Per ogni coppia di lettere, il programma applica le classiche regole geometriche del Playfair:

- se entrambe le lettere si trovano sulla stessa riga, ciascuna viene sostituita dalla lettera alla sua destra;
- se entrambe le lettere si trovano nella stessa colonna, ciascuna viene sostituita dalla lettera sotto di essa;
- altrimenti, le due lettere formano gli angoli di un rettangolo e vengono sostituite dalle lettere poste sugli altri due angoli delle rispettive righe.

La decodifica applica le regole inverse.

Prima della cifratura, l'implementazione esegue anche alcune operazioni di preprocessing. Gli spazi vengono codificati in modo da poter essere ripristinati dopo la decodifica, il carattere mancante dell'alfabeto viene sostituito secondo la configurazione del file chiave e un carattere speciale viene utilizzato per il padding e la gestione dei caratteri ripetuti.

L'output cifrato viene scritto in un file con estensione `.pf`, mentre l'output decifrato viene scritto in un file `.dec`.

## Struttura del progetto

I file più rilevanti sono:

```text
.
├── main.c
├── playfair.c
├── playfair.h
├── utility.c
├── utility.h
├── deallocate.c
├── deallocate.h
├── CMakeLists.txt
└── example/
    ├── key.txt
    ├── message.txt
    └── results/
        ├── message.pf
        └── message.dec
```

Il repository contiene già un esempio completo ed eseguibile nella cartella `example/`.

## Requisiti

È necessario un compilatore C con supporto a C99, come **GCC**.

Su Windows, una soluzione comoda è utilizzare GCC tramite **MSYS2 / MinGW-w64**. Su Linux, GCC è normalmente disponibile tramite il package manager della distribuzione. Il progetto può essere compilato anche con CMake.

## Compilazione con GCC

Dalla cartella principale del progetto:

### Windows / MSYS2

```bash
gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair.exe
```

### Linux / macOS

```bash
gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair
```

## Compilazione con CMake

In alternativa:

```bash
cmake -S . -B build
cmake --build build
```

La posizione e il nome esatti dell'eseguibile generato possono dipendere dal sistema operativo e dal generatore utilizzato da CMake.

## Utilizzo da terminale

Il programma utilizza la seguente sintassi:

```text
playfair (encode|decode) <keyfile> <directory_output> <file> [altri_file...]
```

La directory di output deve esistere già.

### Cifratura

Su Windows / MSYS2:

```bash
./playfair.exe encode <keyfile> <directory_output> <file_input>
```

Su Linux / macOS:

```bash
./playfair encode <keyfile> <directory_output> <file_input>
```

Il file cifrato generato mantiene il nome base del file di input e usa l'estensione `.pf`.

Per esempio:

```text
message.txt -> message.pf
```

### Decodifica

Su Windows / MSYS2:

```bash
./playfair.exe decode <keyfile> <directory_output> <file_cifrato>
```

Su Linux / macOS:

```bash
./playfair decode <keyfile> <directory_output> <file_cifrato>
```

Il file decifrato generato usa l'estensione `.dec`.

Per esempio:

```text
message.pf -> message.dec
```

Il programma scrive il risultato nei file invece di stampare direttamente il messaggio cifrato o decifrato nel terminale.

## Formato del file chiave

Il file chiave non contiene soltanto una semplice frase. Contiene la configurazione utilizzata per costruire la griglia Playfair.

Il file di esempio `example/key.txt` contiene:

```text
ABCDEFGHIKLMNOPQRSTUVWXYZ
I
X
INTERESTING AND DIFFICULT KEY
```

Le righe hanno il seguente significato:

1. `ABCDEFGHIKLMNOPQRSTUVWXYZ` — l'alfabeto di 25 caratteri utilizzato dalla matrice 5×5;
2. `I` — il carattere sostitutivo della lettera mancante (`J` in questo esempio);
3. `X` — il carattere speciale utilizzato dalla logica di preprocessing;
4. `INTERESTING AND DIFFICULT KEY` — la chiave usata per costruire la griglia Playfair.

Non è necessario eliminare manualmente i caratteri duplicati dalla chiave: la logica di costruzione della griglia li gestisce durante la creazione della matrice.

## Esempio da terminale incluso

Il repository contiene un esempio già pronto nella cartella `example/`.

Il testo in chiaro contenuto in:

```text
example/message.txt
```

è:

```text
THIS IS AN IMPORTANT MESSAGE BE CAREFULL
```

La directory di output è:

```text
example/results/
```

### 1. Cifrare l'esempio

Dopo la compilazione, eseguire:

```bash
./playfair.exe encode example/key.txt example/results example/message.txt
```

Su Linux/macOS, utilizzare `./playfair` al posto di `./playfair.exe`.

Il programma crea:

```text
example/results/message.pf
```

Con la chiave e il messaggio inclusi nel progetto, il contenuto cifrato è:

```text
NM SC QV SC QV GT QV TB BP IE GT RW WB ID GD DN QV OI QV LS IR GY KW
```

È possibile visualizzarlo dal terminale con:

```bash
cat example/results/message.pf
```

### 2. Decodificare il file cifrato

Eseguire:

```bash
./playfair.exe decode example/key.txt example/results example/results/message.pf
```

Il programma crea:

```text
example/results/message.dec
```

Il suo contenuto è:

```text
THIS IS AN IMPORTANT MESSAGE BE CAREFUL
```

È possibile visualizzarlo con:

```bash
cat example/results/message.dec
```

Una sessione completa da terminale appare quindi così:

```bash
$ gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair.exe

$ ./playfair.exe encode example/key.txt example/results example/message.txt

$ cat example/results/message.pf
NM SC QV SC QV GT QV TB BP IE GT RW WB ID GD DN QV OI QV LS IR GY KW

$ ./playfair.exe decode example/key.txt example/results example/results/message.pf

$ cat example/results/message.dec
THIS IS AN IMPORTANT MESSAGE BE CAREFUL
```

L'assenza di output in console dopo `encode` o `decode` non indica necessariamente un errore: durante una normale esecuzione, il programma comunica principalmente il risultato creando il relativo file `.pf` o `.dec`.

## Note sull'input

L'implementazione attuale è pensata principalmente per testo alfabetico maiuscolo e spazi.

Con la configurazione di esempio:

- `J` viene convertita in `I`;
- gli spazi vengono rappresentati internamente in modo reversibile e ripristinati durante la decodifica;
- `Z` viene gestita tramite una codifica interna per poter convivere con il marcatore degli spazi;
- `X` viene utilizzata come carattere speciale/padding.

Per ottenere risultati prevedibili, utilizzare testo maiuscolo ed evitare punteggiatura o simboli arbitrari non supportati.

Si tratta di un'implementazione didattica e alcuni casi limite che coinvolgono lettere ripetute e il carattere speciale potrebbero non produrre un round-trip perfettamente identico byte per byte. Per esempio, il testo in chiaro incluso termina con `CAREFULL`, mentre il risultato decifrato incluso è `CAREFUL`.

## Più file in un unico comando

Il programma può elaborare più di un file con un singolo comando.

Per esempio:

```bash
./playfair.exe encode key.txt output file1.txt file2.txt file3.txt
```

Ogni file di input viene elaborato indipendentemente e scritto nella directory di output selezionata.

## Note

Il progetto è pensato principalmente per l'apprendimento e la sperimentazione con la crittografia classica e la programmazione in C. Il cifrario Playfair è storicamente interessante, ma **non è sicuro per l'uso crittografico moderno** e non deve essere utilizzato per proteggere informazioni sensibili.
