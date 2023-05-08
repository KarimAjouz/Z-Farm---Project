#pragma once
#include <stack>
#include <memory>

#include "GameState.h"
namespace ZEngine
{
	typedef std::unique_ptr<GameState> StateRef;

	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		void AddState(StateRef newState, bool isReplacing);
		void RemoveState();

		void ProcessStateChanges();

	private:

	public:
		StateRef& GetActiveState();

	private:
		std::stack<StateRef> _states;
		StateRef _newState;

		bool _isAdding;
		bool _isRemoving;
		bool _isReplacing;
	};
}