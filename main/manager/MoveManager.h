#ifndef _MOVE_MANAGER_H_
#define _MOVE_MANAGER_H_

#define MAX_WHEEL_ROTATE_SPEED (MAX_PWM_VALUE - 155) //최대 바퀴 회전 속도

/// <summary>
/// 적외선 통신 핀 정의
/// </summary>
namespace ir_comm_pin
{
	//TODO : 리모콘 버튼 입력 시 이동
	const int IR_INPUT;

};

/// <summary>
/// 바퀴에 대한 핀 정의
/// </summary>
namespace wheel_pin
{
	const int H_BRIDGE_LEFT_INPUT1 = 11; //H-브릿지 왼쪽 바퀴 입력 핀 1
	const int H_BRIDGE_LEFT_INPUT2 = 10; //H-브릿지 왼쪽 바퀴 입력 핀 2

	const int H_BRIDGE_RIGHT_INPUT1 = 9; //H-브릿지 오른쪽 바퀴 입력 핀 1
	const int H_BRIDGE_RIGHT_INPUT2 = 8; //H-브릿지 오른쪽 바퀴 입력 핀 2
};

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
/// 이동 관리자
/// </summary>
class MOVE_MANAGER : public SINGLETON<COMMON_SHIFT_REG_PWM>
{
public:
	void MoveTo(MOVE_DIRECTION) const;

private:
	//상속 시 SINGLETON에서 생성자, 소멸자 접근
	friend class SINGLETON;

	MOVE_MANAGER();
	~MOVE_MANAGER();
};
#endif