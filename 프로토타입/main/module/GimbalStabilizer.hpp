#ifndef _GIMBAL_STABILIZER_HPP_
#define _GIMBAL_STABILIZER_HPP_

#include "../Wheelchair_Core.h"
#include <Servo-avr-custom.h> // https://github.com/arduino-libraries/Servo

static uint8_t INIT_SERVO_X_ANGLE = 80;
static uint8_t INIT_SERVO_Y_ANGLE = 97;

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

	Servo _xAxisServo; //x축에 대한 서보 모터 (roll)
	Servo _yAxisServo; //y축에 대한 서보 모터 (pitch)
};
#endif