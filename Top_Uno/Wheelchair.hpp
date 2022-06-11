#ifndef _WHEELCHAIR_HPP_
#define _WHEELCHAIR_HPP_

#include "./Wheelchair_Core.h"

/// <summary>
/// 휠체어 제어
/// </summary>
class WHEELCHAIR
{
public:
	/// <summary>
	/// WHEELCHAIR 생성자
	/// </summary>
	WHEELCHAIR()
	{	
	}

	/// <summary>
	/// WHEELCHAIR 소멸자
	/// </summary>
	~WHEELCHAIR()
	{
	}

	/// <summary>
	/// 초기화 작업 수행
	/// </summary>
	void Init()
	{
		//this->_collisionAlert.Init();
		this->_gimbalStabilizer.Init();
	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask()
	{
		//this->_collisionAlert.RunTask();
		this->_gimbalStabilizer.RunTask();
	}

private:
	GIMBAL_STABILIZER _gimbalStabilizer; //수평 안정화 장치
	COLLISION_ALERT _collisionAlert; //충돌 경고
};
#endif