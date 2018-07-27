// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf/plugin/pluginable/PluginableManager.h"

#include <boost/container/flat_map.hpp>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class Right;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    Rights manager class
	*
	*  @remarks
	*    The rights manager orchestrates the rights generally known to the QSF application, each plugin can add its own rights.
	*
	*    The purpose of the rights class is to collect fine granular rights instead of having to write a new
	*    class for each and every tiny right. This way new rights can be plugged into the QSF rights
	*    system with a reasonable amount of effort.
	*
	*    The rights manager is automatically able to use all CAMP classes which are derived from "qsf::Rights".
	*/
	class QSF_API_EXPORT RightsManager : public PluginableManager
	{


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
		friend class Right; // Individual rights register/unregister themselves


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		typedef std::vector<const Right*>						 RightList;
		typedef boost::container::flat_map<uint32, const Right*> RightMap;


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		inline RightsManager();

		/**
		*  @brief
		*    Destructor
		*/
		inline virtual ~RightsManager();

		/**
		*  @brief
		*    Return a right instance by using its unique identifier
		*
		*  @param[in] id
		*    The unique right identifier generated by "qsf::StringHash"
		*
		*  @return
		*    The requested right instance, null pointer on error (maybe the ID is unknown?), do not destroy the instance
		*/
		inline const Right* getRightById(const StringHash& id) const;

		/**
		*  @brief
		*    Return the right list
		*
		*  @return
		*    Reference to the internal right list, do not manipulate the list or destroy the rights
		*/
		inline const RightList& getRights() const;

		/**
		*  @brief
		*    Convert a right ID into a right string
		*
		*  @param[in] rightId
		*    ID of the right to convert into a string
		*
		*  @return
		*    The right ID as right string, human readable on success, ID as number in case of unknown right (we need to be tolerant in here)
		*/
		std::string rightIdToString(uint32 rightId) const;

		/**
		*  @brief
		*    Convert a right string into a right ID
		*
		*  @param[in] rightString
		*    String of the right to convert into a right ID
		*
		*  @return
		*    The right string as right ID
		*/
		uint32 rightStringToId(const std::string& rightString) const;

		/**
		*  @brief
		*    Return all rights as semicolon separated string
		*
		*  @return
		*    All rights as semicolon separated ASCII string (e.g. "ServerManagement;AssetManagement")
		*
		*  @note
		*    - Ease-of-use method
		*/
		std::string getAllRightsAsString() const;


	//[-------------------------------------------------------]
	//[ Protected virtual qsf::PluginableManager methods      ]
	//[-------------------------------------------------------]
	protected:
		virtual void classAdded(const camp::Class& added) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RightList mRightList;	///< List of all individual rights within the rights manager
		RightMap  mRightMap;	///< Individual rights map with unique right identifier as key and pointer to the right as value


	//[-------------------------------------------------------]
	//[ CAMP reflection system                                ]
	//[-------------------------------------------------------]
	QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // qsf


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "qsf/base/rights/RightsManager-inl.h"


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(qsf::RightsManager)
