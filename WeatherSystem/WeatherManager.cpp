#include "WeatherManager.h"

State* State::GetNextState(Graph HMM)
{
	string ThisState = ToString();
	
	// get number in [0, 1] interval
	// TODO use some advanced random generator (need normal distribution)
	float Random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float Sum = 0.0f;
	for (auto It : HMM[ThisState])
	{
		float Probability = It.second;
		if (Sum <= Random && Random < (Sum + Probability))
		{
			return State::CreateState(It.first);
		}		
		Sum += Probability;
	}

	return nullptr;
}

State* State::CreateState(string State)
{
	if (State == "clear")
	{
		return new ClearState();
	}
	else if (State == "cloudy")
	{
		return new CloudyState();
	}
	else if (State == "rainy")		
	{
		return new RainyState();
	}
	else if (State == "stormy")
	{
		return new StormyState();
	}

	return nullptr;
}