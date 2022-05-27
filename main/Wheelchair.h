#ifndef _WHEELCHAIR_H_
#define _WHEELCHAIR_H_

/// <summary>
/// 휠체어 제어
/// </summary>
class WHEELCHAIR
{
public:
	WHEELCHAIR();
	~WHEELCHAIR();

	void RunTask();

private:
	class MOVE_MANAGER _moveManager;
	class GIMBAL_STABILITY_MANAGER _gimbalStabilityManager;
	class COLLISION_ALERT_MANAGER _collisionAlertManager;
};
#endif
