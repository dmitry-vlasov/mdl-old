/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Tree.hpp                                  */
/* Description:     expression tree (set of expressions)                     */
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
#include "mdl/expression/mdl_expression_Branching.hpp"

namespace mdl {
namespace expression {

template
<
	class V,	// Value
	template<class> class H = storage :: ByPointer,
	template<class, template<class> class, class> class S = node :: container :: Singleton,
	class A = allocator :: Heap
>
class Tree :
	public Branching<Tree<V, H, S, A>, node :: valued :: Tree<V, H, S, A>, V, A>,
	public Scalar<Tree<V, H, S, A>, A> {
public :
	typedef A Allocator_;
	typedef
		Branching<Tree<V, H, S, A>, node :: valued :: Tree<V, H, S, A>, V, A>
		Ancestor_;

	Tree();
	~ Tree();

	template<class I>
	void copyNode (typename Ancestor_ :: Iterator_&, const I&) const;
	template<class I>
	bool findNode (typename Ancestor_ :: Iterator_&, const I&) const;
	template<class I>
	void addFindNode (typename Ancestor_ :: Iterator_&, const I&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
};

namespace type {
template
<
	class V,
	template<class> class H,
	template<class, template<class> class, class> class S,
	class A
>
class Map<node :: valued :: Tree<V, H, S, A> > {
public :
	typedef Tree<V, H, S, A> Expression_;
};

}

}
}


