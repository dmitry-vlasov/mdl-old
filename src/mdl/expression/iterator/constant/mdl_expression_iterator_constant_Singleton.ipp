/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Singleton.ipp           */
/* Description:     singleton (0-dimensional) const iterator                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_CONSTANT_SINGLETON_IPP_
#define MDL_EXPRESSION_ITERATOR_CONSTANT_SINGLETON_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

	/****************************
	 *		Public members
	 ****************************/

	template<class N>
	inline
	Singleton<N> :: Singleton () :
	node_ (NULL) {
	}
	template<class N>
	inline
	Singleton<N> :: Singleton (const Node_* node) :
	node_ (node) {
	}
	template<class N>
	inline
	Singleton<N> :: Singleton (const typename iterator :: Singleton<N>& iterator) :
	node_ (iterator.node_) {
	}
	template<class N>
	inline
	Singleton<N> :: Singleton (const Singleton& iterator) :
	node_ (iterator.node_) {
	}

	template<class N>
	inline bool
	Singleton<N> :: operator == (const Node_* pointer) const {
		return node_ == pointer;
	}
	template<class N>
	inline bool
	Singleton<N> :: operator != (const Node_* pointer) const {
		return !(operator == (pointer));
	}

	template<class N>
	inline bool
	Singleton<N> :: operator == (const Singleton& iterator) const {
		return node_ == iterator.node_;
	}
	template<class N>
	inline bool
	Singleton<N> :: operator != (const Singleton& iterator) const {
		return !(operator == (iterator));
	}
	template<class N>
	inline bool
	Singleton<N> :: operator == (const typename iterator :: Singleton<N>& iterator) const {
		return node_ == iterator.node_;
	}
	template<class N>
	inline bool
	Singleton<N> :: operator != (const typename iterator :: Singleton<N>& iterator) const {
		return !(operator == (iterator));
	}
	template<class N>
	inline void
	Singleton<N> :: operator = (const Singleton& iterator) {
		node_ = iterator.node_;
	}

	template<class N>
	inline const N&
	Singleton<N> :: operator * () const {
		return *node_;
	}
	template<class N>
	inline const N*
	Singleton<N> :: operator ->() const {
		return node_;
	}
	template<class N>
	inline const N*
	Singleton<N> :: getNode() const {
		return node_;
	}
	template<class N>
	inline bool
	Singleton<N> :: isNull() const {
		return (NULL == node_);
	}

	template<class N>
	template<Direction dir>
	inline bool
	Singleton<N> :: isTerminal () const
	{
		if (node_ == NULL) {
			return true;
		} else {
			return node_->template isTerminal<dir>();
		}
	}
	template<class N>
	inline void
	Singleton<N> :: setNull() {
		node_ = NULL;
	}

	template<class N>
	void
	Singleton<N> :: dump() const
	{
		std :: cout << "iterator: ";
		std :: cout << "node: " << static_cast<void*>(node_) << ", ";
	}

	template<class N>
	void
	Singleton<N> :: show (String& string) const {
		string << getNode();
	}

	/*******************************
	 *		Overloaded operators
	 *******************************/

	template<class N>
	String&
	operator << (String& string, const Singleton<N>& singleton)
	{
		string << singleton->getNode();
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_CONSTANT_SINGLETON_IPP_*/
