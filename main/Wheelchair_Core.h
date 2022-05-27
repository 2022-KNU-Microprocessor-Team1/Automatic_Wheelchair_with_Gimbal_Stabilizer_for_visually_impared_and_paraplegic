#ifndef _WHEELCHAIR_CORE_H_
#define _WHEELCHAIR_CORE_H_

#define _VAR_DUMP(name, value) Serial.println(String(name) + " : " +  String(value)); //�ø��� ��ſ� "name : value" ���
#define VAR_DUMP(var) _VAR_DUMP(#var, (var))
#define ERROR_LOG(msg) _VAR_DUMP("Error", msg) //���� �α� ���

#define LENGTH(array) ((sizeof(array)) / (sizeof(array[0])))

#define ARDUINO_RESOLUTION_IN_BITS 10 //�Ƶ��̳��� ��Ʈ ���� �ػ�
#define MIN_ADC_VALUE 0 //�ּ� �Ƴ��α�-������ ��ȣ ��ȯ (ADC) ��
#define MAX_ADC_VALUE (((1) << ARDUINO_RESOLUTION_IN_BITS) - 1) //�ִ� �Ƴ��α�-������ ��ȣ ��ȯ (ADC) ��
#define MIN_PWM_VALUE 0 //�ּ� �޽� �� ���� (PWM) ��
#define MAX_PWM_VALUE 255 //�ִ� �޽� �� ���� (PWM) ��
#define BITS_PER_SECONDS 9600 //�ø��� ��� ���� �ʴ� ��Ʈ ���� ���� �ӵ�

#define DEBUG_MODE
#ifndef DEBUG_MODE
#define VAR_DUMP(var) //do nothing
#define ERROR_LOG(msg) //do nothing
#endif

#include <Arduino.h> // https://www.circuitstoday.com/arduino-mega-pinout-schematics
#include <IRremote.h> // https://arduino-irremote.github.io/Arduino-IRremote/index.html
#include <TimerThree.h> // https://www.pjrc.com/teensy/td_libs_TimerOne.html
#include <ShiftRegisterPWM.h> // https://timodenk.com/blog/shiftregister-pwm-library/
#include <Servo.h>

#include "./template/Singleton.hpp"
#include "./common/CommonShiftRegPwm.h"

#include "./manager/MoveManager.h"
#include "./manager/GimbalStabilityManager.h"
#include "./manager/CollisionAlertManager.h"

#include "./Wheelchair.h"
#endif