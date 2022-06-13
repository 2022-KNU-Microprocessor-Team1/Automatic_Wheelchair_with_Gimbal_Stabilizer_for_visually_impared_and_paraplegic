#ifndef _GIMBAL_STABILIZER_HPP_
#define _GIMBAL_STABILIZER_HPP_

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
#include "./GimbalStabilizer_Pin.h"
#include "./TimeSensitiveJobHandler.hpp"

#include <Servo.h> // https://github.com/arduino-libraries/Servo

static uint8_t INIT_SERVO_X_ANGLE = 80; //x축에 대한 초기 서보 회전 각도
static uint8_t INIT_SERVO_Y_ANGLE = 97; //y축에 대한 초기 서보 회전 각도

static uint16_t INIT_STS90H1_X_RAW_VALUE = 496; //2축 기울기 센서 (수평 고정형)의 초기 x축에 대한 원시 값 (수평 기준)
static uint16_t MIN_STS90H1_X_RAW_VALUE = 45; //2축 기울기 센서 (수평 고정형)의 최소 x축에 대한 원시 값
static uint16_t MAX_STS90H1_X_RAW_VALUE = 942; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

static uint16_t INIT_STS90H1_Y_RAW_VALUE = 488; //2축 기울기 센서 (수평 고정형)의 초기 y축에 대한 원시 값 (수평 기준)
static uint16_t MIN_STS90H1_Y_RAW_VALUE = 37; //2축 기울기 센서 (수평 고정형)의 최소 y축에 대한 원시 값
static uint16_t MAX_STS90H1_Y_RAW_VALUE = 943; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

/// <summary>
/// 수평 유지 장치
/// </summary>
class GIMBAL_STABILIZER
{
public:
	/// <summary>
	/// GIMBAL_STABILIZER 생성자
	/// </summary>
	GIMBAL_STABILIZER()
	{
	}

	/// <summary>
	/// GIMBAL_STABILIZER 소멸자
	/// </summary>
	~GIMBAL_STABILIZER()
	{
	}

	/// <summary>
	/// 초기화 작업 수행
	/// </summary>
	void Init()
	{
		if (this->_xAxisServo.attach(gimbal_pin::X_AXIS_SERVO_OUTPUT) == INVALID_SERVO ||
			this->_yAxisServo.attach(gimbal_pin::Y_AXIS_SERVO_OUTPUT) == INVALID_SERVO)
		{
			ERROR_LOG("Failed to attach Servo");
			while (1);
		}

		this->_xAxisServo.write(INIT_SERVO_X_ANGLE);
		this->_yAxisServo.write(INIT_SERVO_Y_ANGLE);
		return;
	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask()
	{
		this->GimbalStabilize(this->GetDipAngleXY());
		TIME_SENSITIVE_JOB_HANDLER::HandleNonBlockingInterruptDelay(100);
	}

private:
	/// <summary>
	/// x 및 y축에 대한 각도
	/// </summary>
	struct ANGLE_XY
	{
		int8_t _xAngle;
		int8_t _yAngle;
	};

	/// <summary>
	/// x 및 y축에 대한 경사각으로 수평 조절
	/// </summary>
	/// <param name="dipAngleXY">x 및 y축에 대한 경사각</param>
	void GimbalStabilize(const ANGLE_XY& dipAngleXY)
	{
		this->_xAxisServo.write(INIT_SERVO_X_ANGLE + dipAngleXY._xAngle);
		this->_yAxisServo.write(INIT_SERVO_Y_ANGLE + dipAngleXY._yAngle);
		TIME_SENSITIVE_JOB_HANDLER::HandleNonBlockingInterruptDelay(100);
	}
	
	/// <summary>
	///  x 및 y축에 대한 경사각 반환
	/// </summary>
	/// <returns>x 및 y축에 대한 경사각</returns>
	ANGLE_XY GetDipAngleXY()
	{
		ANGLE_XY retVal = { 0, };

		uint16_t xRawValue = analogRead(gimbal_pin::X_AXIS_GIMBAL_INPUT);
		uint16_t yRawValue = analogRead(gimbal_pin::Y_AXIS_GIMBAL_INPUT);

		VAR_DUMP(xRawValue);
		VAR_DUMP(yRawValue);

		retVal._xAngle = map(xRawValue,
			MIN_STS90H1_X_RAW_VALUE, MAX_STS90H1_X_RAW_VALUE,
			-90, 90);
		retVal._yAngle = map(yRawValue,
			MIN_STS90H1_Y_RAW_VALUE, MAX_STS90H1_Y_RAW_VALUE,
			-90, 90);
		retVal._xAngle = constrain(retVal._xAngle, -90, 90);
		retVal._yAngle = constrain(retVal._yAngle, -90, 90);

		VAR_DUMP(retVal._xAngle);
		VAR_DUMP(retVal._yAngle);
		return retVal;
	}

private:
	Servo _xAxisServo; //x축에 대한 서보 모터 (roll)
	Servo _yAxisServo; //y축에 대한 서보 모터 (pitch)
};
#endif