
### STM32F411RE RTOS 기반 비동기 제어 시스템

## 프로젝트 개요
STM32F411RE 보드를 기반으로 GPIO, TIM, UART, Interrupt, FreeRTOS Task,Queue를 활용한 비동기 제어 시스템을 구현하는 프로젝트입니다.

초기에는 TIM Interrupt와 main loop 기반의 Stopwatch 기능 구현으로 시작했지만, 기능 확장 과정에서 main.c의 복잡도 증가와 애플리케이션이 하드웨어에 종속되는 문제를 발견했고, 이를 개선하기 위해 HW Wrapper 계층구조로 리팩토링하여 상위 계층에서 하드웨어를 직접 조작하지 않게 하였습니다.

이후 임의의 시스템인 Smart Blind를 구성하여 UART 명령 수신 → Parser → Command Queue → Smart Blind FSM → Servo Command Queue → Servo Task → PWM으로 이어지는 비동기 제어 흐름을 구현하였습니다.

각 HW 모듈은 채널 정보를 통해 여러 인스턴스를 처리할 수 있도록 구성하여 재사용성을 고려하였으며,애플리케이션의 상태를 한 모듈만이 소유하여 이벤트가 발생하면 상태를 전이하는 방식을 사용하여 모듈간의 의존을 최소화 하였습니다. 또한 Task 간 데이터 전달에는 Queue를 사용하고,주기적인 이벤트가 없는 Task는 대기하도록 구성하여 지속적인 polling을 최소화하였습니다.

## 현재 구현 상태
- UART Interrupt RX
- 명령 Passer
- Queue 기반 task간 통신
- Smatblind, Stopwatch FSM
- Servo PWM 제어
- HD44780 LCD 출력 

## 추가 예정
- 센서 상태기반 자동 제어 정책
- Linux Gateway 연동
- 정량적 측정 기반 TASK Stack Size 최적화, RTOS Queue Length 산정
- Task Priority 설계

## 주요 데이터 흐름

<img width="651" height="775" alt="RTOS_SYSTEM drawio (2)" src="https://github.com/user-attachments/assets/6ecc0287-07f6-4040-9ea8-bd335aa109a7" />


**STOPWATCH**

UART_RX_ISR > Uart_Rx_Queue > uart_cmd_task > uart_cmd_process(parser) > Sw_Cmd_Queue > sw_task > sw_module


**SMART_BLIND**

PC terminal

-> uart_rx_Interrupt(hw/driver/uart)

-> uart_rx_queue(hw/driver/uart)

-> uart_cmd_task(rtos/uart_cmd_task)

-> uart_cmd_process(ap/module/uart_cmd)

-> smart_blind_queue(rtos/uart_cmd_task)

-> smart_blind_task(rtos/smart_blind_task)

-> smart_blind_process(ap/module/smart_blind)

-> servo_motor_queue(rtos/smart_blind_task)

-> servo_motor_task(rtos/servo_motor_task)

-> servo_motor_process(ap/module/servo_motor)

-> hw_motor(hw/driver/hw_motor)

-> hw_tim_pwm(hw/driver/hw_tim)

---
## 트러블슈팅
| 문제 | 원인 | 해결 |
|---|---|---|
| 전역 변수 유실 가능성 | ISR-메인루프 간 타이밍 불일치 | RTOS Queue 기반 통신으로 전환 |
| ISR 미진입 | NVIC 인터럽트 미활성화 | NVIC Table Enable 적용 |
| 데이터 송신 시 HardFault | RTOS Queue 생성 이슈 | Queue 생성 조정 |
| 파서 쓰레기 값 유입 | TX/RX Baudrate 불일치 | 버퍼 오버플로우 방어 로직 적용, 추가 예외처리 검토 중 |
| CCR 오동작 | `uint8 angle` 256 이상 입력 시 overflow | 파서 단에서 180도 초과 값 사전 차단 예정 |
---
## 사용기술


**STM32F411RE, FreeRTOS, UART, TIM/PWM, GPIO, Interrupt, HD44780 LCD, HAL, ST-LINK Debugger, Tera Term, Logic Analyzer,SG90, HD44780**

---
## 개발 기록

### v.2.0 아키텍처 리팩토링 및 검증

**1. AP/HW 계층 분리**
- AP/HW 계층을 분리하고 계층간의 의존성을 분리했습니다.
- 계층 분리의 동작을 검증하기 위한 메인 루프만을 테스트한 버전입니다.

**2. 한계점과 향후 계획**
- 현재 sw_tim 업데이트 이벤트의 ISR에서 메인루프의 지연으로 인해 전역변수가 유실 될 수 있다는 점을 확인했습니다.
- 전역변수의 한계를 느끼고 RTOS의 메세지 큐를 활용한 모듈간 통신을 검토중입니다.

