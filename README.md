# Controle de Servos e Motores

## Detalhes Técnicos

- Autor: _Leonardo dos Santos_
- Data de Criação: _17 de junho de 2023_
- Última Atualização: _02 de outubro de 2023_

## Descrição do Projeto

Este projeto consiste em um código Arduino para controlar servos e motores de acordo com a entrada do volante e botões. Ele usa as bibliotecas `ServoEngine.h` para controlar os servos e `ServoEngineCC.h` para a lógica de controle dos motores. Além disso, há uma funcionalidade de gravação dos movimentos dos servos proporcionada pela `ServoRecorder.h`.

## Hardware Necessário

- Placa Arduino compatível (por exemplo, Arduino Uno, Arduino Mega).
- Servos para controle de movimento
- Motores para movimentação
- Sensor de volante
- Botões de controle
- Conexões de acordo com a pinagem especificada abaixo.

## Uso / Instalação

- Carregue o código no Arduino IDE.
- Conecte o Arduino à sua configuração de hardware.
- Certifique-se de ter a biblioteca `Servo.h` instalada no seu Arduino IDE.
- Faça as devidas conexões de acordo com a pinagem mencionada acima.
- Carregue o programa no Arduino.

## Funcionamento:

O programa lê a entrada do sensor do volante e controla os servos e motores de acordo com essa entrada e os botões de controle. O estado de gravação e execução pode ser alternado com os botões correspondentes.

## Pinagem dos servos:

### Portas analógicas

| Servo  | Nome da Porta  | Pin |
| :----- | :------------- | :-: |
| Base   | baseServoPin   | `A0`  |
| Braço  | bracoServoPin  | `A1`  |
| Altura | alturaServoPin | `A2`  |
| Garra  | garraServoPin  | `A3`  |

### Portas digitais:

| Servo  | Nome da Porta        | Pin |
| :----- | :------------------- | :-: |
| Base   | baseServoPinNumber   |  3  |
| Braço  | bracoServoPinNumber  |  5  |
| Altura | alturaServoPinNumber |  6  |
| Garra  | garraServoPinNumber  |  9  |

### Pinagem dos motores:

| Motor          | Positivo    | Negativo    | Leitor de Velocidade | Leitor de Direção |
| :------------- | :---------- | :---------- | :------------------- | :---------------- |
| Motor direito  | positivePin | negativePin | speedPin             | rightEnablePin    |
| Motor esquerdo | positivePin | negativePin | speedPin             | leftEnablePin     |

#### Pinos:

| Nome           | Pin |
| :------------- | :-: |
| positivePin    |  6  |
| negativePin    |  9  |
| speedPin       | `A0`  |
| volantPin      | `A1`  |
| rightEnablePin |  3  |
| leftEnablePin  |  5  |

#### Botões:

| Botão              | Nome             | Pin |
| :----------------- | :--------------- | :-: |
| início da gravação | BTN_START_RECORD |  7  |
| gravação           | BTN_RECORD       |  2  |
| execução           | BTN_EXECUTE      |  4  |

## Comandos de inversão de controle:

- `RECORD + EXECUTE`: _Troca o controle dos motores para os servos e vice-versa_

## Bibliotecas Utilizadas

#### As bibliotecas usadas fazem parte deste repositório

- ServoEngine - Biblioteca para controle de servo motores.
- ServoEngineCC - Controle de direção para carro protótipo.
- ServoRecorder - Gravação e execução de sequências de movimento para servos.

# SvRecorder - Gravação e Execução de Sequências de Movimento para Servos

é uma biblioteca para Arduino que facilita a gravação, armazenamento e execução de sequências de movimento para servomotores.

## Funcionalidades

- Gravação de sequências de movimentos de servomotores.
- Armazenamento das sequências em memória.
- Execução das sequências gravadas.

## Uso

1. Inclua a biblioteca ServoRecorder no seu sketch Arduino.

```cpp
 #include <ServoRecorder.h>
```

2. Crie uma instância da classe SvRecorder.

```cpp
SvRecorder svRecorder;
```

