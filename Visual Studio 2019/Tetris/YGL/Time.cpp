#include "Time.hpp"


// —˜_ã‚ÌFPS’l‚ğæ“¾‚·‚é
double Time::GetTheoreticalFPS() {

	return (double)RefreshRate;

}

// ÀÛ‚ÌFPS’l‚ğæ“¾‚·‚é
double Time::GetActualFPS() {

	return FPS;

}