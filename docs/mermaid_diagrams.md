## 1. Main program (main.cpp)

### Flowchart – setup și loop

```mermaid
flowchart TD
    subgraph Main["main.cpp"]
        A([Start]) --> B{ACTIVE_APP_LAB == 2?}
        B -->|Da| C[app_lab_3_2_setup]
        B -->|Nu| D[app_lab_3_1_setup]
        C --> E[FreeRTOS scheduler rulează]
        D --> E
        E --> F([loop])
        F --> G{ACTIVE_APP_LAB == 2?}
        G -->|Da| H[app_lab_3_2_loop]
        G -->|Nu| I[app_lab_3_1_loop]
        H --> F
        I --> F
    end
```

---

## 2. Lab 3.1

### 2.1 FSM – Starea sistemului (app_sys_state_t)

```mermaid
stateDiagram-v2
    [*] --> IDLE
    IDLE --> ACQUIRING : Task encoder actualizează
    ACQUIRING --> ACQUIRING : Achiziție continuă
    ACQUIRING --> ERROR : Eroare mutex / citire
    ERROR --> ACQUIRING : Recuperare
```

### 2.2 Flowchart – app_lab_3_1_setup

```mermaid
flowchart TD
    A([app_lab_3_1_setup]) --> B[ddSerialStdioSetup]
    B --> C[Inițializare app_signals]
    C --> D[Creare xPrintfMutex, xStateMutex]
    D --> E[app_lab_3_1_task_encoder_setup]
    E --> F[app_lab_3_1_task_display_setup]
    F --> G[xTaskCreate task_encoder]
    G --> H[xTaskCreate task_display]
    H --> I[vTaskStartScheduler]
    I --> J([Scheduler preia controlul])
```

### 2.3 Flowchart – Task Encoder (Lab 3.1)

```mermaid
flowchart TD
    A([task_encoder]) --> B[xLastWakeTime = xTaskGetTickCount]
    B --> C[vTaskDelay offset]
    C --> D([Bucla infinită])
    D --> E[dd_encoder_ky040_update]
    E --> F{xStateMutex != NULL?}
    F -->|Da| G[Take xStateMutex]
    G --> H[Scrie position, direction, button, system_state]
    H --> I[Give xStateMutex]
    F -->|Nu| D
    I --> J[vTaskDelayUntil period]
    J --> D
```

### 2.4 Flowchart – Task Display (Lab 3.1)

```mermaid
flowchart TD
    A([task_display]) --> B[xLastWakeTime = xTaskGetTickCount]
    B --> C[vTaskDelay offset]
    C --> D([Bucla infinită])
    D --> E{Take xStateMutex?}
    E --> F[Citește pos, dir, btn, state]
    F --> G[Give xStateMutex]
    G --> H{changed?}
    H -->|Da| I{Take xPrintfMutex?}
    I --> J[printf raport]
    J --> K[last_pos, last_dir, last_btn = curent]
    K --> L[Give xPrintfMutex]
    L --> M[vTaskDelayUntil 500ms]
    H -->|Nu| M
    M --> D
```

### 2.5 Flowchart – app_lab_3_1_loop

```mermaid
flowchart LR
    A([app_lab_3_1_loop]) --> B[Gol / nimic]
```

---

## 3. Lab 3.2

### 3.1 Flowchart – app_lab_3_2_setup

```mermaid
flowchart TD
    A([app_lab_3_2_setup]) --> B[ddSerialStdioSetup]
    B --> C[Inițializare app_lab_3_2_signals]
    C --> D[Creare xLab32PrintfMutex, xLab32StateMutex]
    D --> E[app_lab_3_2_task_acquisition_setup]
    E --> F[app_lab_3_2_task_display_setup]
    F --> G[xTaskCreate task_acquisition]
    G --> H[xTaskCreate task_display]
    H --> I[vTaskStartScheduler]
    I --> J([Scheduler preia controlul])
```

### 3.2 Flowchart – Task Acquisition + Condiționare (Lab 3.2)

