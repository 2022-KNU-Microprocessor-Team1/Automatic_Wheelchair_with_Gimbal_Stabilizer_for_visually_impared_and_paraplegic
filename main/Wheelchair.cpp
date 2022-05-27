#include "./Wheelchair_Core.h"

WHEELCHAIR::WHEELCHAIR()
{
	pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT1, INPUT);
	pinMode(wheel_pin::H_BRIDGE_LEFT_INPUT2, INPUT);
	pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT1, INPUT);
	pinMode(wheel_pin::H_BRIDGE_RIGHT_INPUT2, INPUT);
	pinMode(collision_alert_pin::HCSR04_BACKWARD_ECHO_INPUT, INPUT);
	pinMode(collision_alert_pin::HCSR04_FORWARD_ECHO_INPUT, INPUT);


	
}

WHEELCHAIR::~WHEELCHAIR()
{
}

void WHEELCHAIR::RunTask()
{

}
