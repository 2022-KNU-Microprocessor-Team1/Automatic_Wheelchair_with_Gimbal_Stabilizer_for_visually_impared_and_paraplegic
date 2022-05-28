#ifndef _BODY_MOVE_HPP_
#define _BODY_MOVE_HPP_

#include "../Wheelchair_Core.h"

//#include "../extern_lib/IRremote/src/IRremote.h" // https://github.com/Arduino-IRremote/Arduino-IRremote

#define MAX_WHEEL_ROTATE_SPEED (MAX_PWM_VALUE - 155) //최대 바퀴 회전 속도

/// <summary>
/// 이동 방향
/// </summary>
enum class MOVE_DIRECTION : const int
{
	FORWARD = 0, //전진
	BACKWARD, //후진
	LEFT, //제자리 좌회전
	RIGHT, //제자리 우회전
	LEFT_AND_FORWARD, //좌회전 및 전진
	RIGHT_AND_FORWARD, //우회전 및 전진
	BRAKE //정지
};

/// <summary>
/// 차체 이동
/// </summary>
class BODY_MOVE
{
public:
	/// <summary>
	/// BODY_MOVE 생성자
	/// </summary>
	BODY_MOVE()
	{
	}

	/// <summary>
	/// BODY_MOVE 소멸자
	/// </summary>
	~BODY_MOVE()
	{
	}

	void Init()
	{
		pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT1, INPUT);
		pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT2, INPUT);
		pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT1, INPUT);
		pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT2, INPUT);

		//TODO : 적외선 통신 핀 테스트 후 초기화 수행
	}

	/// <summary>
	/// 이동 방향에 따라 차체 이동
	/// </summary>
	/// <param name="moveDirection">이동 방향</param>
	void MoveTo(MOVE_DIRECTION moveDirection) const
	{
		COMMON_SHIFT_REG_PWM& commonShiftRegPwmInstance = COMMON_SHIFT_REG_PWM::GetInstance();

		//스위치의 상태 변경 전 비활성화 (단락 방지)
		commonShiftRegPwmInstance.SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, LOW);
		commonShiftRegPwmInstance.SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, LOW);

		int leftWheelRotateSpeed = 0; //왼쪽 바퀴 회전 속도
		int rightWheelRotateSpeed = 0; //오른쪽 바퀴 회전 속도

		switch (moveDirection) //이동 방향에 따라 각 바퀴의 이동 속도 할당
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

		switch (moveDirection) //이동 방향에 따라 H-브릿지 출력 방향 설정
		{
		case MOVE_DIRECTION::FORWARD:
		case MOVE_DIRECTION::LEFT:
		case MOVE_DIRECTION::RIGHT:
		case MOVE_DIRECTION::LEFT_AND_FORWARD:
		case MOVE_DIRECTION::RIGHT_AND_FORWARD:
			//전진 위한 출력 1 활성화, 출력 2 비활성화
			digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT1, HIGH);
			digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT2, LOW);
			digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT1, HIGH);
			digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT2, LOW);
			break;

		case MOVE_DIRECTION::BACKWARD:
			//후진 위한 출력 1 비활성화, 출력 2 활성화
			digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT1, LOW);
			digitalWrite(wheel_pin::H_BRIDGE_LEFT_INPUT2, HIGH);
			digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT1, LOW);
			digitalWrite(wheel_pin::H_BRIDGE_RIGHT_INPUT2, HIGH);
			break;

		case MOVE_DIRECTION::BRAKE:
			break;
		}

		//각 바퀴의 회전 속도에 따라 제어
		commonShiftRegPwmInstance.SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_LEFT_EN_OUTPUT, leftWheelRotateSpeed);
		commonShiftRegPwmInstance.SetPwmData(shift_reg_pin::inner_wheel_pin::H_BRIDGE_RIGHT_EN_OUTPUT, rightWheelRotateSpeed);
	}

private:

};
#endif