
#include "BaseModel.h"


		void BaseModel::SetTransform(Transform* _transform)
		{
			transform = _transform;
		}

		BaseModel::BaseModel()
		{
			transform = nullptr;
		}
