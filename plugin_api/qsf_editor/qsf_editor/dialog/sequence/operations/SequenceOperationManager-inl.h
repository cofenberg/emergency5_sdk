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
		inline QUndoStack& SequenceOperationManager::getQUndoStack() const
		{
			return getQUndoStackWritable();
		}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // editor
} // qsf
