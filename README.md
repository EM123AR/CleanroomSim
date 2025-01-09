# CleanroomSim
Progetto per il corso di Programmazione ad Oggetti (BSc Informatica, A.A. 2023/24) dell'Università di Padova.

# Introduzione
L’obiettivo del progetto è sviluppare una simulazione di sensori, ad esempio
sensori che rilevano temperatura, umidità, presenza di polveri sottili o altri
fenomeni, utilizzando il linguaggio di programmazione C++ e il framework Qt
per creare un’interfaccia grafica utente. In questa simulazione, gli utenti finali
dell’applicazione devono essere in grado di definire nuovi sensori, modificare e
cancellare quelli esistenti, oltre ad avviare una simulazione. Si incoraggia l’uso di
design pattern appropriati, benché non sia obbligatorio. Il progetto potrà essere
sviluppato da un singolo studente e dovrà richiedere approssimativamente 50 ore di lavoro complessivo.

# Vincoli
Il progetto deve obbligatoriamente soddisfare i seguenti vincoli:
1. essere un lavoro originale dello studente
2. essere interamente scritto in C++
3. prevedere un’interfaccia grafica realizzata in Qt
4. compilare senza errori sulla macchina virtuale fornita (sono tollerati,
sebbene generalmente penalizzati, i warning durante la compilazione)
5. realizzare i principi di incapsulamento e information hiding della
buona programmazione ad oggetti
6. mantenere una separazione netta tra il modello logico e l’interfaccia
grafica
7. eseguire in maniera efficiente e robusta, senza errori a runtime
8. utilizzare il polimorfismo in maniera non banale
9. implementare una gerarchia di classi per i sensori con almeno tre classi
concrete
10. consentire la creazione, la ricerca, la modifica e la cancellazione dei
sensori, tali operazioni devono essere fruibili tramite interfaccia grafica
11. realizzare la persistenza dei dati dei sensori
12. consentire, tramite l’interfaccia grafica, il salvataggio e il caricamento
di un file di sensori (come descritto al punto precedente) attraverso
opportune finestre di dialogo: non è consentito l’utilizzo di percorsi di file
di sensori cablati nel codice sorgente
13. consentire, tramite interfaccia grafica, di avviare una simulazione per
un sensore selezionato, simulando un certo numero di raccolte di dati; i
dati dovranno essere quindi mostrati in maniera opportuna, ad esempio
tramite QtCharts
14. essere corredato di una relazione in formato pdf, in lingua italiana o
inglese

# Criteri di valutazione
Il progetto viene valutato sulla base dei vincoli obbligatori e delle funzionalità
implementate. Più precisamente, se uno o più vincoli obbligatori non
risultano soddisfatti il progetto verrà considerato insufficiente. Viceversa, se tutti i
vincoli obbligatori sono soddisfatti il progetto è considerato (almeno)
sufficiente e la valutazione aumenterà in base alla qualità delle funzionalità
sviluppate e, in misura minore, in base alla qualità della relazione.
Una funzionalità viene valutata positivamente in base alla sua pertinenza al
tema, all’utilità, all’usabilità, alla complessità e alla qualità del codice attraverso
cui è implementata. Funzionalità più semplici o generiche migliorano la valutazione, sebbene 
non tanto quanto idee più complesse o articolate.




# Valutazione
Feedback Progetto di Programmazione ad Oggetti

Studente: Artusi Emanuele

Valutazione del progetto: Lode

Vincoli obbligatori
+ Soddisfatti


Orientamento ad oggetti
+ Incapsulamento
+ Modularità (modello logico e la GUI sono separati)
+ Estensibilità ed evolvibilità, polimorfismo
+ Efficienza e robustezza


Funzionalità
+ Complessivamente molto curato, funzionalità ben implementate
  e descritte nella relazione


GUI
+ Visualizza i diversi tipi di dato in maniera opportuna
+ Usabile e intuitiva
+ Robusta, gestisce ridimensionamento
+ Utilizza icone
+ Utilizza immagini
+ Utilizza stili


Relazione
+ Adeguata


Suggerimenti non collegati alla valutazione

Nessuno.
