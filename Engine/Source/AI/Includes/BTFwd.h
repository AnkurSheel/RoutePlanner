//  *******************************************************************************************************************
//  BTFwd   version:  1.0   Ankur Sheel  date: 2014/12/09
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTFWD_H__
#define __BTFWD_H__

namespace AI
{
	namespace BT_STATUS
	{
		enum Enum
		{
			Invalid,
			Running,
			Success,
			Failure,
			Aborted
		};
	}
	namespace BT_POLICY 
	{
		enum Enum
		{
			RequireOne,
			RequireAll
		};
	}

	class cBTBehavior;
	typedef shared_ptr<cBTBehavior> BTNodeStrongPtr;
	typedef weak_ptr<cBTBehavior> BTNodeWeakPtr;
	typedef std::vector<BTNodeStrongPtr> BTNodes;

#define DEFINE_NODE_PROPERTY(CLASS, TYPE, NAME) \
public: \
	shared_ptr<CLASS> const Set##NAME(const TYPE & _##NAME) \
	{ \
	m_##NAME = _##NAME; \
	return dynamic_pointer_cast<CLASS>(shared_from_this()); \
	} \
	const TYPE& Get##NAME() const { return m_##NAME; } \
private: \
	TYPE m_##NAME;
}
#endif  // __BTFWD_H__
