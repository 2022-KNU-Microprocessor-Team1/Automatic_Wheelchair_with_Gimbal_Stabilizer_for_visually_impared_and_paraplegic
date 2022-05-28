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
	/// 
	/// </summary>
	WHEELCHAIR()
	{	
	}

	/// <summary>
	/// 
	/// </summary>
	~WHEELCHAIR()
	{
	}

	/// <summary>
	/// 
	/// </summary>
	void Init()
	{
		pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT1, INPUT);
		pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT2, INPUT);
		pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT1, INPUT);
		pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT2, INPUT);
		pinMode(collision_alert_pin::HCSR04_BACKWARD_ECHO_INPUT, INPUT);
		pinMode(collision_alert_pin::HCSR04_FORWARD_ECHO_INPUT, INPUT);

		this->_bodyMove.Init();
		this->_collisionAlert.Init();
		this->_gimbalStabilizer.Init();
	}

	/// <summary>
	/// 작업 수행
	/// </summary>
	void RunTask()
	{

	}

private:
	BODY_MOVE _bodyMove;
	GIMBAL_STABILIZER _gimbalStabilizer;
	COLLISION_ALERT _collisionAlert;
};
#endif
