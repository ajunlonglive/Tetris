#include "Time.hpp"


// ���_���FPS�l���擾����
double Time::GetTheoreticalFPS() {

	return (double)RefreshRate;

}

// ���ۂ�FPS�l���擾����
double Time::GetActualFPS() {

	return FPS;

}