# Battery-Monitoring-System-V1
Projeto de Monitoramento de Parâmetros Elétricos e Térmicos de Duas Células de Bateria de 4 V

## Descrição
Este projeto realiza a medição da tensão e da corrente utilizando o sensor INA219 current sensor module por meio do protocolo I²C, além de monitorar a temperatura através de um termistor NTC222 conectado a um conversor ADC.

Quando a temperatura de uma das duas células ultrapassa um determinado limiar (threshold), um buzzer é acionado como mecanismo de alerta.

<img width="867" height="647" alt="image" src="https://github.com/user-attachments/assets/1de3c8cd-b232-4d75-a8cb-32c14abadd69" />


## Materiais
Para a implementação deste projeto, foram utilizados os seguintes componentes: duas células de bateria de 4 V com suporte (shell), dois sensores de corrente e tensão INA219 current sensor module, dois termistores NTC 222, dois resistores de 10 kΩ, dois resistores de 1 kΩ, um buzzer, um Arduino Uno R3, além de uma protoboard e cabos jumpers para as conexões.

## Conexões 
Como foram utilizados dois sensores INA219 current sensor module, foi necessário configurar endereços I²C distintos para cada dispositivo. O primeiro sensor foi mantido no endereço padrão (0x40), enquanto o segundo teve seu endereço ajustado para 0x44 por meio da configuração de offset.

O buzzer foi conectado ao pino digital 7 do Arduino Uno. A comunicação I²C foi realizada utilizando o pino analógico A4 como SDA e o pino A5 como SCL.

Para a medição de temperatura, os termistores foram ligados a divisores resistivos: o primeiro conectado ao pino A0 e o segundo ao pino A1 do microcontrolador.

Abaixo um esquema das conexões feitas:
<img width="934" height="612" alt="Circuitousado" src="https://github.com/user-attachments/assets/78432908-aa4f-4996-a0f1-257dae3942b5" />

