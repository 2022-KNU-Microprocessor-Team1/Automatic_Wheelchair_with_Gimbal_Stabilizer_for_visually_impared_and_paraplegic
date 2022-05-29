#ifndef _GIMBAL_STABILIZER_HPP_
#define _GIMBAL_STABILIZER_HPP_

#include "../Wheelchair_Core.h"
//#include <Servo.h>
//TODO : 서보 라이브러리 다중 정의 오류

/// <summary>
/// 수평 유지 장치
/// </summary>
class GIMBAL_STABILIZER
{
public:
	/// <summary>
	/// GIMBAL_STABILIZER 생성자
	/// </summary>
	GIMBAL_STABILIZER()
	{
		//TODO : 기울기 센서 핀 테스트 후 초기화 수행
	}

	/// <summary>
	/// GIMBAL_STABILIZER 소멸자
	/// </summary>
	~GIMBAL_STABILIZER()
	{
	}

	/// <summary>
	/// 초기화
	/// </summary>
	void Init() const
	{

	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask() //TODO : x, y에 대해 읽어서 서보 모터 제어 (Servo.h 사용)
	{
	}

private:

};
#endif