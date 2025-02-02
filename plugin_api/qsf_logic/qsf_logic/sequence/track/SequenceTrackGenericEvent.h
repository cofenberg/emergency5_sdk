// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_logic/sequence/track/SequenceTrack.h"
#include "qsf_logic/sequence/track/SequenceTrackKey.h"

#include <qsf/reflection/type/CampUint64.h>	// The 64 bit unsigned integer ID of the sequencer entity component property track class is connected to the CAMP reflection system, so we need this header to tell CAMP about this data type
#include <qsf/base/GetUninitialized.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace logic
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		class QSF_LOGIC_API_EXPORT SequenceTrackKeyGenericEvent : public SequenceTrackKey
		{


		//[-------------------------------------------------------]
		//[ Public data                                           ]
		//[-------------------------------------------------------]
		public:
			std::string mMessage;
			uint64		mFilter;
			std::string mParameter;


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			explicit SequenceTrackKeyGenericEvent(uint32 frameNumber) : SequenceTrackKey(frameNumber), mFilter(getUninitialized<uint64>()) {}


		//[-------------------------------------------------------]
		//[ CAMP reflection system                                ]
		//[-------------------------------------------------------]
		QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


		};

		/**
		*  @brief
		*    Generic event sequence track
		*/
		class QSF_LOGIC_API_EXPORT SequenceTrackGenericEvent : public SequenceTrack
		{


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			SequenceTrackGenericEvent(Sequence* sequence, uint32 id);
			virtual ~SequenceTrackGenericEvent();


		//[-------------------------------------------------------]
		//[ Public virtual qsf::logic::SequenceTrack methods      ]
		//[-------------------------------------------------------]
		public:
			virtual void serializeOriginalControlledValue(BinarySerializer& serializer) override;
			virtual uint32 getKeyCount() const override;
			virtual const SequenceTrackKey* getKeyFromIndex(uint32 index) const override;
			virtual SequenceTrackKey* getKeyFromIndex(uint32 index) override;
			virtual SequenceTrackKeyWithIndex createKeyAtFrame(uint32 frame) override;
			virtual void removeKeyAtIndex(uint32 index) override;
			virtual void deleteAllKeys() override;


		//[-------------------------------------------------------]
		//[ Protected virtual qsf::logic::SequenceTrackGenericEvent methods ]
		//[-------------------------------------------------------]
		protected:
			/**
			*  @brief
			*    Called if an event has been triggered
			*
			*  @remarks
			*    This is triggered by the track evaluation algorithm for each event detected.
			*    May be called multiple times during one frame, but the order of the
			*    events is always guranteed to be in the right order
			*/
			virtual void onEventTriggered(const SequenceTrackKeyGenericEvent& key) const;


		//[-------------------------------------------------------]
		//[ Protected virtual qsf::logic::SequenceTrack methods   ]
		//[-------------------------------------------------------]
		protected:
			virtual void notifyTimePassed(float oldTime, float newTime) const override;


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			typedef std::vector<SequenceTrackKeyGenericEvent*> KeyList;
			KeyList mKeys;


		//[-------------------------------------------------------]
		//[ CAMP reflection system                                ]
		//[-------------------------------------------------------]
		QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // logic
} // qsf


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE(qsf::logic::SequenceTrackKeyGenericEvent)
QSF_CAMP_TYPE_NONCOPYABLE(qsf::logic::SequenceTrackGenericEvent)
