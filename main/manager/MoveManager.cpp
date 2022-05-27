#include "../Wheelchair_Core.h"

/// <summary>
/// MOVE_MANAGER ������
/// </summary>
MOVE_MANAGER::MOVE_MANAGER()
{
	pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT1, INPUT);
	pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT2, INPUT);
	pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT1, INPUT);
	pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT2, INPUT);

	//TODO : ���ܼ� ��� �� �׽�Ʈ �� �ʱ�ȭ ����
}

/// <summary>
/// MOVE_MANAGER �Ҹ���
/// </summary>
MOVE_MANAGER::~MOVE_MANAGER()
{
}

/// <summary>
/// �̵� ���⿡ ���� ��ü�� �̵�
/// </summary>
/// <param name="moveDirection">�̵� ����</param>
void MOVE_MANAGER::MoveTo(MOVE_DIRECTION moveDirection) const
{
	//����ġ�� ���� ���� �� ��Ȱ��ȭ (�ܶ� ����)
	this->GetInstance().SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, LOW);
	this->GetInstance().SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, LOW);
	this->GetInstance().WriteShiftReg();

	int leftWheelRotateSpeed = 0; //���� ���� ȸ�� �ӵ�
	int rightWheelRotateSpeed = 0; //������ ���� ȸ�� �ӵ�

	switch (moveDirection) //�̵� ���⿡ ���� �� ������ �̵� �ӵ� �Ҵ�
	{
	case MOVE_DIRECTION::FORWARD:
	case MOVE_DIRECTION::BACKWARD:
		leftWheelRotateSpeed = rightWheelRotateSpeed = MAX_WHEEL_ROTATE_SPEED;
		break;

	case MOVE_DIRECTION::LEFT:
		rightWheelRotateSpeed = MAX_WHEEL_ROTATE_SPEED;
		break;

	case MOVE_DIRECTION::RIGHT:
		leftWheelRotateSpeed = MAX_WHEEL_ROTATE_SPEED;
		break;

	case MOVE_DIRECTION::LEFT_AND_FORWARD:
		leftWheelRotateSpeed = (MAX_WHEEL_ROTATE_SPEED / 2);
		rightWheelRotateSpeed = MAX_WHEEL_ROTATE_SPEED;
		break;

	case MOVE_DIRECTION::RIGHT_AND_FORWARD:
		leftWheelRotateSpeed = MAX_WHEEL_ROTATE_SPEED;
		rightWheelRotateSpeed = (MAX_WHEEL_ROTATE_SPEED / 2);
		break;

	case MOVE_DIRECTION::BRAKE:
		break;
	}

	switch (moveDirection) //�̵� ���⿡ ���� H-�긴�� ��� ���� ����
	{
	case MOVE_DIRECTION::FORWARD:
	case MOVE_DIRECTION::LEFT:
	case MOVE_DIRECTION::RIGHT:
	case MOVE_DIRECTION::LEFT_AND_FORWARD:
	case MOVE_DIRECTION::RIGHT_AND_FORWARD:
		//���� ���� ��� 1 Ȱ��ȭ, ��� 2 ��Ȱ��ȭ
		digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT1, HIGH);
		digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT2, LOW);
		digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT1, HIGH);
		digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT2, LOW);
		break;

	case MOVE_DIRECTION::BACKWARD:
		//���� ���� ��� 1 ��Ȱ��ȭ, ��� 2 Ȱ��ȭ
		digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT1, LOW);
		digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT2, HIGH);
		digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT1, LOW);
		digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT2, HIGH);
		break;

	case MOVE_DIRECTION::BRAKE:
		break;
	}

	//�� ������ ȸ�� �ӵ��� ���� ����
	this->GetInstance().SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, leftWheelRotateSpeed);
	this->GetInstance().SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, rightWheelRotateSpeed);
	this->GetInstance().WriteShiftReg();
}