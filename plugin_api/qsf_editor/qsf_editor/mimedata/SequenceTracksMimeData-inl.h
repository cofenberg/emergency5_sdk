// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace editor
	{


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		inline SequenceTracksMimeData::~SequenceTracksMimeData()
		{
			// Nothing to do in here
		}


		//[-------------------------------------------------------]
		//[ Public virtual QMimeData methods                      ]
		//[-------------------------------------------------------]
		inline bool SequenceTracksMimeData::hasFormat(const QString& mimeType) const
		{
			return (MIME_TYPE == mimeType);
		}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // editor
} // qsf
