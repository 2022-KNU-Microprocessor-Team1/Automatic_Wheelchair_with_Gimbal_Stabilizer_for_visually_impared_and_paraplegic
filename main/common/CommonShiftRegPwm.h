#ifndef _COMMON_SHIFT_REG_PWM_H_
#define _COMMON_SHIFT_REG_PWM_H_

#define NUM_OF_SHIFT_REG 1 //쉬프트 레지스터 개수
#define SHIFT_REG_PWM_RESOLUTION (MAX_PWM_VALUE) //쉬프트 레지스터 PWM 출력 위한 해상도 (1 ~ 255)

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
	//상속 시 SINGLETON에서 상속받은 개체의 생성자, 소멸자 접근
	friend class SINGLETON<COMMON_SHIFT_REG_PWM>;

	COMMON_SHIFT_REG_PWM();
	~COMMON_SHIFT_REG_PWM();
};
#endif