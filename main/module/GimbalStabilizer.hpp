#ifndef _GIMBAL_STABILIZER_HPP_
#define _GIMBAL_STABILIZER_HPP_

#include "../Wheelchair_Core.h"

/***
TODO : 서보 하드웨어 타이머 충돌
***/
#include <Servo.h> // https://github.com/arduino-libraries/Servo

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
		if (this->_xAxisServo.attach(gimbal_pin::X_AXIS_SERVO_OUTPUT) != INVALID_SERVO)
			goto THROW_INVALID_SERVO_EX;

		if (this->_yAxisServo.attach(gimbal_pin::Y_AXIS_SERVO_OUTPUT) != INVALID_SERVO)
			goto THROW_INVALID_SERVO_EX;

		return;

	THROW_INVALID_SERVO_EX:
		ERROR_LOG("Failed to attach Servo");
		while (1);
	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask()
	{
	}

private:
	/// <summary>
	/// x 및 y축에 대한 경사각 반환
	/// </summary>
	void GetDipAngleXY()
	{
		//TOOD : x및 y축에 대한 현재 경사각 반환
	}

private:
	Servo _xAxisServo; //x축에 대한 서보 모터 (roll)
	Servo _yAxisServo; //y축에 대한 서보 모터 (pitch)
};
#endif