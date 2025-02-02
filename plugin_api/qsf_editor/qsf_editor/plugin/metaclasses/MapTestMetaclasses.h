// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <qsf/plugin/metaclasses/Metaclasses.h>

#include <QtCore/qobjectdefs.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace editor
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Static CAMP map test plugin metaclass collection class
		*/
		class MapTestMetaclasses : public QObject, public Metaclasses
		{


		//[-------------------------------------------------------]
		//[ Qt definitions (MOC)                                  ]
		//[-------------------------------------------------------]
		Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
					// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


		//[-------------------------------------------------------]
		//[ Friends                                               ]
		//[-------------------------------------------------------]
			friend class Plugin;


		//[-------------------------------------------------------]
		//[ Private methods                                       ]
		//[-------------------------------------------------------]
		private:
			/**
			*  @brief
			*    Constructor
			*
			*  @param[in] plugin
			*    Plugin to register the CAMP metaclasses within, instance must stay valid as long as this metaclass collection instance exists
			*/
			explicit MapTestMetaclasses(qsf::Plugin& plugin);

			/**
			*  @brief
			*    Destructor
			*
			*  @brief
			*    - Not virtual by intent
			*/
			~MapTestMetaclasses();

			/**
			*  @brief
			*    Register the CAMP metaclasses
			*/
			void registerMetaclasses();


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // editor
} // qsf
