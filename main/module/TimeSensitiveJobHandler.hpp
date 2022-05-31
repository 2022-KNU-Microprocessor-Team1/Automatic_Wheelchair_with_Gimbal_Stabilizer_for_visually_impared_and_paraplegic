#ifndef _TIME_SENSITIVE_JOB_HANDLER_H_
#define _TIME_SENSITIVE_JOB_HANDLER_H_

#include "../Wheelchair_Core.h"

using TIME_SENSITIVE_JOB_ADDR_TYPE = void(*)(void); //Time Sensitive 작업

/// <summary>
/// Time Sensitive 작업 핸들러
/// </summary>
class TIME_SENSITIVE_JOB_HANDLER
{
public:
	/// <summary>
	/// Time Sensitive한 작업 수행
	/// </summary>
	/// <param name="timeSensitiveJobAddrType">Time Sensitive 작업</param>
	static inline void HandleTimeSensitiveJob(TIME_SENSITIVE_JOB_ADDR_TYPE timeSensitiveJobAddrType)
	{
		cli(); //인터럽트 비활성화
		timeSensitiveJobAddrType; //run
		sei(); //인터럽트 재활성화
	}

	/// <summary>
	/// Time Sensitive한 밀리초 단위 지연 수행
	/// </summary>
	/// <param name="milliseconds">밀리초 단위 시간</param>
	static inline void HandleTimeSensitiveDelay(unsigned long milliseconds)
	{
		cli(); //인터럽트 비활성화
		delay(milliseconds);
		sei(); //인터럽트 재활성화
	}

	/// <summary>
	/// Time Sensitive한  마이크로초 단위 지연 수행
	/// </summary>
	/// <param name="microseconds">마이크로초 단위 시간</param>
	static inline void HandleTimeSensitiveDelayMs(unsigned int microseconds)
	{
		cli(); //인터럽트 비활성화
		delayMicroseconds(microseconds);
		sei(); //인터럽트 재활성화
	}

private:
	/// <summary>
	/// TIME_SENSITIVE_JOB_HANDLER 생성자
	/// </summary>
	TIME_SENSITIVE_JOB_HANDLER()
	{
	}

	/// <summary>
	/// TIME_SENSITIVE_JOB_HANDLER 소멸자
	/// </summary>
	~TIME_SENSITIVE_JOB_HANDLER()
	{
	}
};
#endif