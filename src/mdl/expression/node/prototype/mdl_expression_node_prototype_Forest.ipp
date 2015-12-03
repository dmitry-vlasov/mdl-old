/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Forest.ipp                 */
/* Description:     represents a node of a forest (monotonous set of trees)  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_IPP_
#define MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline
	Forest<T, N, S, A> :: Forest
	(
		const Node_* const node,
		const Direction direction
	) :
	Tree_ (node, direction),
	level_ (index :: undefined :: STEP) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Forest<T, N, S, A> :: Forest
	(
		const Symbol& symbol,
		const index :: Step level,
		const Node_* const node,
		const Direction direction
	) :
	Tree_ (symbol, node, direction),
	level_ (level) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Forest<T, N, S, A> :: ~ Forest() {
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Forest<T, N, S, A> :: const_Iterator_
	Forest<T, N, S, A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Forest<T, N, S, A> :: Iterator_
	Forest<T, N, S, A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline index :: Step
	Forest<T, N, S, A> :: getLevel() const {
		return level_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Forest<T, N, S, A> :: setLevel (const index :: Step level) {
		level_ = level;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline bool
	Forest<T, N, S, A> :: isReacheable (const index :: Step level) const {
		return (level_ <= level);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Forest<T, N, S, A> :: operator = (const Symbol& symbol) {
		Tree_ :: operator = (symbol);
	}

using manipulator :: endLine;
using manipulator :: tab;

	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: showSymbol (String& string) const {
		Tree_ :: showSymbol (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: showTerms (String& string) const {
		Tree_ :: showTerms (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: showForest (String& string) const
	{
		if (Tree_ :: right_ == NULL) {
			showBack (string);
			string << endLine;
		} else {
			Tree_ :: right_->showForest (string);
		}
		if (Tree_ :: up_ != NULL) {
			Tree_ :: up_->showForest (string);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: showBack (String& string) const
	{
		if (Tree_ :: left_ != NULL) {
			Tree_ :: left_->showBack (string);
		} else {
			string << tab;
		}
		Tree_ :: show (string);
		string << "[" << level_ << "]  ";
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: showKind (String& string) {
		string << "Forest" << endLine;
	}

	// object :: Object implementation
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Forest<T, N, S, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Forest<T, N, S, A> :: getVolume () const {
		return Tree_ :: getVolume();
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Forest<T, N, S, A> :: getSizeOf() const {
		return sizeof (Forest);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: show (String& string) const {
		Tree_ :: show (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Forest<T, N, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_IPP_*/
