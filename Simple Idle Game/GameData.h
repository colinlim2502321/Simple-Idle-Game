#pragma once

struct GameData {
	// Game data variables
	double cookies = 0.0;	// Number of cookies
	int grandma = 0;		// Number of grandmas (gives 1 cookie per second)

	int getCookiesPerSecond() const {
		return grandma * 1; // Each grandma gives 1 cookie per second
	}
};
