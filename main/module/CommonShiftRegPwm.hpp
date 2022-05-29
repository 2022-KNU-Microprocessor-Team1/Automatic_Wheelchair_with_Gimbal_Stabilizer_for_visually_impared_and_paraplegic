#ifndef _COMMON_SHIFT_REG_PWM_HPP_
#define _COMMON_SHIFT_REG_PWM_HPP_

#include "../Wheelchair_Core.h"

#define ShiftRegisterPWM_CUSTOM_INTERRUPT
#include <ShiftRegisterPWM.h> // https://github.com/Simsso/ShiftRegister-PWM-Library
#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#define NUM_OF_SHIFT_REG 1 //쉬프트 레지스터 개수
#define SHIFT_REG_OUTPUT_PIN_COUNT (NUM_OF_SHIFT_REG * 8) //쉬프트 레지스터의 총 출력 핀 개수
#define SHIFT_REG_PWM_RESOLUTION (MAX_PWM_VALUE) //쉬프트 레지스터 PWM 출력 위한 해상도 (1 ~ 255)

/***
	인터럽트 발생 시 흐름이 ISR로 넘어가므로, 기타 센서의 동작을 위해
	delay를 이용 할 경우, 최대한 방해없는 동작을 위해
	타이머 인터럽트 발생 단위 시간을 그 이상으로 할당 할 것
***/
#define TIMER_INTERRUPT_MS 20 //하드웨어 타이머 인터럽트 발생 단위 시간 (ms)

void COMMON_SHIFT_REG_PWM_InterruptServiceRoutine_Wrapper();

/// <summary>
/// 공통 쉬프트 레지스터 PWM 출력
/// </summary>
class COMMON_SHIFT_REG_PWM : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	/// <summary>
	/// 초기화
	/// </summary>
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

		//하드웨어 타이머 3 사용, 타이머에 의해 인터럽트 발생 시마다 시프트 레지스터 출력 갱신
		Timer3.initialize(TIMER_INTERRUPT_MS);
		Timer3.attachInterrupt(&COMMON_SHIFT_REG_PWM_InterruptServiceRoutine_Wrapper);

		this->ClearPwmData();
		this->_shiftRegPwm = new ShiftRegisterPWM(NUM_OF_SHIFT_REG, SHIFT_REG_PWM_RESOLUTION);
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
		if (index >= SHIFT_REG_OUTPUT_PIN_COUNT)
		{
			ERROR_LOG("Pwm Index - Out Of Range");
			return;
		}

		/***
			ShiftRegister-PWM-Library의 출력 핀이 역순으로 할당되어 있으므로,
			정방향으로 출력 위해 역순 할당 : 0번 입력 => 7번 출력 할당
		***/

		this->_pwmData[(SHIFT_REG_OUTPUT_PIN_COUNT - index)] = pwmData;
	}

	/// <summary>
	/// 하드웨어 타이머에 의해 인터럽트 발생 시 수행 될 작업 (ISR)
	/// </summary>
	void InterruptServiceRoutine() const
	{
		for (uint8_t i = 0; i < 8; i++) //마지막으로 할당 된 PWM 값 할당
			this->_shiftRegPwm->set(i, this->_pwmData[i]);

		this->_shiftRegPwm->update();
	}

private:
	//상속 시 SINGLETON에서 상속받은 개체의 생성자, 소멸자 접근
	friend class SINGLETON<COMMON_SHIFT_REG_PWM>;

	/// <summary>
	/// COMMON_SHIFT_REG_PWM 생성자
	/// </summary>
	COMMON_SHIFT_REG_PWM()
	{
		this->_shiftRegPwm = NULL;
		this->Init();
	}

	/// <summary>
	/// COMMON_SHIFT_REG_PWM 소멸자
	/// </summary>
	~COMMON_SHIFT_REG_PWM()
	{
		delete this->_shiftRegPwm;
		this->_shiftRegPwm = NULL;
	}

private:
	uint8_t _pwmData[SHIFT_REG_OUTPUT_PIN_COUNT]; //쉬프트 레지스터 출력 핀에 출력 될 PWM 데이터 (index : shift_reg_pin에 따름)
	class ShiftRegisterPWM* _shiftRegPwm;
};

/// <summary>
/// COMMON_SHIFT_REG_PWM의 ISR 래퍼
/// </summary>
void COMMON_SHIFT_REG_PWM_InterruptServiceRoutine_Wrapper()
{
	// https://forum.arduino.cc/t/how-to-use-attachinterrupt-with-a-class-member/41823/2
	COMMON_SHIFT_REG_PWM::GetInstance().
		InterruptServiceRoutine(); //고유 인스턴스의 ISR 호출
}
#endif