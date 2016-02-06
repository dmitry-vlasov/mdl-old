/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Bush.hpp                                  */
/* Description:     bush expression set class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/expression/node/mdl_expression_node.hpp"

namespace mdl {
namespace expression {

template
<
	class V,	// Value
	template<class> class H = storage :: ByPointer,
	template<class, template<class> class, class> class S = node :: container :: Singleton,
	class A = allocator :: Heap
>
class Bush :
	public Branching<Bush<V, H, S, A>, node :: valued :: Bush<V, H, S, A>, V, A>,
	public Scalar<Bush<V, H, S, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef
		Branching
		<
			Bush,
			typename node :: valued :: Bush<V, H, S, A>,
			V, A
		>
		Ancestor_;
	typedef
		typename Ancestor_ :: Node_ Node_;
	typedef
		typename Node_ :: Term_
		Term_;
	typedef
		typename Term_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Term_ :: Iterator_
		Iterator_;

	Bush();
	virtual ~ Bush();

	template<class E>
	Iterator_ addBranch
	(
		const E* const,
		const Value_,
		const bool
	);

	void copyNode (Iterator_&, const Iterator_&) const;
	template<class I>
	void copyNode (Iterator_&, const I&) const;
	template<class I>
	bool findNode (Iterator_&, const I&) const;
	template<class I>
	void addFindNode (Iterator_&, const I&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
private :
	bool isAccessible_;
};

namespace type {
template
<
	class V,
	template<class> class H,
	template<class, template<class> class, class> class S,
	class A
>
class Map<node :: valued :: Bush<V, H, S, A> > {
public :
	typedef Bush<V, H, S, A> Expression_;
};

}

}
}


