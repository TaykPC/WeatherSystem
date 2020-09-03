#include "WeatherManager.h"
#include <ctime>

// model weather as random process using Hidden Markov Model (HMM)
// HMM is a set of states and transitions between states based on probability theory
int main()
{
	// TODO FIXME: implement duration and cross fading
	srand(static_cast<unsigned>(time(nullptr)));
	
	// please note: probability from every node needs to be 1
	WeatherManager Manager;
	Manager.AddWeather("clear", "clear", 0.2f);
	Manager.AddWeather("clear", "cloudy", 0.8f);
	Manager.AddWeather("cloudy", "cloudy", 0.3f);
	Manager.AddWeather("cloudy", "clear", 0.3f);
	Manager.AddWeather("cloudy", "rainy", 0.3f);
	Manager.AddWeather("cloudy", "stormy", 0.1f);
	Manager.AddWeather("rainy", "rainy", 0.4f);
	Manager.AddWeather("rainy", "cloudy", 0.4f);
	Manager.AddWeather("rainy", "stormy", 0.2f);
	Manager.AddWeather("stormy", "stormy", 0.1f);
	Manager.AddWeather("stormy", "cloudy", 0.1f);
	Manager.AddWeather("stormy", "rainy", 0.8f);
	Manager.SetState("clear");

	for (unsigned i = 0; i < 20; i++)
	{
		// each state has a duration of 1 frame
		Manager.GetState();
		Manager.ChangeWeather();
	}

	return 0;
}