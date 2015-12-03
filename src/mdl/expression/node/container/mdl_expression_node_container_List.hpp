/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_List.hpp                   */
/* Description:     list container for values                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_CONTAINER_LIST_HPP_
#define MDL_EXPRESSION_NODE_CONTAINER_LIST_HPP_

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace container {

template<class V, template<class> class H, class A>
class List : public Scalar<List<V, H, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef
		typename list :: List<Value_, H, Allocator_>
		List_;
	typedef
		List_ Container_;
	typedef
		typename List_ :: Node_
		Node_;

	List();
	List (Value_);
	~ List();

	const Node_* getFirst() const;
	const Node_* getLast() const;

	void addValue (Value_);
	Value_ getValue() const;

	Container_& container();
	const Container_& getContainer() const;

	void copy (const List&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	List_ list_;
};

	template<class V, template<class> class H, class A>
	String&
	operator << (String&, const List<V, H, A>&);
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_CONTAINER_LIST_HPP_*/
