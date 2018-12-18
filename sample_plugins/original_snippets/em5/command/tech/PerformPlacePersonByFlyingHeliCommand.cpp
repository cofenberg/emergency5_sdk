// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/PrecompiledHeader.h"
#include "em5/command/tech/PerformPlacePersonByFlyingHeliCommand.h"
#include "em5/action/ActionPriority.h"
#include "em5/action/move/MoveAction.h"
#include "em5/action/tech/PlacePersonByFlyingHeliAction.h"
#include "em5/ai/MovementModes.h"
#include "em5/audio/AudioFeedbackHelper.h"
#include "em5/command/mode/DefaultCommandMode.h"

#include <qsf_game/command/CommandContext.h>
#include <qsf_game/command/CommandSystem.h>
#include <qsf_game/QsfGameHelper.h>

#include <qsf_ai/navigation/goal/ReachSinglePointGoal.h>

#include <qsf/logic/action/ActionComponent.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	const uint32 PerformPlacePersonByFlyingHeliCommand::PLUGINABLE_ID = qsf::StringHash("em5::PerformPlacePersonByFlyingHeliCommand");


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	const uint32 PerformPlacePersonByFlyingHeliCommand::ACTION_PRIORITY = action::COMMAND_STD;


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	void PerformPlacePersonByFlyingHeliCommand::pushCommandToEntity(qsf::Entity& entity, qsf::game::CommandContext& commandContext)
	{
		// The command mode will be executed on client side in multiplayer mode, so we need to push the actual actions within another command object to the host for things to work as expected
		const qsf::game::CommandEvaluationHelper::EntityArray callers = { &entity };

		// Execute command, here we have a special way for pushing
		PerformPlacePersonByFlyingHeliCommand& command = QSFGAME_COMMAND.getCommandManager().getSafe<PerformPlacePersonByFlyingHeliCommand>();
		qsf::game::CommandEvaluationHelper::executeCommand(command, callers, commandContext);

		// The command can only be issued for one element in the selection -> no check here for the amount
		AudioFeedbackHelper::playCommandResponse(entity);
	}


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	PerformPlacePersonByFlyingHeliCommand::PerformPlacePersonByFlyingHeliCommand(qsf::game::CommandManager* commandManager) :
		Command(commandManager, PLUGINABLE_ID)
	{
		// No mouse cursor, no button - command is pushed implicitly by the command mode
	}


	//[-------------------------------------------------------]
	//[ Public virtual em5::Command methods                   ]
	//[-------------------------------------------------------]
	bool PerformPlacePersonByFlyingHeliCommand::checkAvailable()
	{
		// This command will only be pushed explicitly and should never be chosen by some automatism
		return false;
	}

	bool PerformPlacePersonByFlyingHeliCommand::checkCaller(qsf::Entity& caller)
	{
		// This command will only be pushed explicitly and should thus always have a valid caller
		return true;
	}

	bool PerformPlacePersonByFlyingHeliCommand::checkContext(const qsf::game::CommandContext& context)
	{
		// This command will only be pushed explicitly and should thus always have a valid context
		return true;
	}

	void PerformPlacePersonByFlyingHeliCommand::execute(const qsf::game::CommandContext& context)
	{
		QSF_ASSERT(nullptr != context.mCaller, "Perform rope down from helicopter command was pushed without a valid caller", QSF_REACT_THROW);

		// Push action
		qsf::ActionComponent& actionComponent = context.mCaller->getOrCreateComponentSafe<qsf::ActionComponent>();
		actionComponent.clearPlan();

		if (context.mCaller != context.mTargetEntity)
		{
			// Create the static target point for the AI to move towards only for non selftargets
			qsf::logic::TargetPoint moveTargetConfig;
			moveTargetConfig.mPosition = context.getTargetPosition();

			actionComponent.pushAction<MoveAction>(ACTION_PRIORITY).init(new qsf::ai::ReachSinglePointGoal(moveTargetConfig), MovementModes::MOVEMENT_MODE_DEFAULT);
		}
		actionComponent.pushAction<PlacePersonByFlyingHeliAction>(action::BLOCKING, qsf::action::APPEND_TO_BACK).init(context.getTargetPosition());

		// Only play it once when the command is executed for multiple entities at the same time
		if (context.mCurrentCallerIndex == 0)
		{
			DefaultCommandMode::showVisualCommandFeedback(context);
		}
	}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // em5
