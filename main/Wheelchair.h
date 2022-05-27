#ifndef _WHEELCHAIR_H_
#define _WHEELCHAIR_H_

/// <summary>
/// ��ü�� ����
/// </summary>
class WHEELCHAIR
{
public:
	void RunTask();

private:
	class MOVE_MANAGER _moveManager;
	class GIMBAL_STABILITY_MANAGER _gimbalStabilityManager;
	class COLLISION_ALERT_MANAGER _collisionAlertManager;

	WHEELCHAIR();
	~WHEELCHAIR();
};
#endif