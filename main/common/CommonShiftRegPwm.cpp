#include "../Wheelchair_Core.h"

/// <summary>
/// COMMON_SHIFT_REG_PWM ������
/// </summary>
COMMON_SHIFT_REG_PWM::COMMON_SHIFT_REG_PWM()
{
	//����Ʈ �������� �� �ʱ�ȭ
	pinMode(shift_reg_pin::HC595_DATA_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::HC595_RCLK_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::HC595_SRCLK_OUTPUT, OUTPUT);

	//����Ʈ �������� ���� ��� �� �ʱ�ȭ
	pinMode(shift_reg_pin::inner_collison_alert_pin::HCSR04_BACKWARD_TRIG_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::HCSR04_FORWARD_TRIG_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::PIEZO_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::LED_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, OUTPUT);

	this->_shiftRegPwm = ShiftRegisterPWM(NUM_OF_SHIFT_REG, SHIFT_REG_PWM_RESOLUTION);
	//����Ʈ �������ͷ� PWM ��� ���� �ϵ���� Ÿ�̸� 1 ���
	this->_shiftRegPwm.interrupt(ShiftRegisterPWM::UpdateFrequency::SuperFast);
	this->ClearPwmData();
}

/// <summary>
/// COMMON_SHIFT_REG_PWM �Ҹ���
/// </summary>
COMMON_SHIFT_REG_PWM::~COMMON_SHIFT_REG_PWM()
{
}

/// <summary>
/// ����Ʈ �������� ��� �ɿ� ��� �� PWM ������ �ʱ�ȭ
/// </summary>
void COMMON_SHIFT_REG_PWM::ClearPwmData()
{
	memset(this->_pwmData, MIN_PWM_VALUE, (sizeof(unsigned char) * 8));
}

/// <summary>
/// �̵� ���������� ���� �� ��ȣ�� ��� �� PWM ������ �Ҵ�
/// </summary>
/// <param name="index">�̵� ���������� ���� �� ��ȣ</param>
/// <param name="pwmData">��� �� PWM ������</param>
void COMMON_SHIFT_REG_PWM::SetPwmData(char index, unsigned char pwmData)
{
	if (index < 0 || index >= 8)
	{
		ERROR_LOG("Pwm Index - Out Of Range");
		return;
	}

	this->_pwmData[index] = pwmData;
}

/// <summary>
/// ��ü �̵� ���������� ���� �� ��ȣ�� PWM ������ ���
/// </summary>
void COMMON_SHIFT_REG_PWM::WriteShiftReg() const
{
	for (char i = 0; i < 8; i++)
		this->_shiftRegPwm.set(i, this->_pwmData[i]);
}