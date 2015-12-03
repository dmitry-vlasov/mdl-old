/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_object_Object.cpp                          */
/* Description:     abstract interface for general smm object                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_INTERFACE_OBJECT_OBJECT_CPP_
#define SMM_INTERFACE_OBJECT_OBJECT_CPP_

#include "smm/interface/object/smm_interface_object_Object.hpp"

namespace smm {
namespace interface {
namespace object {

	/****************************
	 *		Public members
	 ****************************/

	void
	Object :: release()
	{
		nstd :: Object :: release();
		if (string_ != NULL) {
			delete string_;
			string_ = NULL;
		}
	}
	Size_t
	Object :: getStringVolume()
	{
		Size_t volume = 0;
		volume += getAggregateVolume (string_);
		volume += nstd :: Object :: getStringVolume();
		return volume;
	}

	// nstd :: Object implementation
	void
	Object :: show (nstd :: String<>& string) const
	{
		if (string_ == NULL) {
			string_ = new String (INITAIL_STRING_CAPACITY);
		} else {
			string_->clear();
		}
		show (*string_);
		string << *string_;
	}

	/****************************
	 *		Operators
	 ****************************/

	String&
	operator << (String& string,  const Object& object)
	{
		object.show (string);
		return string;
	}
	std :: ostream&
	operator << (std :: ostream& os,  const Object& object)
	{
		if (Object :: string_ == NULL) {
			Object :: string_ = new String (Object :: INITAIL_STRING_CAPACITY);
		} else {
			Object :: string_->clear();
		}
		object.show (*(Object :: string_));
		os << *(Object :: string_);
		return os;
	}

	/***********************************
	 *		Private static attributes
	 ***********************************/

	String*
		Object :: string_ = NULL;
}
}
}

#endif /*SMM_INTERFACE_OBJECT_OBJECT_CPP_*/