```mermaid
flowchart TD
    A([task_acquisition]) --> B[xLastWakeTime = xTaskGetTickCount]
    B --> C[vTaskDelay offset]
    C --> D([Bucla infinită])
    D --> E[dd_encoder_ky040_update]
    E --> F[raw = encoder.position]
    F --> G[salt_pepper_put raw]
    G --> H[after_sp = salt_pepper_output]
    H --> I[weighted_avg_put after_sp]
    I --> J[after_wa = weighted_avg_output]
    J --> K[physical = clamp after_wa]
    K --> L{Take xLab32StateMutex?}
    L --> M[Scrie raw, after_sp, after_wa, physical, sample_count++]
    M --> N[Give xLab32StateMutex]
    N --> O[vTaskDelayUntil period]
    O --> D
```

### 3.3 Flowchart – Task Display (Lab 3.2)

```mermaid
flowchart TD
    A([task_display]) --> B[xLastWakeTime = xTaskGetTickCount]
    B --> C[vTaskDelay offset]
    C --> D([Bucla infinită])
    D --> E{Take xLab32StateMutex?}
    E --> F[Citește raw, after_sp, after_wa, physical, sample_count]
    F --> G[Give xLab32StateMutex]
    G --> H{changed?}
    H -->|Da| I{Take xLab32PrintfMutex?}
    I --> J[printf raport condiționare]
    J --> K[Actualizare last_raw, last_after_sp, last_after_wa, last_physical]
    K --> L[Give xLab32PrintfMutex]
    L --> M[vTaskDelayUntil 500ms]
    H -->|Nu| M
    M --> D
```

### 3.4 Flowchart – Pipeline condiționare (Lab 3.2, detaliu)

```mermaid
flowchart LR
    A[Encoder raw] --> B[Filtru sare-piper]
    B --> C[Mediere ponderată]
    C --> D[Saturare]
    D --> E[Parametru fizic]
```

---

## 4. Overview – Lab 3.1 vs Lab 3.2

```mermaid
flowchart TB
    subgraph Lab31["Lab 3.1"]
        M1[main] --> S1[app_lab_3_1_setup]
        S1 --> T1A[Task Encoder]
        S1 --> T1B[Task Display]
        T1A --> |app_signals| T1B
    end
    subgraph Lab32["Lab 3.2"]
        M2[main] --> S2[app_lab_3_2_setup]
        S2 --> T2A[Task Acquisition]
        S2 --> T2B[Task Display]
        T2A --> |encoder → filtre → saturare| T2A
        T2A --> |app_lab_3_2_signals| T2B
    end
```

---

## 5. Secvență temporală – Lab 3.1

```mermaid
sequenceDiagram
    participant Main
    participant Setup as app_lab_3_1_setup
    participant Enc as Task Encoder
    participant Disp as Task Display
    Main->>Setup: setup()
    Setup->>Setup: Serial, mutexes, task setup
    Setup->>Enc: xTaskCreate
    Setup->>Disp: xTaskCreate
    Setup->>Main: vTaskStartScheduler()
    loop La fiecare T ms
        Enc->>Enc: dd_encoder_ky040_update
        Enc->>Enc: scrie app_signals
    end
    loop La fiecare 500 ms
        Disp->>Disp: citește app_signals
        alt date modificate
            Disp->>Disp: printf raport
        end
    end
```

---

## 6. Secvență temporală – Lab 3.2

```mermaid
sequenceDiagram
    participant Main
    participant Setup as app_lab_3_2_setup
    participant Acq as Task Acquisition
    participant Disp as Task Display
    Main->>Setup: setup()
    Setup->>Setup: Serial, mutexes, task setup
    Setup->>Acq: xTaskCreate
    Setup->>Disp: xTaskCreate
    Setup->>Main: vTaskStartScheduler()
    loop La fiecare T ms
        Acq->>Acq: encoder update → salt_pepper → weighted_avg → clamp
        Acq->>Acq: scrie app_lab_3_2_signals
    end
    loop La fiecare 500 ms
        Disp->>Disp: citește app_lab_3_2_signals
        alt parametri modificați
            Disp->>Disp: printf raport
        end
    end
```
