/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_valued_Forest.ipp                    */
/* Description:     value containing forest node                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_VALUED_FOREST_IPP_
#define MDL_EXPRESSION_NODE_VALUED_FOREST_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace valued {

	/****************************
	 *		Public members
	 ****************************/

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Forest<V, H, S, A> :: Forest
	(
		const Forest* const node,
		const Direction direction,
		const Value_ value
	) :
	Forest_ (node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Forest<V, H, S, A> :: Forest
	(
		const Symbol& symbol,
		const Forest* const node,
		const Direction direction,
		const Value_ value
	) :
	Forest_ (symbol, node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Forest<V, H, S, A> :: ~ Forest() {
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Data_&
	Forest<V, H, S, A> :: getData() {
		return data_;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Data_&
	Forest<V, H, S, A> :: getData() const {
		return data_;
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getLeft() {
		return Forest_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getRight() {
		return Forest_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getUp() {
		return Forest_ :: getUp();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getDown() {
		return Forest_ :: getDown();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getLeft() const {
		return Forest_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getRight() const {
		return Forest_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getUp() const {
		return Forest_ :: getUp();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: getDown() const {
		return Forest_ :: getDown();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goLeft() const {
		return Forest_ :: goLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goRight() const {
		return Forest_ :: goRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goUp() const {
		return Forest_ :: goUp();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goDown() const {
		return Forest_ :: goDown();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goLeft() {
		return Forest_ :: goLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goRight() {
		return Forest_ :: goRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goUp() {
		return Forest_ :: goUp (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Forest<V, H, S, A> :: Node_*
	Forest<V, H, S, A> :: goDown() {
		return Forest_ :: goDown (this);
	}


	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Forest<V, H, S, A> :: operator = (const Symbol& symbol) {
		Forest_ :: operator = (symbol);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: showSymbol (String& string) const {
		Forest_ :: showSymbol (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: showTerms (String& string) const {
		Forest_ :: showTerms (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: showForest (String& string) const
	{
		if (Forest_ :: right_ == NULL) {
			showBack (string);
			string << tab <<" data:" << tab;
			string << data_;
			string << tab <<" level:" << tab;
			string << Forest_ :: getLevel();
			string << endLine;
		} else {
			Forest_ :: right_->showForest (string);
		}
		if (Forest_ :: up_ != NULL) {
			Forest_ :: up_->showForest (string);
		}
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: showBack (String& string) const {
		Forest_ :: showBack (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: showKind (String& string) {
		string << "Forest (valued)" << endLine;
	}

	// object :: Object implementation
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Forest<V, H, S, A> :: commitSuicide() {
		delete this;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Forest<V, H, S, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Forest_ :: getVolume();
		volume += data_.getVolume();
		return volume;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Forest<V, H, S, A> :: getSizeOf() const {
		return sizeof (Forest);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: show (String& string) const {
		Forest_ :: show (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	String&
	operator << (String& string, const Forest<V, H, S, A>& tree)
	{
		tree.showForest (string);
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_VALUED_FOREST_IPP_*/