---

### v.2.1 RTOS 아키텍처 사전 준비 및 STOPWATCH_TASK 추가
**1. RTOS task 실행 계층 추가**
- FreeRTOS Scheduler에 의해 실행되는 Task 코드를 scheduler 계층으로 분리했습니다.
- 해당 계층에 stopwatch_task.c를 추가하여 스톱워치 모듈의 실행 흐름을 관리하도록 구성했습니다.

**2.ST-LINK 동작 검증**
- ST-LINK로 분 단위 COUNT에 breakpoint를 걸고 동작을 검증했습니다.

---

### v.2.2 UART_CMD 파서 모듈 추가 및 검증
**1. UART_CMD_PROCESS 파서 모듈 추가**
- UART의 ISR에서 UART_CMD_TASK로 전송한 1byte data를 모듈 내부 정적 배열에 저장 한 뒤
- 명령문의 끝 지점에서 문자열을 비교해 CMD_STATE를 변경하는 모듈을 추가했습니다.
- 시스템이 시작 될때 정적 배열로 데이터를 넣어 CMD_STATE의 상태가 변경되는 것을 확인하여 모듈의 검증을 완료 했습니다.

**2. UART_CMD_PROCESS 한계점**
- 현재 모듈의 구조는 UART_CMD_TASK가 명령 대상 채널을 미리 지정하고, 파서 모듈은 해당 채널의 명령어 문자열만 비교하는 방식입니다.
- UART의 ISR에서 전송되는 1byte data로는 문장이 완성 되기 전까지는 타겟을 지정하기 어렵다는 것을 파악했습니다.

**3. 향후 UART_CMD_PROCESS 리팩토링 계획**
- 향후 파서 모듈이 문자열 명령을 분석하여 target과 command를 포함한 결과를 반환하고
- UART_CMD_TASK는 해당 target을 기준으로 각 Task Queue에 명령을 전달하는 구조로 리팩토링할 계획입니다.
- 이를 통해 향후 UART_CMD로 제어할 디바이스를 추가하더라도 기존 로직에서 구조를 바꾸지 않고 확장이 가능 할 것입니다.
---
### v.2.3 UART_CMD_TASK 실행 모듈 추가 및 RX_ISR TO TASK 흐름 검증

**1. UART_driver UART_RX 통합 검증**
- 기존에 제작했던 UART_driver의 RX_ISR를 TASK와 Rtos_Queue로 연결했습니다.
- tera term에서 "SW_START" 명령어를 송신하고 ISR에서 UartRxQueueHandle를 통해 1BYTE DATA가 TASK로 전달 되는 것을 확인했습니다.
- 이를 통해 UART_RX_IT Rtos_queue UART_CMD_TASK UART_CMD_PARSER가 하나의 흐름으로 동작하는 것을 검증 했습니다.

**2. RTOS_Queue기반 UART_TASK 동작 검증**
- UART_CMD_TASK는 xQueueReceive의 portMAX_DELAY를 사용하여 UART_CMD가 RX될 때까지 TASK를 Blocked 상태로 대기하는 구조입니다.
- UART_RX_ISR에서 데이터가 전송되면 UART_CMD_TASK가 실행되어 CMD 파서를 동작 시킵니다.
- 문자열이 완성되고 명령이 테이블에 있다면 파서에서 파싱된 데이터와 타겟을 TASK로 전달하고,
- true를 반환해 타겟의 switch case문을 동작시킬 예정입니다.

**3. 문제 해결 과정**
- UART_RX_ISR과 TASK의 연결 흐름을 확인 할 때 ISR에 진입하지 않는 것을 확인했고, NVIC TABLE ENABLE을 통해 ISR의 진입을 확인했습니다.
- UART_RX_ISR 진입은 확인했으나 teraterm의 터미널로 data를 송신하면 보드가 뻗어버리는 문제가 발생했습니다
- HardFualt가 일어난 것으로 판단하고, RTOS_Queue의 생성 타이밍을 확인, 생성타이밍을 추가하여 Queue의 데이터 흐름을 검증 했습니다.

**4. RTOS_Queue적용을 통해 배운점**
- 기존에는 RTOS를 TASK를 실행하는 상위계층이라고 생각했습니다.
- 하지만 ISR에서 생성된 데이터를 TASK로 전달하고 파서에서 파싱된 데이터로 다른 TASK를 전달하는 구조를 생각하면서 단순 TASK의 실행 계층은 아니라는 점을 파악했습니다
- RTOS는 하드웨어 이벤트와 애플리케이션 로직을 연결하며 TASK실행을 주체하는 계층이라는 것 확인했습니다.

