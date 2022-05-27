#include "./Wheelchair_Core.h"

#ifndef DEBUG_MODE
#define VAR_DUMP(var) //do nothing
#define ERROR_LOG(msg) //do nothing
#endif

WHEELCHAIR wheelchair;

/// <summary>
/// 한 번 실행
/// </summary>
void setup()
{
#ifdef DEBUG_MODE
  Serial.begin(BITS_PER_SECONDS);
#endif

}

/// <summary>
/// 반복 실행
/// </summary>
void loop()
{

}
