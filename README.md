# Analisi e Valutazione delle Performance di WebAssembly System Interface

WebAssembly, abbreviato in Wasm, è un linguaggio di programmazione nato nel 2015 che consente di eseguire codice originariamente scritto in diversi linguaggi di programmazione, come ad esempio C, C++, Rust e Python, all'interno di un ambiente isolato, chiamato runtime, in modo sicuro ed efficiente, originariamente pensato per essere eseguito all'interno del browser. Successivamente è stato creato WASI, ovvero WebAssembly System Interface, che amplia la possibilità di utilizzo di Wasm al di fuori del solo browser, permettendo in aggiunta la comunicazione con le risorse di sistema. L'obiettivo di questa tesi è valutare le performance di diversi runtime WebAssembly e delle loro implementazioni di WASI, confrontandoli in base a parametri e scenari d'uso differenti, grazie all'impiego della libreria Libsodium come caso studio. Per far ciò sono stati analizzati diversi aspetti dei vari runtime Wasm riguardo alla velocità di esecuzione, velocità di lettura e scrittura file, integrazione con le socket e conformità a WASI. Dai risultati di questi test risulta come WebAssembly sia una tecnologia estremamente promettente, soprattutto in termini di portabilità e velocità di esecuzione, sebbene sia ancora in fase di sviluppo, e contenga, di conseguenza, ancora svariate criticità e difficoltà d'uso.

## Cartelle

- `plots`: contiene i plot dei risultati dei test in formato .pdf
- `wasm`: contiene tutti i file wasm che possono essere testati
- `results`: contiene tutti i file in formato .txt con il tempo di esecuzione per ogni file
- `socket_test`: contiene uno sviluppo futuro che avevo iniziato ma mai concluso, che può essere uno spunto da continuare
