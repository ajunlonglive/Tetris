#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Time.hpp"


class Time : private Core, private Core_Time {

public:
	// ���_���FPS�l���擾����
	static double GetTheoreticalFPS();

	// ���ۂ�FPS�l���擾����
	static double GetActualFPS();

};