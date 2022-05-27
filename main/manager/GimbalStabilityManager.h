#ifndef _GIMBAL_STABILITY_MANAGER_H_
#define _GIMBAL_STABILITY_MANAGER_H_

/// <summary>
/// 수평 유지 관리자
/// </summary>
class GIMBAL_STABILITY_MANAGER
{
public:
	void RunTask(); //TODO : x, y에 대해 읽어서 서보 모터 제어 (Servo.h 사용)

private:
	GIMBAL_STABILITY_MANAGER();
	~GIMBAL_STABILITY_MANAGER();
};
#endif