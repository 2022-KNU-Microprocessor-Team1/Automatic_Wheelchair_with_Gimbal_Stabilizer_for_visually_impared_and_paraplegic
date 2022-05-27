#ifndef _COLLISION_ALERT_MANAGER_H_
#define _COLLISION_ALERT_MANAGER_H_

#define MIN_HCSR04_CM_RANGE 2 //������ �Ÿ� ���� �ּ� ���� ���� ���� (cm ����)
#define MAX_HCSR04_CM_RANGE 400 //������ �Ÿ� ���� �ִ� ���� ���� ���� (cm ����)

/// <summary>
/// �浹 ��� ���� �� ����
/// </summary>
namespace collision_alert_pin
{
	const int HCSR04_BACKWARD_ECHO_INPUT = 13; //�Ĺ� ��ֹ� ���� ������ ���� ���� ��
	const int HCSR04_FORWARD_ECHO_INPUT = 12; //���� ��ֹ� ���� ������ ���� ���� ��

	const int Gl5537_ANALOG_INPUT = 0; //���� ���� (ANALOG)
};

/// <summary>
/// ��ֹ����� cm ���� �Ÿ�
/// </summary>
struct DISTANCE_CM
{
	unsigned long _backwardCm; //�Ĺ� ��ֹ����� cm ���� �Ÿ�
	unsigned long _forwardCm; //���� ��ֹ����� cm ���� �Ÿ�
};

/// <summary>
/// �浹 ��� ������
/// </summary>
class COLLISION_ALERT_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void RunTask() const;

public:
	int MIN_GL5537_THRESHOLD = 60; //�ּ� ���� ���� ���� �Ӱ� ��
	int MAX_GL5537_THRESHOLD = 970; //�ִ� ���� ���� ���� �Ӱ� ��
	int COLLISION_ALERT_CM_THRESHOLD = (MIN_HCSR04_CM_RANGE + 20); //�浹 ��� �Ӱ� �� (cm ����)

private:
	unsigned char GetBrightnessFromGl5537() const;
	DISTANCE_CM GetDistanceCmFromHcsr04() const;

private:
	//��� �� SINGLETON���� ������, �Ҹ��� ����
	friend class SINGLETON;

	COLLISION_ALERT_MANAGER();
	~COLLISION_ALERT_MANAGER();
};
#endif