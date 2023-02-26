#include "AlertBubble.h"
#include "Definitions.h"

AlertBubble::AlertBubble(ZEngine::GameDataRef data) :
	_data(data),
	animSys(&sprite, data)
{
	InitAnimations();
	sprite.setScale(2.0f, 2.0f);

	alertState = AlertState::passive;

}

AlertBubble::~AlertBubble()
{
}

void AlertBubble::Update(float dT, sf::Vector2f pos)
{
	if (alertState != AlertState::passive && alertState != AlertState::alert)
	{
		animSys.Update(dT);
		sprite.setPosition(pos);
	}
}

void AlertBubble::Draw()
{
	if (alertState != AlertState::passive && alertState != AlertState::alert)
		_data->GameWindow.draw(sprite);
}

bool AlertBubble::UpdateState(bool seePlayer, ZEngine::Timer* questionTimer)
{
	switch (alertState)
	{
	case AlertState::passive:
		if (seePlayer)
		{
			questionTimer->Start();
			alertState = AlertState::question;
			QuestionIn();
		}
		break;
	case AlertState::question:
		if (animSys.GetCurrentAnim() != "QuestionIn" && animSys.GetCurrentAnim() != "QuestionOut" && animSys.GetCurrentAnim() == "NONE")
			QuestionIn();
		else if (animSys.GetCurrentAnim() == "QuestionIn" && questionTimer->Complete())
			QuestionOut();
		else if (animSys.GetCurrentAnim() == "QuestionOut" && animSys.Complete())
			if (seePlayer)
				alertState = AlertState::alerted;
			else
			{
				alertState = AlertState::passive;
				questionTimer->Reset();
			}

		break;
	case AlertState::alerted:
		if (animSys.GetCurrentAnim() != "AlertIn" && animSys.GetCurrentAnim() != "AlertOut")
			AlertIn();
		else if (animSys.GetCurrentAnim() == "AlertIn" && animSys.Complete())
			AlertOut();
		else if (animSys.GetCurrentAnim() == "AlertOut" && animSys.Complete())
			alertState = AlertState::alert;
		break;
	case AlertState::alert:
		return true;
		break;
	}
	return false;
}


void AlertBubble::QuestionIn()
{
	animSys.SetAnimation("QuestionIn");
	animSys.Play();
}
void AlertBubble::QuestionOut()
{
	animSys.SetAnimation("QuestionOut");
	animSys.Play();
}

void AlertBubble::AlertIn()
{
	animSys.SetAnimation("AlertIn");
	animSys.Play();
}

void AlertBubble::AlertOut()
{
	animSys.SetAnimation("AlertOut");
	animSys.Play();
}

void AlertBubble::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 14, 12);
	sf::Vector2f frameOrigin = sf::Vector2f(7, 6);
	animSys.AddAnimation("QuestionIn", DIALOGUE_QUESTION_IN, 0.6f, false, frameRect, frameOrigin);
	animSys.AddAnimation("QuestionOut", DIALOGUE_QUESTION_OUT, 0.4f, false, frameRect, frameOrigin);
	animSys.AddAnimation("AlertIn", DIALOGUE_ALERT_IN, 0.6f, false, frameRect, frameOrigin);
	animSys.AddAnimation("AlertOut", DIALOGUE_ALERT_OUT, 0.4f, false, frameRect, frameOrigin);
}