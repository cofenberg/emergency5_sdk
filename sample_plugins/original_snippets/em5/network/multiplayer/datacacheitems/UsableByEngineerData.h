// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/network/multiplayer/datacache/DataCacheComponentExistenceTrackingBase.h"
#include "em5/component/objects/UsableByEngineerComponent.h"

#include <vector>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class Entity;
	namespace game
	{
		class BitStream;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{
	namespace multiplayer
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    EMERGENCY 5 entity with a usable by engineer component data cache for a single entity for multiplayer
		*/
		class UsableByEngineerData: public DataCacheComponentExistenceTrackingBase<UsableByEngineerComponent>
		{


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			UsableByEngineerData(const qsf::Entity& targetEntity);
			virtual ~UsableByEngineerData();


		//[-------------------------------------------------------]
		//[ Public virtual em5::multiplayer::DataCacheBase methods ]
		//[-------------------------------------------------------]
		public:
			virtual bool prepareForUpdate(const qsf::Entity& targetEntity, const qsf::Clock& clock) override;
			virtual void updateData(qsf::game::BitStream& bitStream, bool force) override;
			virtual void setData(const qsf::game::BitStream& bitStream, const int32 receivedHostTickCount) override;
			virtual void interpolate(qsf::Entity& targetEntity, const qsf::Clock& clock, const int32 receivedHostTickCount) override;


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			bool mUsed;
			bool mIsInUse;

			// For client side only
			struct HistoryEntry
			{
				int32 tickCount;
				bool mUsed;
				bool mIsInUse;
			};

			std::vector<HistoryEntry>	mHistoryList;


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // multiplayer
} // em5
