#ifndef _GIMBAL_STABILIZER_HPP_
#define _GIMBAL_STABILIZER_HPP_

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

	void Init() const
	{

	}

	void RunTask(); //TODO : x, y에 대해 읽어서 서보 모터 제어 (Servo.h 사용)

private:

};
#endif