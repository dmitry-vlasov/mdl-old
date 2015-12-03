/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_valued_Bush.ipp                      */
/* Description:     value containing bush node                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_VALUED_BUSH_IPP_
#define MDL_EXPRESSION_NODE_VALUED_BUSH_IPP_

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
	Bush<V, H, S, A> :: Bush
	(
		const Bush* const node,
		const Direction direction,
		const Value_ value
	) :
	Bush_ (node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Bush<V, H, S, A> :: Bush
	(
		const Symbol& symbol,
		const Bush* const node,
		const Direction direction,
		const Value_ value
	) :
	Bush_ (symbol, node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Bush<V, H, S, A> :: ~ Bush() {
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Data_&
	Bush<V, H, S, A> :: getData() {
		return data_;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Data_&
	Bush<V, H, S, A> :: getData() const {
		return data_;
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getLeft() {
		return Bush_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getRight() {
		return Bush_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getUp() {
		return Bush_ :: getUp (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getDown() {
		return Bush_ :: getDown (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getLeft() const {
		return Bush_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getRight() const {
		return Bush_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getUp() const {
		return Bush_ :: getUp();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: getDown() const {
		return Bush_ :: getDown();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goLeft() {
		return Bush_ :: goLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goRight() {
		return Bush_ :: goRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goUp() {
		return Bush_ :: goUp (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goDown() {
		return Bush_ :: goDown (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goLeft() const {
		return Bush_ :: goLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goRight() const {
		return Bush_ :: goRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goUp() const {
		return Bush_ :: goUp();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Bush<V, H, S, A> :: Node_*
	Bush<V, H, S, A> :: goDown() const {
		return Bush_ :: goDown();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Bush<V, H, S, A> :: operator = (const Symbol& symbol) {
		Bush_ :: operator = (symbol);
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
	Bush<V, H, S, A> :: showSymbol (String& string) const {
		Bush_ :: showSymbol (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: showTerms (String& string) const {
		Bush_ :: showTerms (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: showBush (String& string) const
	{
		if (Bush_ :: right_ == NULL) {
			showBack (string);
			string << tab <<" data:" << tab;
			string << data_;
			string << endLine;
		} else {
			Bush_ :: right_->showBush (string);
		}
		if (Bush_ :: up_ != NULL) {
			Bush_ :: up_->showBush (string);
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
	Bush<V, H, S, A> :: showBack (String& string) const {
		Bush_ :: showBack (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: showKind (String& string) {
		string << "Bush (valued)" << endLine;
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
	Bush<V, H, S, A> :: commitSuicide() {
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
	Bush<V, H, S, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Bush_ :: getVolume();
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
	Bush<V, H, S, A> :: getSizeOf() const {
		return sizeof (Bush);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: show (String& string) const {
		Bush_ :: show (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: dump() const
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
	operator << (String& string, const Bush<V, H, S, A>& tree)
	{
		tree.showBush (string);
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_VALUED_BUSH_IPP_*/
