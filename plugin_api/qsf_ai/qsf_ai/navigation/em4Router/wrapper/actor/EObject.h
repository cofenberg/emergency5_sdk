// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_ai/navigation/em4Router/wrapper/actor/EGenericObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace ai
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    EObject wrapper class for a QSF entity
		*/
		class EObject : public EGenericObject
		{


		//[-------------------------------------------------------]
		//[ Protected methods                                     ]
		//[-------------------------------------------------------]
		protected:
			EObject() : EGenericObject(EAT_OBJECT) {}


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // ai
} // qsf
