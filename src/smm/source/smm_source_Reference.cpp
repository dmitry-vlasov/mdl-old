/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Reference.cpp                                 */
/* Description:     smm proof reference (element)                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_REFERENCE_CPP_
#define SMM_SOURCE_REFERENCE_CPP_

#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: space;

	// object :: Object implementation
	Size_t
	Reference :: getVolume() const {
		return 0;
	}
	Size_t
	Reference :: getSizeOf() const {
		return sizeof (Reference);
	}
	void
	Reference :: show (String& string) const
	{
		switch (kind_) {
		case Token :: PREFIX_F :
			string << Token :: prefix_f_;
			string << index_ << space;
			break;
		case Token :: PREFIX_E :
			string << Token :: prefix_e_;
			string << index_ << space;
			break;
		case Token :: PREFIX_I :
			string << Token :: prefix_i_;
			string << index_ << space;
			break;
		case Token :: PREFIX_A :
			string << Token :: prefix_a_;
			string << (Config :: noLabels() ? index_ : Table :: labels()->get (index_))<< space;
			break;
		case Token :: PREFIX_P :
			string << Token :: prefix_p_;
			string << (Config :: noLabels() ? index_ : Table :: labels()->get (index_))<< space;
			break;
		default :
			string << Token :: unknown_; break;
		}
	}
}
}

#endif /*SMM_SOURCE_REFERENCE_CPP_*/