3. Configure e utilize as funções da SvRecorder conforme necessário para gravar e executar sequências de movimentos para servomotores.
   - Você pode manter a configuração padrão, apenas seguindo as tabelas acima **Portas**, **Pinos**, **Botões**.

## Comandos Disponíveis

_SvRecorder_ Possui alguns comando que podem ser utilizados. Para executar corretamente sempre precione primeiro o botão **Gravar**, pois ele não executa nenhuma função que deixa o sistema em execução.

- `START_RECORD`: _Troca de **Gravando** para **Manual** e vice-versa_

- `RECORD`: _Grava a ultima posição em que o servo foi deixado_

- `EXECUTE`: _Executa as posições que foram gravadas_

- `RECORD + START_RECORD`: _Limpa as movimentos gravados_

## Métodos Disponíveis

_Construtor da classe SvRecorder._

```cpp
SvRecorder(int recButton, int startRecButton, int executeButton)
```

- `listening()` : _Monitora os botões e a lógica de gravação/execução._
- `joystick()` : _Simula o movimento dos servos durante a gravação._
- `recording()` : _Realiza o processo de gravação dos movimentos dos servos._
- `recordStep()` : _Grava um passo do movimento atual._
- `executeSequence()` : _Executa a sequência de movimento gravada._
- `invertAxis(int engineId)` : _Inverte a direção do movimento para um determinado motor._
- `includeServo(SvEngine list[SERVO_LIST_SIZE])` : _Inclui a lista de motores para a gravação e execução._
- `handleIsRecording()`: _Lida com o início e término da gravação._
- `swapRecording()`: _Alterna entre os modos de gravação e execução._
- `isResetMemory()`: _Verifica se é necessário redefinir a memória._
- `calibrateServos()`: _Calibra os servos antes de executar a sequência._
- `calibrateEveryRound(bool calibrate)` : _Define se a calibração dos servos é feita a cada execução._
- `setExecuteSequenceState()` : _Define o estado de execução da sequência._
- `getIsRecord()` : _Verifica se está no modo de gravação._
- `getIsExecute() const` : _Verifica se está no modo de execução._
- `getIsRecording() const` : _Verifica se está gravando._
- `getIsStartRecording() const` : _Verifica se o botão de início de gravação foi pressionado._

## Exemplo de uso:

```cpp
#include "ServoRecorder.h"
#include "ServoEngine.h"

SvRecorder recorder(BTN_RECORD, BTN_START_RECORD, BTN_EXECUTE);

//Utilize o valor Interno da classe SERVO_LIST_SIZE para garantir o tamanho correto da lista dos motores

SvEngine servos[recorder.SERVO_LIST_SIZE];  // Crie um array de objetos da classe SvEngine com os servos desejados

void setup() {
  // Inicializações
  recorder.includeServo(servos);  // Inclui os servos no gravador
}

void loop() {
  recorder.listening();  // Monitora os botões e executa a lógica de gravação e execução
}
```

## Execução

- Certifique-se de que os componentes estejam devidamente conectados.
- Pressione o botão **Iniciar Gravação** _(BTN_START_RECORD)_ para começar a gravação.
- Realize os movimentos desejados com os servomotores.
- Pressione o botão **Gravar** _(BTN_RECORD)_ para salvar a sequência de movimentos.
- Para **executar a sequência** gravada, pressione o botão **Executar** _(BTN_EXECUTE)_.

# ServoEngine - Biblioteca para Controle de Servo Motores

Esta biblioteca representa um mecanismo de controle para um servo motor, fornecendo métodos e funcionalidades essenciais para ajustar a velocidade, ângulos, direção e sensibilidade do motor. A classe `ServoEngine` permite calibrar e movimentar o motor com precisão, facilitando sua integração em projetos que necessitam de posicionamento e controle preciso de objetos físicos. Sua flexibilidade e capacidade de adaptação tornam-na uma peça fundamental para projetos de automação e robótica.

## Uso

Para utilizar a biblioteca **SvEngine** em seu projeto

1. Inclua a biblioteca ServoEngine no seu sketch Arduino.

