// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <qsf/gui/GuiDocument.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    Base layer for the in-game HUD
	*/
	class BaseHudLayer : public qsf::GuiDocument
	{


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		explicit BaseHudLayer(qsf::GuiContext& guiContext);


	//[-------------------------------------------------------]
	//[ Public virtual qsf::GuiDocument methods               ]
	//[-------------------------------------------------------]
	public:
		virtual void processEvent(const std::string& eventKey, Rocket::Core::Event& event) override;


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // em5
