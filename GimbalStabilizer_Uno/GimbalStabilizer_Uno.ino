#include "./GimbalStabilizer.hpp"

GIMBAL_STABILIZER gimbalStabilizer; //수평 안정화 장치

// GimbalStabilizer.hpp
extern uint8_t INIT_SERVO_X_ANGLE; //x축에 대한 초기 서보 회전 각도
extern uint8_t INIT_SERVO_Y_ANGLE; //y축에 대한 초기 서보 회전 각도

extern uint16_t INIT_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 초기 x축에 대한 원시 값 (수평 기준)
extern uint16_t MIN_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최소 x축에 대한 원시 값
extern uint16_t MAX_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

extern uint16_t INIT_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 초기 y축에 대한 원시 값 (수평 기준)
extern uint16_t MIN_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최소 y축에 대한 원시 값
extern uint16_t MAX_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

/// <summary>
/// 한 번 실행
/// </summary>
void setup()
{
#ifdef DEBUG_MODE
  Serial.begin(BITS_PER_SECONDS);
#endif

	INIT_SERVO_X_ANGLE = 80;
	INIT_SERVO_Y_ANGLE = 97;

	INIT_STS90H1_X_RAW_VALUE = 496;
	MIN_STS90H1_X_RAW_VALUE = 45;
	MAX_STS90H1_X_RAW_VALUE = 942;

	INIT_STS90H1_Y_RAW_VALUE = 488;
	MIN_STS90H1_Y_RAW_VALUE = 37;
	MAX_STS90H1_Y_RAW_VALUE = 943;

	gimbalStabilizer.Init();
}

/// <summary>
/// 반복 실행
/// </summary>
void loop()
{
	gimbalStabilizer.RunTask();
}