**5. 향후 계획**
- 현재는 UART RX ISR → `UART_CMD_TASK` → `uart_cmd_process()`까지의 데이터 흐름과 target 기준 switch-case 진입까지 검증했습니다.
- 아직 파싱된 command를 `STOPWATCH_TASK`로 전달하는 구조는 구현하지 않았습니다.
- Stop_watch_task로 전달된 명령이 stop_watch 모듈의 동작을 제어하는 것까지 데이터의 흐름을 이어볼 생각입니다. 

---
### v.2.4 UART_CMD_TASK to SW_TASK task간 Queue 통신과 UART_CMD기반 SW_MODULE 상태 제어 검증
**1. UART_CMD_TASK to SW_TASK 데이터 흐름 검증**
- Rtos Queue를 이용해 파싱된 cmd를 SW_TASK로 보내는 데이터의 흐름을 검증했습니다.
- SW_TASK는 파싱된 CMD를 받으면 SW_SET_CMD 통해 SW_MODULE 내부 SW_CMD의 상태를 전환 합니다.

**2. UART_CMD 기반 SW_MODULE 상태 제어 검증**
- 주기적으로 실행되는 SW_MODULE은 내부의 SW_CMD의 상태를 검사합니다.
- SW_CMD가 상태가 전환되어 있으면 SW_MODULE의 내부 상태를 전환하고 전환 된 상태로 동작합니다.
- Tera Term에서 SW_START, SW_PAUSE, SW_STOP 명령을 송신했을 때, Debugger를 통해 각 command가 SW_TASK로 전달되고 Stopwatch 상태 전환 로직에 반영되는 것을 확인했습니다.

**3. 발견한 문제점**
- 현재 TX와 UART_RX의 BUADRATE가 일치하지 않으면 UART_CMD_PARSER의 내부 정적배열에 쓰레기 값이 저장되는 것을 확인했습니다.
- 정적 배열의 buffer_overflow의 예외처리는 if(buffer_idx >= buffer_size)buffer_idx = 0;로 적용되어 있는 상태입니다.
- 현재 UART_CMD_PARSER내부의 정적배열에 쓰레기값이 들어올 때의 예외처리를 고민중입니다.

---

- 현재 servo_motor 모듈이 set_servo_motor_cmd로 명령과 value 받고 servo_motor_process를 실행해 CMD를 기반으로 동작하는 것을 검증했습니다.
- 로직 아날라이저를 이용해 정확한 PWM의 20ms 주기의 신호와 1ms / 1.5ms / 2ms High Pulse 신호를 측정하여 동작을 검증 했습니다.
- 현재 uint8 타입의 angle에 256이상의 값이 입력되었을 때 1byteoverflow가 발생하여 ccr에 에러값이 입력되는 것을 확인했습니다.
- 이를 해결하기 위해 파서에서 angle의 값이 180도 초과인 비정상적인 명령이 입력 되었을때 명령을 전송 하지 않는 예외처리를 할 예정입니다 
---
### v2.5 — Smart Blind FSM 구현 및 서보 연동 검증

**1. Smart Blind FSM 구현**
- 블라인드 상태를 BLIND_NONE, BLIND_OPEN, BLIND_HALF, BLIND_CLOSE로 정의
- 수신 명령(BLIND_CMD_OPEN / BLIND_CMD_HALF / BLIND_CMD_CLOSE)에 따라 상태를 전이하고, 각 상태에 대응하는 서보 각도(0° / 45° / 90°)를 Servo_Cmd_Packet에 담아 반환
- 현재 상태와 동일한 명령이 들어오면 상태를 바꾸지 않고 false를 반환하도록 처리해 불필요한 서보 명령 전송을 방지

**2. 검증**

- UART로 OPEN/HALF/CLOSE 명령을 전송해 Smart Blind Task → Servo Queue → Servo Task로 이어지는 흐름이 정상 동작하는지 확인
- 로직 아날라이저로 서보 PWM 출력을 측정해, 각 명령에 대응하는 각도(0° / 45° / 90°)로 정확히 구동되는지 검증

---

### v2.6 — LCD 출력

**1. LCD HD44780 라이브러리 구현**
- LCD1602의 드라이버인 HD44780의 데이터 시트의 초기화 시퀸스와 타이밍을 기반으로 한 디바이스 추상화 라이브러리를 작성
- 여러 핀으로 연결되어 있는 GPIO를 nibble로 관리
- us단위의 타이밍을 CORE M4의 DWT로 구현
- 다중 인스턴스를 계획했으나 현재 LCD의 GPIO의 사용을 봤을 때 불가능하다 판단, GPIO의 소모를 줄이기 위해 I2C 도입을 고려 중

**2. Diplay Task 추가**
- Stopwatch 시간과 Smart Blind 상태를 LCD에 출력하기 위해 Display Task를 추가
- Stopwatch/Smart Blind 각 모듈에서 Queue로 데이터를 전달받아 LCD에 반영하는 구조로 구성
 



