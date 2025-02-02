// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/Export.h"

#include <qsf/base/UniqueInstance.h>
#include <qsf/base/rights/RightsManager.h>

#include <boost/signals2.hpp>

#include <unordered_set>


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
	*    EMERGENCY 5 rights manager
	*/
	class EM5_API_EXPORT RightsManager : public qsf::RightsManager, public qsf::UniqueInstance<RightsManager>
	{


	//[-------------------------------------------------------]
	//[ Public Boost signals                                  ]
	//[-------------------------------------------------------]
	public:
		boost::signals2::signal<void (const RightsManager&)> RightsChange;	///< Boost signal emitted after a rights change has occurred


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		typedef std::unordered_set<uint32_t> RightIds;


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		RightsManager();

		/**
		*  @brief
		*    Destructor
		*/
		inline virtual ~RightsManager();

		/**
		*  @brief
		*    Check whether or not the requested right is set
		*
		*  @param[in] id
		*    The unique right identifier generated by "qsf::StringHash"
		*
		*  @return
		*    "true" if the requested right is set, else "false"
		*/
		inline bool hasRight(const qsf::StringHash& id) const;

		/**
		*  @brief
		*    Return the rights
		*
		*  @return
		*    The rights
		*/
		inline const RightIds& getRightIds() const;

		/**
		*  @brief
		*    Set the rights
		*
		*  @param[in] rightIds
		*    The new rights
		*/
		inline void setRightIds(const RightIds& rightIds);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RightIds mRightIds;


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // qsf


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "em5/base/rights/RightsManager-inl.h"
