#ifndef _COMMON_SHIFT_REG_PWM_H_
#define _COMMON_SHIFT_REG_PWM_H_

#define NUM_OF_SHIFT_REG 1 //쉬프트 레지스터 개수
#define SHIFT_REG_PWM_RESOLUTION (MAX_PWM_VALUE) //쉬프트 레지스터 PWM 출력 위한 해상도 (1 ~ 255)

/// <summary>
/// 이동 레지스터 핀 정의
/// </summary>
namespace shift_reg_pin
{
	/***
		ShiftRegister-PWM-Library는 기본값으로 데이터, LATCH, 클록에 대해
		순차적으로 2, 4, 3번 핀 사용
	***/

	const int HC595_DATA_OUTPUT = 2; //쉬프트 레지스터 데이터 핀
	const int HC595_RCLK_OUTPUT = 4; //쉬프트 레지스터 출력 레지스터 클록 (LATCH)
	const int HC595_SRCLK_OUTPUT = 3; //쉬프트 레지스터 클록

	/***
		ShiftRegister-PWM-Library의 출력 핀이 역순으로 할당되어 있으므로,
		0번 출력 핀 연결 => 7번 출력 핀 할당으로 역순으로 할당 할 것
	***/

	/// <summary>
	/// 쉬프트 레지스터의 출력에 대한 충돌 감지 알림 핀 정의
	/// </summary>
	namespace inner_collison_alert_pin
	{
		const char HCSR04_BACKWARD_TRIG_OUTPUT = 7; //후방 장애물 감지 초음파 센서 트리거 핀 (PWM)
		const char HCSR04_FORWARD_TRIG_OUTPUT = 6; //전방 장애물 감지 초음파 센서 트리거 핀 (PWM)

		const char PIEZO_OUTPUT = 3; //충돌 경고 피에조 부저 (PWM)
		const char LED_OUTPUT = 2; //충돌 경고 LED (PWM)
	};

	/// <summary>
	/// 쉬프트 레지스터의 출력에 대한 바퀴 핀 정의
	/// </summary>
	namespace inner_wheel_pin
	{
		const char H_BRIDGE_RIGHT_EN_OUTPUT = 5; //H-브릿지 오른쪽 바퀴 속도 조절을 위한 1,2 활성화 핀 (PWM)
		const char H_BRIDGE_LEFT_EN_OUTPUT = 4; //H-브릿지 왼쪽 바퀴 속도 조절을 위한 3,4 활성화 핀 (PWM)
	}
};

/// <summary>
/// 공통 쉬프트 레지스터 PWM 출력
/// </summary>
class COMMON_SHIFT_REG_PWM : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void ClearPwmData();
	void SetPwmData(char, unsigned char);
	void WriteShiftReg() const;

private:
	unsigned char _pwmData[8]; //쉬프트 레지스터 출력 핀에 출력 될 PWM 데이터 (index : shift_reg_pin에 따름)
	class ShiftRegisterPWM _shiftRegPwm;

private:
	//상속 시 SINGLETON에서 생성자, 소멸자 접근
	friend class SINGLETON;

	COMMON_SHIFT_REG_PWM();
	~COMMON_SHIFT_REG_PWM();
};
#endif