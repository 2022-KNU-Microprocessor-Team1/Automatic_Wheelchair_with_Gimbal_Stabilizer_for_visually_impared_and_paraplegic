#include "./Move.hpp"

MOVE move; //IR 통신 및 이동

//Move.hpp
extern uint8_t MAX_WHEEL_ROTATE_SPEED; //최대 바퀴 회전 속도

/// <summary>
/// 한 번 실행
/// </summary>
void setup()
{
#ifdef DEBUG_MODE
  Serial.begin(BITS_PER_SECONDS);
#endif

	MAX_WHEEL_ROTATE_SPEED = (MAX_PWM_VALUE / 2);
	move.Init();
}

/// <summary>
/// 반복 실행
/// </summary>
void loop()
{
	move.RunTask();
}
