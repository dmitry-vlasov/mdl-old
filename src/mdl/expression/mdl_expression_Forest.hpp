/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Forest.hpp                                */
/* Description:     forest expression set class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_FOREST_HPP_
#define MDL_EXPRESSION_FOREST_HPP_

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
class Forest :
	public Branching<Forest<V, H, S, A>, node :: valued :: Forest<V, H, S, A>, V, A>,
	public Scalar<Forest<V, H, S, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef
		Branching
		<
			Forest,
			typename node :: valued :: Forest<V, H, S, A>,
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

	Forest();
	virtual ~ Forest();

	template<class E>
	Iterator_ addBranch
	(
		const E* const, const Value_,
		const index :: Step = index :: undefined :: STEP
	);

	index :: Step getLevel() const;
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
	index :: Step level_;
};

namespace type {
template
<
	class V,
	template<class> class H,
	template<class, template<class> class, class> class S,
	class A
>
class Map<node :: valued :: Forest<V, H, S, A> > {
public :
	typedef Forest<V, H, S, A> Expression_;
};

}

}
}

#endif /*MDL_EXPRESSION_FOREST_HPP_*/
