#ifndef _MOVE_MANAGER_H_
#define _MOVE_MANAGER_H_

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
/// 이동 관리자
/// </summary>
class MOVE_MANAGER
{
public:
	void MoveTo(MOVE_DIRECTION) const;

private:
	MOVE_MANAGER();
	~MOVE_MANAGER();
};
#endif