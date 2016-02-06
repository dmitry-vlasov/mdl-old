/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Container.ipp                                   */
/* Description:     global container                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class R>
	inline
	Container<T, R> :: Container (const Index_ initialCapacity) :
	formVector_ (initialCapacity) {
	}
	template<class T, class R>
	Container<T, R> :: ~ Container () {
	}

	template<class T, class R>
	Size_t
	Container<T, R> :: getContentVolume() const
	{
		Size_t result = 0;
		for (Index_ i = 0; i < formVector_.getSize(); i++) {
			const Form_* form = formVector_.getValue (i);
			result += getAggregateVolume (form);
		}
		return result;
	}
	template<class T, class R>
	inline typename Container<T, R> :: Index_
	Container<T, R> :: getSize() const {
		return formVector_.getSize();
	}
	template<class T, class R>
	inline typename Container<T, R> :: Form_*
	Container<T, R> :: getForm (R index) {
		return formVector_.getValue (index);
	}
	template<class T, class R>
	inline typename Container<T, R> :: Index_
	Container<T, R> :: addForm (Form_* form)
	{
		formVector_.add (form);
		return formVector_.getSize() - 1;
	}

using manipulator :: endLine;

	// object :: Object implementation
	template<class T, class R>
	void
	Container<T, R> :: commitSuicide() {
		delete this;
	}
	template<class T, class R>
	Size_t
	Container<T, R> :: getVolume () const {
		return formVector_.getVolume();
	}
	template<class T, class R>
	Size_t
	Container<T, R> :: getSizeOf () const {
		return sizeof (Container);
	}
	template<class T, class R>
	void
	Container<T, R> :: show (String& string) const {
		string << formVector_.getSize() << endLine;
	}

	/****************************
	 *		Protected members
	 ****************************/
}
}


