#ifndef _GIMBAL_STABILIZER_PIN_H_
#define _GIMBAL_STABILIZER_PIN_H_

/// <summary>
/// 수평 유지 장치에 대한 핀 정의
/// </summary>
namespace gimbal_pin
{
	const int X_AXIS_SERVO_OUTPUT = 9; //x축에 대한 서보 모터 (PWM)
	const int Y_AXIS_SERVO_OUTPUT = 10; //y축에 대한 서보 모터 (PWM)

	const int X_AXIS_GIMBAL_INPUT = A1; //x축에 대한 기울기 센서
	const int Y_AXIS_GIMBAL_INPUT = A2; //y축에 대한 기울기 센서
}
#endif