#ifndef _GIMBAL_STABILITY_MANAGER_H_
#define _GIMBAL_STABILITY_MANAGER_H_

/// <summary>
/// 수평 유지 장치에 대한 핀 정의
/// </summary>
namespace gimbal_pin
{
	const int X_AXIS_SERVO_OUTPUT = 6; //x축에 대한 서보 모터 (PWM)
	const int Y_AXIS_SERVO_OUTPUT = 5; //y축에 대한 서보 모터 (PWM)

	//TODO : 기울기 센서 아날로그 입력 혹은 디지털 입력 테스트
	const int X_AXIS_GIMBAL_INPUT; //x축에 대한 기울기 센서
	const int Y_AXIS_GIMBAL_INPUT; //y축에 대한 기울기 센서
};

/// <summary>
/// 수평 유지 관리자
/// </summary>
class GIMBAL_STABILITY_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void RunTask(); //TODO : x, y에 대해 읽어서 서보 모터 제어 (Servo.h 사용)

private:
	//상속 시 SINGLETON에서 생성자, 소멸자 접근
	friend class SINGLETON;

	GIMBAL_STABILITY_MANAGER();
	~GIMBAL_STABILITY_MANAGER();
};
#endif