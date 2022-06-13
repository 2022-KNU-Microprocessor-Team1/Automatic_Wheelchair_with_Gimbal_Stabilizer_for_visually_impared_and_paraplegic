#ifndef _COLLISION_ALERT_HPP_
#define _COLLISION_ALERT_HPP_

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
#include <Arduino.h> // https://github.com/arduino/ArduinoCore-avr

#pragma message("--- Compile Target Architecture ---")
#if defined(ARDUINO_ARCH_AVR)
#pragma message("ARDUINO_ARCH_AVR")
#elif defined(ARDUINO_ARCH_SAM)
#pragma message("ARDUINO_ARCH_SAM")
#elif defined(ARDUINO_ARCH_SAMD)
#pragma message("ARDUINO_ARCH_SAMD")
#elif defined(ARDUINO_ARCH_STM32F4)
#pragma message("ARDUINO_ARCH_STM32F4")
#elif defined(ARDUINO_ARCH_NRF52)
#pragma message("ARDUINO_ARCH_NRF52")
#elif defined(ARDUINO_ARCH_MEGAAVR)
#pragma message("ARDUINO_ARCH_MEGAAVR")
#elif defined(ARDUINO_ARCH_MBED)
#pragma message("ARDUINO_ARCH_MBED")
#else
#error "Unknown Architecture"
#endif

//#include "./Singleton.hpp"
#include "./CollisionAlert_Pin.h"
#include "./Pitches.h"
#include "./TimeSensitiveJobHandler.hpp"

#define MIN_HCSR04_CM_RANGE 2 //초음파 거리 센서 최소 측정 가능 범위 (cm 단위)
#define MAX_HCSR04_CM_RANGE 400 //초음파 거리 센서 최대 측정 가능 범위 (cm 단위)
static int MIN_GL5537_THRESHOLD = 60; //최소 조도 센서 측정 임계 값
static int MAX_GL5537_THRESHOLD = 970; //최대 조도 센서 측정 임계 값
static unsigned long COLLISION_ALERT_CM_THRESHOLD = (MIN_HCSR04_CM_RANGE + 20); //충돌 경고 임계 값 (cm 단위)

/// <summary>
/// 충돌 경고
/// </summary>
class COLLISION_ALERT
{
public:
	/// <summary>
	/// COLLISION_ALERT 생성자
	/// </summary>
	COLLISION_ALERT()
	{
	}

	/// <summary>
	/// COLLISION_ALERT 소멸자
	/// </summary>
	~COLLISION_ALERT()
	{
	}

