/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Singleton.hpp              */
/* Description:     singleton container for values                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_CONTAINER_SINGLETON_HPP_
#define MDL_EXPRESSION_NODE_CONTAINER_SINGLETON_HPP_

namespace mdl {
namespace expression {
namespace node {
namespace container {

template<class V, template<class> class H, class A>
class Singleton : public Scalar<Singleton<V, H, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	class Node_;

	Singleton();
	Singleton (Value_);
	~ Singleton();

	const Node_* getFirst() const;
	const Node_* getLast() const;

	void addValue (Value_);
	Value_ getValue() const;

	void copy (const Singleton&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume () const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Node_* node_;
};

	template<class T, template<class> class H, class A>
	String&
	operator << (String&, const List<T, H, A>&);
}
}
}
}

#include "mdl/expression/node/container/mdl_expression_node_container_Singleton_Node.hpp"

#endif /*MDL_EXPRESSION_NODE_CONTAINER_SINGLETON_HPP_*/
