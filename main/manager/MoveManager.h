#ifndef _MOVE_MANAGER_H_
#define _MOVE_MANAGER_H_

#define MAX_WHEEL_ROTATE_SPEED (MAX_PWM_VALUE - 155) //�ִ� ���� ȸ�� �ӵ�

/// <summary>
/// ���ܼ� ��� �� ����
/// </summary>
namespace ir_comm_pin
{
	//TODO : ������ ��ư �Է� �� �̵�
	const int IR_INPUT;

};

/// <summary>
/// ������ ���� �� ����
/// </summary>
namespace wheel_pin
{
	const int H_BRIDGE_LEFT_INPUT1 = 11; //H-�긴�� ���� ���� �Է� �� 1
	const int H_BRIDGE_LEFT_INPUT2 = 10; //H-�긴�� ���� ���� �Է� �� 2

	const int H_BRIDGE_RIGHT_INPUT1 = 9; //H-�긴�� ������ ���� �Է� �� 1
	const int H_BRIDGE_RIGHT_INPUT2 = 8; //H-�긴�� ������ ���� �Է� �� 2
};

/// <summary>
/// �̵� ����
/// </summary>
enum class MOVE_DIRECTION : const int
{
	FORWARD = 0, //����
	BACKWARD, //����
	LEFT, //���ڸ� ��ȸ��
	RIGHT, //���ڸ� ��ȸ��
	LEFT_AND_FORWARD, //��ȸ�� �� ����
	RIGHT_AND_FORWARD, //��ȸ�� �� ����
	BRAKE //����
};

/// <summary>
/// �̵� ������
/// </summary>
class MOVE_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void MoveTo(MOVE_DIRECTION) const;

private:
	//��� �� SINGLETON���� ������, �Ҹ��� ����
	friend class SINGLETON;

	MOVE_MANAGER();
	~MOVE_MANAGER();
};
#endif