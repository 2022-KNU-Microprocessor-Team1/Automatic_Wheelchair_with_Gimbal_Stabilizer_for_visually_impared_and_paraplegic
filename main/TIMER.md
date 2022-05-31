## < Arduino Mega 2560 하드웨어 타이머 >

---

| Timer | Control Pin | Usage |
|:---|:---|:---|
| Timer 0 (8bit) | 4, 13 | millis(), micros(), delay() |
| Timer 1 (16bit) | 11, 12 | 서보 모터 제어 (Servo-avr-custom) |
| Timer 2 (8bit) | 9, 10 | tone() | 
| Timer 3 (16bit) | 2, 3, 5 | ShiftRegPWM 출력 (TimerThree-custom) |
| Timer 4 (16bit) | 6, 7, 8 | 적외선 통신 (IRremote-custom) |
| Timer 5 (16bit) | 44, 45, 46 | - |

- https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072
