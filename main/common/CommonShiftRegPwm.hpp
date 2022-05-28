#ifndef _COMMON_SHIFT_REG_PWM_HPP_
#define _COMMON_SHIFT_REG_PWM_HPP_

#ifndef ShiftRegisterPWM_h
#error "Must include ShiftRegisterPWM.h"
#endif

#define NUM_OF_SHIFT_REG 1 //쉬프트 레지스터 개수
#define SHIFT_REG_PWM_RESOLUTION (MAX_PWM_VALUE) //쉬프트 레지스터 PWM 출력 위한 해상도 (1 ~ 255)

ShiftRegisterPWM shiftRegPwm(NUM_OF_SHIFT_REG, SHIFT_REG_PWM_RESOLUTION);

/// <summary>
/// 공통 쉬프트 레지스터 PWM 출력
/// </summary>
class COMMON_SHIFT_REG_PWM : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void Init()
	{
		//쉬프트 레지스터 핀 초기화
		pinMode(shift_reg_pin::HC595_DATA_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::HC595_RCLK_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::HC595_SRCLK_OUTPUT, OUTPUT);

		//쉬프트 레지스터 내부 출력 핀 초기화
		pinMode(shift_reg_pin::inner_collision_alert_pin::HCSR04_BACKWARD_TRIG_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::inner_collision_alert_pin::HCSR04_FORWARD_TRIG_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::inner_collision_alert_pin::PIEZO_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::inner_collision_alert_pin::LED_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, OUTPUT);
		pinMode(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, OUTPUT);

		//TODO : 이하 삭제 (타이머 3 사용)
		//쉬프트 레지스터로 PWM 출력 위해 하드웨어 타이머 1 사용
		shiftRegPwm.interrupt(ShiftRegisterPWM::UpdateFrequency::SuperFast);
		this->ClearPwmData();
	}

	/// <summary>
	/// 쉬프트 레지스터 출력 핀에 출력 될 PWM 데이터 초기화
	/// </summary>
	void ClearPwmData()
	{
		memset(this->_pwmData, MIN_PWM_VALUE, (sizeof(unsigned char) * 8));
	}

	/// <summary>
	/// 이동 레지스터의 내부 핀 번호에 출력 될 PWM 데이터 할당
	/// </summary>
	/// <param name="index">이동 레지스터의 내부 핀 번호</param>
	/// <param name="pwmData">출력 될 PWM 데이터</param>
	void SetPwmData(uint8_t index, uint8_t pwmData)
	{
		if (index >= 8)
		{
			ERROR_LOG("Pwm Index - Out Of Range");
			return;
		}

		this->_pwmData[index] = pwmData;
	}

	/// <summary>
	/// 전체 이동 레지스터의 내부 핀 번호에 PWM 데이터 출력
	/// </summary>
	void WriteShiftReg() const
	{
		/***
			ShiftRegister-PWM-Library의 출력 핀이 역순으로 할당되어 있으므로,
			0번 출력 핀 => 7번 출력으로 역순으로 출력
		***/

		for (uint8_t i = 0; i < 8; i++)
			shiftRegPwm.set((8 - i), this->_pwmData[i]);
	}

private:
	uint8_t _pwmData[8]; //쉬프트 레지스터 출력 핀에 출력 될 PWM 데이터 (index : shift_reg_pin에 따름)

private:
	//상속 시 SINGLETON에서 상속받은 개체의 생성자, 소멸자 접근
	friend class SINGLETON<COMMON_SHIFT_REG_PWM>;

	/// <summary>
	/// COMMON_SHIFT_REG_PWM 생성자
	/// </summary>
	COMMON_SHIFT_REG_PWM()
	{
	}

	/// <summary>
	/// COMMON_SHIFT_REG_PWM 소멸자
	/// </summary>
	~COMMON_SHIFT_REG_PWM()
	{
	}
};
#endif