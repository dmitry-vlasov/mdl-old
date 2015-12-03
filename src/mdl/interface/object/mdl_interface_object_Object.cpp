/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Object.cpp                          */
/* Description:     objects                                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_OBJECT_CPP_
#define MDL_INTERFACE_OBJECT_OBJECT_CPP_

#include "mdl/interface/object/mdl_interface_object_Object.hpp"

namespace mdl {
namespace interface {
namespace object {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: mode;

	void
	Object :: dump() const
	{
		std :: cout << std :: endl;
		//show (std :: cout);
		//std :: cout << std :: endl;
		String string (INITAIL_STRING_CAPACITY);
		Mode oldMode (string);
		Mode newMode;
		string << mode << newMode;
		show (string);
		string << mode << oldMode;
		std :: cout << string << std :: flush;
	}
	void
	Object :: release()
	{
		nstd :: Object :: release();
		#ifndef USE_STANDARD_HEAP
		if (string_ != NULL) {
			delete string_;
			string_ = NULL;
		}
		#endif
	}
	Size_t
	Object :: getStringVolume()
	{
		Size_t volume = 0;
		#ifndef USE_STANDARD_HEAP
		volume += getAggregateVolume (string_);
		#endif
		volume += nstd :: Object :: getStringVolume();
		return volume;
	}

#ifndef USE_STANDARD_HEAP
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
	void
	Object :: show (std :: ostream& os) const
	{
		if (string_ == NULL) {
			string_ = new String (INITAIL_STRING_CAPACITY);
		} else {
			string_->clear();
		}
		show (*string_);
		os << *string_ << std :: flush;
	}
#endif

	/****************************
	 *		Operators
	 ****************************/

#ifndef USE_STANDARD_HEAP
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
		return os << std :: flush;
	}
#else
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
		os << *(Object :: string_) << std :: flush;
		return os;
	}
#endif

	/*************************************
	 *		Private static attributes
	 *************************************/

#ifndef USE_STANDARD_HEAP
	String* Object :: string_ = NULL;
#endif
}
}
}

#endif /*MDL_INTERFACE_OBJECT_OBJECT_CPP_*/
