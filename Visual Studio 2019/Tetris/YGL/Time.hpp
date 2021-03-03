#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Time.hpp"


class Time : private Core, private Core_Time {

public:
	// —˜_ã‚ÌFPS’l‚ğæ“¾‚·‚é
	static double GetTheoreticalFPS();

	// ÀÛ‚ÌFPS’l‚ğæ“¾‚·‚é
	static double GetActualFPS();

};