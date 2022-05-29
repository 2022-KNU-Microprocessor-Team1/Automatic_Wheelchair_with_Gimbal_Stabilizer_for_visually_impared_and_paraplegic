#include "./Wheelchair_Core.h"

/***
	Mega 2560 사용되는 하드웨어 타이머 : TIMER.md
***/

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

}
