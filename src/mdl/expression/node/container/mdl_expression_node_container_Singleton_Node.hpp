/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Singleton_Node.hpp         */
/* Description:     singleton node container for values                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace node {
namespace container {

template<class V, template<class> class H, class A>
class Singleton<V, H, A> :: Node_ :
	public Scalar<typename Singleton<V, H, A> :: Node_, A> {
public :
	typedef V Value_;
	typedef H<Value_> Data_;
	Node_();
	~ Node_();

	Value_ getValue() const;
	Value_& getReference();
	const Value_& getReference() const;
	const Node_* getNext() const;

	void copy (const Node_&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Data_ data_;
};

	/*template<class V, template<class> class H, class A>
	String&
	operator << (String&, const Singleton<V, H, A> :: Node_&);*/
}
}
}
}


