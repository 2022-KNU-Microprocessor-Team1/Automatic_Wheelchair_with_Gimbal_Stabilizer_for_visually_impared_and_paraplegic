#include "./Wheelchair_Core.h"

// Move.hpp
extern uint8_t MAX_WHEEL_ROTATE_SPEED; //최대 바퀴 회전 속도

// CollisionAlert.hpp
extern int MIN_GL5537_THRESHOLD; //최소 조도 센서 측정 임계 값
extern int MAX_GL5537_THRESHOLD; //최대 조도 센서 측정 임계 값
extern unsigned long COLLISION_ALERT_CM_THRESHOLD; //충돌 경고 임계 값 (cm 단위)

// GimbalStabilizer.hpp
extern uint8_t INIT_SERVO_X_ANGLE;
extern uint8_t INIT_SERVO_Y_ANGLE;

extern uint16_t INIT_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 초기 x축에 대한 원시 값 (수평 기준)
extern uint16_t MIN_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최소 x축에 대한 원시 값
extern uint16_t MAX_STS90H1_X_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

extern uint16_t INIT_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 초기 y축에 대한 원시 값 (수평 기준)
extern uint16_t MIN_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최소 y축에 대한 원시 값
extern uint16_t MAX_STS90H1_Y_RAW_VALUE; //2축 기울기 센서 (수평 고정형)의 최대 y축에 대한 원시 값

WHEELCHAIR wheelchair;

/// <summary>
/// 한 번 실행
/// </summary>
void setup()
{
#ifdef DEBUG_MODE
  Serial.begin(BITS_PER_SECONDS);
#endif

  wheelchair.Init();
}

/// <summary>
/// 반복 실행
/// </summary>
void loop()
{
	wheelchair.RunTask();
}
