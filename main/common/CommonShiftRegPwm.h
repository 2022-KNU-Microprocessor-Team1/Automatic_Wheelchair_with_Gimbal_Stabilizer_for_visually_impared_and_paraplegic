#ifndef _COMMON_SHIFT_REG_PWM_H_
#define _COMMON_SHIFT_REG_PWM_H_

#define NUM_OF_SHIFT_REG 1 //����Ʈ �������� ����
#define SHIFT_REG_PWM_RESOLUTION (MAX_PWM_VALUE) //����Ʈ �������� PWM ��� ���� �ػ� (1 ~ 255)

/// <summary>
/// �̵� �������� �� ����
/// </summary>
namespace shift_reg_pin
{
	/***
		ShiftRegister-PWM-Library�� �⺻������ ������, LATCH, Ŭ�Ͽ� ����
		���������� 2, 4, 3�� �� ���
	***/

	const int HC595_DATA_OUTPUT = 2; //����Ʈ �������� ������ ��
	const int HC595_RCLK_OUTPUT = 4; //����Ʈ �������� ��� �������� Ŭ�� (LATCH)
	const int HC595_SRCLK_OUTPUT = 3; //����Ʈ �������� Ŭ��

	/***
		ShiftRegister-PWM-Library�� ��� ���� �������� �Ҵ�Ǿ� �����Ƿ�,
		0�� ��� �� ���� => 7�� ��� �� �Ҵ����� �������� �Ҵ� �� ��
	***/

	/// <summary>
	/// ����Ʈ ���������� ��¿� ���� �浹 ���� �˸� �� ����
	/// </summary>
	namespace inner_collison_alert_pin
	{
		const char HCSR04_BACKWARD_TRIG_OUTPUT = 7; //�Ĺ� ��ֹ� ���� ������ ���� Ʈ���� �� (PWM)
		const char HCSR04_FORWARD_TRIG_OUTPUT = 6; //���� ��ֹ� ���� ������ ���� Ʈ���� �� (PWM)

		const char PIEZO_OUTPUT = 3; //�浹 ��� �ǿ��� ���� (PWM)
		const char LED_OUTPUT = 2; //�浹 ��� LED (PWM)
	};

	/// <summary>
	/// ����Ʈ ���������� ��¿� ���� ���� �� ����
	/// </summary>
	namespace inner_wheel_pin
	{
		const char H_BRIDGE_RIGHT_EN_OUTPUT = 5; //H-�긴�� ������ ���� �ӵ� ������ ���� 1,2 Ȱ��ȭ �� (PWM)
		const char H_BRIDGE_LEFT_EN_OUTPUT = 4; //H-�긴�� ���� ���� �ӵ� ������ ���� 3,4 Ȱ��ȭ �� (PWM)
	}
};

/// <summary>
/// ���� ����Ʈ �������� PWM ���
/// </summary>
class COMMON_SHIFT_REG_PWM : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void ClearPwmData();
	void SetPwmData(char, unsigned char);
	void WriteShiftReg() const;

private:
	unsigned char _pwmData[8]; //����Ʈ �������� ��� �ɿ� ��� �� PWM ������ (index : shift_reg_pin�� ����)
	class ShiftRegisterPWM _shiftRegPwm;

private:
	//��� �� SINGLETON���� ������, �Ҹ��� ����
	friend class SINGLETON;

	COMMON_SHIFT_REG_PWM();
	~COMMON_SHIFT_REG_PWM();
};
#endif