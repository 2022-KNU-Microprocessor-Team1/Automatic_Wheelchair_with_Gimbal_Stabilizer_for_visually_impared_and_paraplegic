#ifndef _WHEELCHAIR_CORE_H_
#define _WHEELCHAIR_CORE_H_

#define _VAR_DUMP(name, value) Serial.println(String(name) + " : " +  String(value)); //시리얼 통신에 "name : value" 출력
#define VAR_DUMP(var) _VAR_DUMP(#var, (var))
#define ERROR_LOG(msg) _VAR_DUMP("Error", msg) //오류 로그 출력

#define LENGTH(array) ((sizeof(array)) / (sizeof(array[0])))

#define ARDUINO_RESOLUTION_IN_BITS 10 //아두이노의 비트 단위 해상도
#define MIN_ADC_VALUE 0 //최소 아날로그-디지털 신호 변환 (ADC) 값
#define MAX_ADC_VALUE (((1) << ARDUINO_RESOLUTION_IN_BITS) - 1) //최대 아날로그-디지털 신호 변환 (ADC) 값
#define MIN_PWM_VALUE 0 //최소 펄스 폭 변조 (PWM) 값
#define MAX_PWM_VALUE 255 //최대 펄스 폭 변조 (PWM) 값
#define BITS_PER_SECONDS 9600 //시리얼 통신 위한 초당 비트 단위 전송 속도

#define DEBUG_MODE
#ifndef DEBUG_MODE
#define VAR_DUMP(var) //do nothing
#define ERROR_LOG(msg) //do nothing
#endif

#include <stdint.h>
#include <Arduino.h> // https://www.circuitstoday.com/arduino-mega-pinout-schematics

#include "./template/Singleton.hpp"
#include "./Wheelchair_Pin.h"

#include "./module/CommonShiftRegPwm.hpp"
#include "./module/BodyMove.hpp"
#include "./module/GimbalStabilizer.hpp"
#include "./module/CollisionAlert.hpp"
#include "./Wheelchair.hpp"
#endif