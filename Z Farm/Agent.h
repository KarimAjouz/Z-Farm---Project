#pragma once
class Agent
{
public:
	Agent();
	~Agent();

	virtual void Update(float dT) = 0;
	virtual void Draw(float dT) = 0;

private:
};

