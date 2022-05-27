﻿#ifndef _COLLISION_ALERT_MANAGER_H_
#define _COLLISION_ALERT_MANAGER_H_

#define MIN_HCSR04_CM_RANGE 2 //초음파 거리 센서 최소 측정 가능 범위 (cm 단위)
#define MAX_HCSR04_CM_RANGE 400 //초음파 거리 센서 최대 측정 가능 범위 (cm 단위)

/// <summary>
/// 충돌 경고 위한 핀 정의
/// </summary>
namespace collision_alert_pin
{
	const int HCSR04_BACKWARD_ECHO_INPUT = 13; //후방 장애물 감지 초음파 센서 에코 핀
	const int HCSR04_FORWARD_ECHO_INPUT = 12; //전방 장애물 감지 초음파 센서 에코 핀

	const int Gl5537_ANALOG_INPUT = 0; //조도 센서 (ANALOG)
};

/// <summary>
/// 장애물과의 cm 단위 거리
/// </summary>
struct DISTANCE_CM
{
	unsigned long _backwardCm; //후방 장애물과의 cm 단위 거리
	unsigned long _forwardCm; //전방 장애물과의 cm 단위 거리
};

/// <summary>
/// 충돌 경고 관리자
/// </summary>
class COLLISION_ALERT_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void RunTask() const;

public:
	int MIN_GL5537_THRESHOLD = 60; //최소 조도 센서 측정 임계 값
	int MAX_GL5537_THRESHOLD = 970; //최대 조도 센서 측정 임계 값
	int COLLISION_ALERT_CM_THRESHOLD = (MIN_HCSR04_CM_RANGE + 20); //충돌 경고 임계 값 (cm 단위)

private:
	unsigned char GetBrightnessFromGl5537() const;
	DISTANCE_CM GetDistanceCmFromHcsr04() const;

private:
	//상속 시 SINGLETON에서 생성자, 소멸자 접근
	friend class SINGLETON;

	COLLISION_ALERT_MANAGER();
	~COLLISION_ALERT_MANAGER();
};
#endif