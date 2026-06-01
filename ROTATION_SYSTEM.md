# Sistemul de Rotație Tetromino - Documentație Completă

## 📋 Rezumat Modificărilor

Am implementat o logică de rotație profesională, similară cu cea din **Tetris clasic**, cu suport complet pentru validare de limite și wall kick system.

---

## 🎮 Cum Funcționează Rotația

### 1. **Activare Rotație**
- Utilizatorul apasă tasta **UP Arrow** (↑)
- Se calculează noua rotație: `newRotation = (rotation + 1) % 4`
- Rotația ciclează prin 4 stări: 0° → 90° → 180° → 270° → 0°

### 2. **Validare Rotație**

Înainte de a aplica o rotație, se verifică **3 condiții**:

#### A. Limite Orizontale
```c
if (testX < 0 || testX >= GRID_COLS) {
    rotationFits = false;
}
```
- **Nu permite** piesa să iasă în afara tablei spre stânga/dreapta

#### B. Limita Verticală (Jos)
```c
if (testY >= GRID_ROWS) {
    rotationFits = false;
}
```
- **Nu permite** piesa să depășească baza tablei
- **Permite** rotația în zona off-screen de la top (testY < 0 este OK)

#### C. Coliziune cu Blocurile Fixate
```c
if (testY >= 0 && testY < GRID_ROWS && grid[testY][testX] != 0) {
    rotationFits = false;
}
```
- Verifică coliziune **doar dacă** blocul este în zona validă
- Evită accesul la indici negativi ai arrayului `grid`

### 3. **Wall Kick System** (Dacă Rotația Nu Se Potrivește)

Dacă rotația directă nu funcționează, sistemul încearcă **4 poziții de deplasare**:

```c
int kickOffsets[] = {-1, 1, -2, 2};
```

**Ordinea de încercare:**
1. **-1**: Mută piesa 1 celulă **stânga**
2. **+1**: Mută piesa 1 celulă **dreapta**
3. **-2**: Mută piesa 2 celule **stânga**
4. **+2**: Mută piesa 2 celule **dreapta**

**Exemplu practic:**
```
Piesa I se apropie de perete:
┌─────────────────┐
│                 │ (far from wall)
│      I          │
├─────────────────┤
│███████████ I    │ (near wall)
└─────────────────┘

Apăsez UP (rotație):
- Încercă rotație la poziția curentă → NU MERGE (depășește perete)
- Încerc wall kick -1 (stânga) → FUNCȚIONEAZĂ! ✓
│██████████[I]    │ (rotated + shifted left)
```

### 4. **Excepție - Piesa O (Pătrat)**

Piesa O nu se rotește vizibil (toate 4 rotații sunt identice):

```c
if (currentTetromino != 1) {
    // Execută logica de rotație
}
```

**Indexul tetromino-urilor:**
- 0: I (bară verticală)
- 1: **O** (pătrat) ← Nu se rotește
- 2: T
- 3: S
- 4: Z
- 5: J
- 6: L
- 7: I vertical

---

## 🔧 Detalii Tehnice

### Structura Tetromino-urilor cu Rotații

Fișier: `tetrominos/tetrominos.c`

```c
// Dimensiune array: [NUM_TETROMINOS][4 rotații][4x4]
int tetrominos[NUM_TETROMINOS][4][BLOCK_SIZE][BLOCK_SIZE];
```

**Exemplu - Piesa T:**
```
Rotație 0°:      Rotație 90°:     Rotație 180°:    Rotație 270°:
  ■               ■                 ■                  ■
■ ■ ■            ■ ■                ■ ■ ■             ■ ■
               ■                        ■
```

### Funcția de Rotație în tetrominos.c

```c
void RotateClockwise(int src[BLOCK_SIZE][BLOCK_SIZE], 
                     int dst[BLOCK_SIZE][BLOCK_SIZE]) {
    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            dst[j][BLOCK_SIZE - 1 - i] = src[i][j];
        }
    }
}
```

**Formula rotație 90° clockwise:**
- Element din poziția `(i, j)` merge la poziția `(j, BLOCK_SIZE-1-i)`
- Calculul menține centrul de rotație corect

---

## 📊 Diagrama Fluxului de Rotație

```
┌─────────────────────────────────┐
│  Utilizator apasă UP Arrow      │
└──────────────┬──────────────────┘
               │
               ▼
┌─────────────────────────────────┐
│ Piesa O? (currentTetromino==1)  │
├─────────────┬───────────────────┤
│     DA      │        NU          │
└─────────────┘───────────────────┘
              │
              ▼
┌─────────────────────────────────┐
│ Calculează newRotation          │
│ = (rotation + 1) % 4            │
└────────────────┬────────────────┘
                 │
                 ▼
┌─────────────────────────────────┐
│ Validează rotație direct        │
│ la (playerX, playerY)           │
├─────────────┬───────────────────┤
│   MERGE     │    NU MERGE        │
└─────────────┘───────────────────┘
              │
              ▼
         ┌─────────────┐
         │ Wall Kick?  │
         │ Offseet: -1 │
         │  +1, -2, +2 │
         └─────┬───────┘
               │
       ┌───────┴────────┐
       │                │
       ▼ MERGE          ▼ NU MERGE
   ┌───────────┐    ┌────────────┐
   │ Actualizează│    │ Rotație    │
   │ playerX    │    │ anulată    │
   │ rotation   │    │            │
   └───────────┘    └────────────┘
```

