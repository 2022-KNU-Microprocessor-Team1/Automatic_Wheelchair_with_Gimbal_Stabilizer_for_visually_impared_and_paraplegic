#ifndef _GIMBAL_STABILITY_MANAGER_H_
#define _GIMBAL_STABILITY_MANAGER_H_

/// <summary>
/// ���� ���� ��ġ�� ���� �� ����
/// </summary>
namespace gimbal_pin
{
	const int X_AXIS_SERVO_OUTPUT = 6; //x�࿡ ���� ���� ���� (PWM)
	const int Y_AXIS_SERVO_OUTPUT = 5; //y�࿡ ���� ���� ���� (PWM)

	//TODO : ���� ���� �Ƴ��α� �Է� Ȥ�� ������ �Է� �׽�Ʈ
	const int X_AXIS_GIMBAL_INPUT; //x�࿡ ���� ���� ����
	const int Y_AXIS_GIMBAL_INPUT; //y�࿡ ���� ���� ����
};

/// <summary>
/// ���� ���� ������
/// </summary>
class GIMBAL_STABILITY_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void RunTask(); //TODO : x, y�� ���� �о ���� ���� ���� (Servo.h ���)

private:
	//��� �� SINGLETON���� ������, �Ҹ��� ����
	friend class SINGLETON;

	GIMBAL_STABILITY_MANAGER();
	~GIMBAL_STABILITY_MANAGER();
};
#endif