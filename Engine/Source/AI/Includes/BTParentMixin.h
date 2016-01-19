//  *******************************************************************************************************************
//  BTParentMixin   version:  1.0   Ankur Sheel  date: 2014/12/11
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTPARENTMIXIN_H__
#define __BTPARENTMIXIN_H__

namespace AI
{
	template <class PARENT>
	struct cBTParentMixin
	{
	protected:
		PARENT* m_pParent;

	public:
		cBTParentMixin<PARENT>()
		: m_pParent(0)
		{
		}

		PARENT& End()
		{
			return *m_pParent;
		}
	};
}
#endif  // __BTPARENTMIXIN_H__
