#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class Graph
{

public:
	
	// if nodes "from" and "to" don't exist, they will be added
	// complexity: O(1) average, O(n) worst case
	void AddNode(string From, string To, float Probability)
	{
		AdjacentNodes[From].push_back(pair<string, float>(To, Probability));
	}

	// return adjacent nodes to vertex "from"
	// complexity: O(1) average, O(n) worst case
	list<pair<string, float>> operator[](string From) { return AdjacentNodes[From]; }

private:

	unordered_map<string, list<pair<string, float>>> AdjacentNodes;
};

class State
{

public:

	// complexity:O(n) where n is total number of weather states
	State* GetNextState(Graph HMM);
	
	virtual string ToString() = 0;

	// create state object from string argument
	static State* CreateState(string State); 
};

class ClearState : public State
{

public:

	string ToString() { return "clear"; }
};

class CloudyState : public State
{

public:

	string ToString() { return "cloudy"; }
};

class RainyState : public State
{

public:

	string ToString() { return "rainy"; }
};

class StormyState : public State
{

public:

	string ToString() { return "stormy"; }
};

class WeatherManager
{

public:

	WeatherManager() : CurrentState(0) {}
	~WeatherManager() { if (CurrentState) delete CurrentState; }

	// add weather states and transition between "from" -> "to" based on probability
	// complexity: same as Graph::AddNode()
	void AddWeather(string From, string To, float Probability)
	{
		HMM.AddNode(From, To, Probability);
	}

	// calculate weather state for next frame
	// complexity: same as State::GetNextState()
	void ChangeWeather()
	{
		// please note: the current implementation does not account for the duration of the state 
		// nor cross fading
		if (CurrentState)
		{
			State* State = CurrentState->GetNextState(HMM);
			delete CurrentState;
			CurrentState = State;
		}
	}

	void SetState(string State)
	{
		if (CurrentState)
		{
			delete CurrentState;
		}
		CurrentState = State::CreateState(State);
	}

	void GetState()
	{
		cout << CurrentState->ToString() << endl;
	}

private:

	Graph HMM;
	State* CurrentState;
};