	/// <summary>
	/// 초기화 작업 수행
	/// </summary>
	void Init() const
	{
		pinMode(collision_alert_pin::HCSR04_BACKWARD_ECHO_INPUT, INPUT);
		pinMode(collision_alert_pin::HCSR04_FORWARD_ECHO_INPUT, INPUT);
		pinMode(collision_alert_pin::HCSR04_FORWARD_TRIG_OUTPUT, OUTPUT);
		pinMode(collision_alert_pin::HCSR04_BACKWARD_TRIG_OUTPUT, OUTPUT);

		pinMode(collision_alert_pin::PIEZO_OUTPUT, OUTPUT);
		pinMode(collision_alert_pin::LED_OUTPUT, OUTPUT);
	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask() const
	{
		uint8_t brightness = this->GetBrightnessFromGL5537(); //주변 밝기
		unsigned long forwardDistanceCm = this->GetDistanceCmFromHcsr04(
			collision_alert_pin::HCSR04_FORWARD_TRIG_OUTPUT,
			collision_alert_pin::HCSR04_FORWARD_ECHO_INPUT); //전방 장애물과의 cm단위 거리
		unsigned long backwardDistanceCm = this->GetDistanceCmFromHcsr04(
			collision_alert_pin::HCSR04_BACKWARD_TRIG_OUTPUT,
			collision_alert_pin::HCSR04_BACKWARD_ECHO_INPUT); //후방 장애물과의 cm단위 거리

		VAR_DUMP(brightness);
		VAR_DUMP(forwardDistanceCm);
		VAR_DUMP(backwardDistanceCm);

		if (forwardDistanceCm <= COLLISION_ALERT_CM_THRESHOLD ||
			backwardDistanceCm <= COLLISION_ALERT_CM_THRESHOLD) //전방 혹은 후방 장애물과의 cm단위 거리가 임계 값 이하일 경우
		{
			analogWrite(collision_alert_pin::LED_OUTPUT,
				map(brightness,
					MIN_PWM_VALUE, MAX_PWM_VALUE,
					MAX_PWM_VALUE, MIN_PWM_VALUE)); //주변이 밝을 경우 최소 밝기 출력, 어두울 경우 최대 밝기 출력
			tone(collision_alert_pin::PIEZO_OUTPUT, NOTE_C6);
		}
		else //인접 한 장애물이 존재하지 않을 경우
		{
			analogWrite(collision_alert_pin::LED_OUTPUT, MIN_PWM_VALUE);
			noTone(collision_alert_pin::PIEZO_OUTPUT);
		}
	}

private:
	/// <summary>
	/// GL5537 조도 센서 (CdS Photoresistor)의 측정 값으로부터 변환 된 펄스 폭 변조 (PWM) 값 범위 내의 밝기 반환
	/// </summary>
	/// <returns>펄스 폭 변조 (PWM) 값 범위 내의 밝기</returns>
	uint8_t GetBrightnessFromGL5537() const
	{
		int retVal = analogRead(collision_alert_pin::GL5537_ANALOG_INPUT); //조도 센서 측정 값

		retVal = map(retVal,
			MIN_GL5537_THRESHOLD, MAX_GL5537_THRESHOLD,
			MIN_PWM_VALUE, MAX_PWM_VALUE); //임계 값 범위 내의 측정 값을 펄스 폭 변조 (PWM) 값 범위 내의 값으로 선형 사상

		return constrain(retVal,
			MIN_PWM_VALUE, MAX_PWM_VALUE);
	}

	/// <summary>
	/// HC-SR04 초음파 센서로부터 물체와의 cm 단위 거리 반환
	/// </summary>
	/// <param name="HCSR04_TRIG_OUTPUT">HC-SR04 초음파 센서 트리거 출력 핀</param>
	/// <param name="HCSR04_ECHO_INPUT">HC-SR04 에코 입력 핀</param>
	/// <returns>물체와의 cm 단위 거리</returns>
	unsigned long GetDistanceCmFromHcsr04(const int HCSR04_TRIG_OUTPUT, const int HCSR04_ECHO_INPUT) const
	{
		// https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
		// https://www.arduino.cc/reference/ko/language/functions/advanced-io/pulsein/
		//10마이크로초 이상 길이 (HIGH에 대한)의 펄스를 트리거 핀에 주어 작동 시작

		digitalWrite(HCSR04_TRIG_OUTPUT, LOW);
		TIME_SENSITIVE_JOB_HANDLER::HandleNonBlockingInterruptDelayMs(5);
		digitalWrite(HCSR04_TRIG_OUTPUT, HIGH);
		TIME_SENSITIVE_JOB_HANDLER::HandleNonBlockingInterruptDelayMs(10);
		digitalWrite(HCSR04_TRIG_OUTPUT, LOW);

		unsigned long durationMs =
			pulseIn(HCSR04_ECHO_INPUT, HIGH); //HIGH 신호가 ECHO에 수신 될 때까지 측정 된 마이크로초 단위 시간

		/***
			- 20도의 공기 중 음속 : 343m/s (0.034cm/µs)
			- 거리 = 시간 * 속도
			- 물체와의 거리 (초음파가 물체에 닿아 반사되어 수신 되는데 걸린 시간 측정) = (시간 / 2) * 속도

			---

			물체와의 거리 = (시간 * 0.034) / 2
		***/

		return ((durationMs * 0.034) / 2); //물체와의 cm 단위 거리
	}
};
#endif