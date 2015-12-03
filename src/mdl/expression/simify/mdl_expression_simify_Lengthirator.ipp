/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Lengthirator.ipp                   */
/* Description:     length measuring iterator                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SIMIFY_LENGTHIRATOR_IPP_
#define MDL_EXPRESSION_SIMIFY_LENGTHIRATOR_IPP_

namespace mdl {
namespace expression {
namespace simify {

	/****************************
	 *		Public members
	 ****************************/

	template<class  T>
	inline
	Lengthirator<T> :: Lengthirator (const Iterator_& iterator) :
	Iterator_ (iterator),
	length_ (0) {
	}
	template<class  T>
	Lengthirator<T> :: Lengthirator (const Lengthirator& lengthirator) :
	Iterator_ (lengthirator),
	length_ (lengthirator.length_) {
	}

	template<class  T>
	inline void
	Lengthirator<T> :: operator ++ () {
		Iterator_ :: operator ++ ();
		++ length_;
	}
	template<class  T>
	inline void
	Lengthirator<T> :: operator -- () {
		Iterator_ :: operator -- ();
		-- length_;
	}
	template<class  T>
	inline void
	Lengthirator<T> :: operator += (const Term_* const term)
	{
		Iterator_ :: operator = (term->getEnd());
		length_ += term->getLength();
	}
	template<class  T>
	inline value :: Integer
	Lengthirator<T> :: getLength() const {
		return length_;
	}
}
}
}

#endif /*MDL_EXPRESSION_SIMIFY_LENGTHIRATOR_IPP_*/
