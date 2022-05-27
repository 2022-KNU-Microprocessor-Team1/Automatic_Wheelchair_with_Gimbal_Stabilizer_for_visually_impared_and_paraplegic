#include "../Wheelchair_Core.h"

/// <summary>
/// COMMON_SHIFT_REG_PWM 생성자
/// </summary>
COMMON_SHIFT_REG_PWM::COMMON_SHIFT_REG_PWM()
{
	//쉬프트 레지스터 핀 초기화
	pinMode(shift_reg_pin::HC595_DATA_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::HC595_RCLK_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::HC595_SRCLK_OUTPUT, OUTPUT);

	//쉬프트 레지스터 내부 출력 핀 초기화
	pinMode(shift_reg_pin::inner_collison_alert_pin::HCSR04_BACKWARD_TRIG_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::HCSR04_FORWARD_TRIG_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::PIEZO_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_collison_alert_pin::LED_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, OUTPUT);
	pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, OUTPUT);

	this->_shiftRegPwm = ShiftRegisterPWM(NUM_OF_SHIFT_REG, SHIFT_REG_PWM_RESOLUTION);
	//쉬프트 레지스터로 PWM 출력 위해 하드웨어 타이머 1 사용
	this->_shiftRegPwm.interrupt(ShiftRegisterPWM::UpdateFrequency::SuperFast);
	this->ClearPwmData();
}

/// <summary>
/// COMMON_SHIFT_REG_PWM 소멸자
/// </summary>
COMMON_SHIFT_REG_PWM::~COMMON_SHIFT_REG_PWM()
{
}

/// <summary>
/// 쉬프트 레지스터 출력 핀에 출력 될 PWM 데이터 초기화
/// </summary>
void COMMON_SHIFT_REG_PWM::ClearPwmData()
{
	memset(this->_pwmData, MIN_PWM_VALUE, (sizeof(unsigned char) * 8));
}

/// <summary>
/// 이동 레지스터의 내부 핀 번호에 출력 될 PWM 데이터 할당
/// </summary>
/// <param name="index">이동 레지스터의 내부 핀 번호</param>
/// <param name="pwmData">출력 될 PWM 데이터</param>
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
/// 전체 이동 레지스터의 내부 핀 번호에 PWM 데이터 출력
/// </summary>
void COMMON_SHIFT_REG_PWM::WriteShiftReg() const
{
	for (char i = 0; i < 8; i++)
		this->_shiftRegPwm.set(i, this->_pwmData[i]);
}