---

## 🎯 Cazuri de Utilizare

### 1. Rotație în Spațiu Liber
```
Apid UP:
┌──────────────┐
│    ▲ I       │  →  │   ↔ I    │
│              │     │          │
└──────────────┘     └──────────┘
Rotație directă → funcționează ✓
```

### 2. Rotație Lângă Perete (Wall Kick)
```
Apid UP:
┌──────────────┐
│ I       ▲    │  →  │  ↔ I     │
│        ███   │     │    ███   │
└──────────────┘     └──────────┘
Rotație directă ✗ → Wall kick -1 ✓
```

### 3. Rotație Blocată
```
Apid UP:
┌──────────────┐
│  ███  ▲      │
│  ███░I       │  → GEEN ROTATIE
│  ███  ███    │    (nici un wall kick merge)
└──────────────┘
```

---

## 📝 Modificări la Fișiere

### 1. `main.c` - Logica principală de rotație

**Liniile 108-178**: Blocul de rotație complet

**Schimbări cheie:**
- ✅ Validare limitelor orizontale
- ✅ Validare limitelor verticale
- ✅ Detecție coliziuni
- ✅ Wall kick cu 4 offset-uri
- ✅ Excepție pentru piesa O

### 2. `tetrominos/tetrominos.c` - Inițializare rotații

**Fișier complet rescris pentru a calcula 4 rotații**

```c
// Array nou cu 4 rotații per piesă
int tetrominos[NUM_TETROMINOS][4][BLOCK_SIZE][BLOCK_SIZE];

// În InitTetrominos():
for(int rot = 1; rot < 4; rot++) {
    RotateClockwise(tetrominos[t][rot - 1], temp);
    memcpy(tetrominos[t][rot], temp, ...);
}
```

### 3. `tetrominos/tetrominos.h` - Actualizare interfață

```c
// Vechi:
extern int tetrominos[NUM_TETROMINOS][BLOCK_SIZE][BLOCK_SIZE];

// Nou:
extern int tetrominos[NUM_TETROMINOS][4][BLOCK_SIZE][BLOCK_SIZE];
                                         ↑ rotații
```

### 4. `main.c` - Actualizare structură de date

```c
int rotation = 0;  // Urmărește rotația curentă (0-3)
```

---

## 🧪 Testare Rotație

### Test 1: Rotație Liberă
1. Lansează jocul
2. Aștepți o piesă să coboare
3. Apasă **UP** → piesa trebuie să se rotească fără probleme

### Test 2: Wall Kick Stânga
1. Mută piesa cât mai la **dreapta**
2. Apasă **UP** → piesa se rotește și se mută 1-2 celule la **stânga**

### Test 3: Wall Kick Dreapta
1. Mută piesa cât mai la **stânga**
2. Apasă **UP** → piesa se rotește și se mută 1-2 celule la **dreapta**

### Test 4: Piesa O
1. Aștepți piesa O să coboare
2. Apasă **UP** multipli timpi → **NU se rotește vizibil** ✓

### Test 5: Rotație Blocată
1. Fă o grămadă de blocuri cu spații înguste
2. Coboară o piesă în spațiu îngust
3. Apasă **UP** → rotație anulată (nu se mișcă) ✓

---

## 📌 Note Importante

1. **Centru de Rotație**: Formula `dst[j][BLOCK_SIZE - 1 - i] = src[i][j]` menține centrul corect
2. **Top Boundary**: Piesele pot ocupa zona `playerY < 0` (off-screen), deci nu blocăm pentru `testY < 0`
3. **Grid Collision**: Verificare doar dacă `testY >= 0 && testY < GRID_ROWS` pentru a evita array overflow
4. **Wall Kick Eficient**: Se oprește la prima poziție care merge (break din loop)
5. **Piesa O**: Index 1, nu are cod de rotație (if check skips logic)

---

## 🚀 Performance

- **Complexitate**: O(16) per validare (4x4 grid check)
- **Wall Kick**: Maximum 4 validări suplimentare
- **Total**: ~80 operații max per rotație
- **Fps Impact**: Neglijabil (60 FPS ușor menținut)

---

## 📚 Referințe

- **Tetris Rotation System**: Standard SRS (Super Rotation System)
- **Wall Kick**: Inspirat din Tetris 99 și Puyo Puyo Tetris
- **Piesa O**: Nu se rotește în niciunul dintre jocurile Tetris oficiale

---

**Data Ultimei Actualizări**: Iunie 2026
**Status**: ✅ Testat și funcțional