```cpp
 #include <ServoEngine.h>
```

2. Crie uma instância da classe **SvEngine**.

```cpp
SvEngine svEngine(/*parâmetros*/);
```

3. Utilize os métodos disponíveis para controlar o motor conforme necessário.

## Métodos Disponíveis

_Construtor da classe ServoEngine._

```cpp
SvEngine(int engineId, int pin, int pw, int center, int min, int max, int maxRPM = ?, int neutral = ?)
```

- `joystick()`: _Controla o motor a partir de um joystick ou entrada análoga._
- `autoMove(int newAngle)`: _Move o motor automaticamente para um ângulo específico._
- `calibrate(bool centralize, int angle)`: _Calibra o motor para uma posição central ou um ângulo específico._
- `isMoving() const`: _Verifica se o motor está em movimento._
- `invertAxis()`: _Inverte a direção do movimento do motor._
- `incrementAngle()`: _Incrementa o ângulo do motor._
- `decrementAngle()`: _Decrementa o ângulo do motor._
- `setSpeed()`: _Configura a velocidade do motor._
- `setSignal()`: _Configura o sinal do motor._
- `setBoost(int value)`: _Define um impulso adicional para o motor._
- `setAutoSpeedPW(int autoPW)`: _Configura o autoPWM do motor._
- `setEngineId(int engineId)`: _Define o ID do motor._
- `setComandAutoAcceleration(bool comand)`: _Ativa ou desativa a aceleração automática do motor._

### Exemplo de uso:

```cpp
Copy code
#include "ServoEngine.h"

SvEngine meuMotor(1, 9, A0, 90, 0, 180);

void setup() {
  // Inicializações
}

void loop() {
  // Controle do motor
  meuMotor.joystick();
}
```

# EngineCC - Controle de Direção para Carro Protótipo

Esta biblioteca oferece uma solução para facilitar o controle de direção de um carro protótipo. Ela permite controlar a aceleração do motor e, ao incluir um segundo motor, determinar a direção em que o carro protótipo deve se movimentar. O ângulo para o volante deve ser respeitado de 0 a 100 para o correto funcionamento do programa.

## Uso

Para utilizar a biblioteca **ServoEngineCC** em seu projeto

1. Inclua a biblioteca ServoEngineCC no seu sketch Arduino.

```cpp
 #include <ServoEngineCC.h>
```

2. Crie uma instância da classe **EngineCC**.

```cpp
EngineCC meuCarro(/*parâmetros*/);
```

3. Utilize os métodos disponíveis para controlar a direção e a aceleração do carro conforme necessário.

## Métodos Disponíveis

_Construtor da classe EngineCC._

```cpp
EngineCC(int enable, int positive, int negative, int potentiometer, int sensibility, int center, int offSet)
```

- `setupPins()`: _Configura as pinagens dos motores._
- `setSteeringAngle(bool rotateClockwise, int angle)`: _Define o ângulo de direção do volante._
- `readAcceleration()`: _Lê a aceleração do motor._
- `setMotorDirection(int pos, int neg)`: _Configura a direção do motor._
- `adjustVelocity(bool neutral, int acceleration)`: _Ajusta a velocidade do motor._
- `writeAngle(int value)`: _Escreve um ângulo específico._
- `performMovement()`: _Executa o movimento do carro._
- `setEndEngageAngle(int value)`: _Define o ângulo de engajamento final._
- `setEngageAngle(int value)`: _Define o ângulo de engajamento._

### Exemplo de uso:

```cpp
#include "ServoEngineCC.h"

EngineCC meuCarro(9, 10, 11, A0, 50);

void setup() {
  // Inicializações
}

void loop() {
  // Controle do carro
  meuCarro.setSteeringAngle(true, 45);  // Gira o volante
  meuCarro.adjustVelocity(false, 512);  // Ajusta a velocidade
  meuCarro.performMovement();         // Executa o movimento
}
```

## Contribuindo

_Sinta-se à vontade para contribuir com melhorias ou correções para esta biblioteca. Basta fazer um fork deste repositório, fazer suas alterações e enviar um pull request._
