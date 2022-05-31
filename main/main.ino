#include "./Wheelchair_Core.h"

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
