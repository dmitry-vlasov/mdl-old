/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Identifiable.cpp                                */
/* Description:     base class for identifiable objects                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_IDENTIFIABLE_CPP_
#define MDL_FORM_IDENTIFIABLE_CPP_

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Identifiable :: Identifiable() :
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	identificator_ (NULL),
	theory_ (NULL) {
	}
	inline
	Identifiable :: Identifiable
	(
		const value :: Name name,
		mdl :: Theory* theory,
		bool unique
	) :
	location_ (Indent (1)),
	comments_ (NULL),
	name_ (name),
	identificator_ (new form :: Identificator (name)),
	theory_ (theory)
	{
		if (unique) {
			try {
				theory_->checkUnused (name_);
			} catch (Error* error) {
				error->add (location_);
				throw error;
			}
		}
	}
	inline
	Identifiable :: Identifiable
	(
		const Location& location,
		const mdl :: Comments* comments,
		const value :: Name name,
		mdl :: Theory* theory
	) :
	location_ (location),
	comments_ (comments),
	name_ (name),
	identificator_ (new form :: Identificator (name)),
	theory_ (theory) {
	}
	Identifiable :: ~ Identifiable()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (identificator_);
	}

	const mdl :: Comments*
	Identifiable :: getComments() const {
		return comments_;
	}
	value :: Integer
	Identifiable :: getDepth() const
	{
		value :: Integer depth = 0;
		const mdl :: Theory* theory = theory_;
		while (theory != NULL) {
			++ depth;
			theory = theory->getTheory();
		}
		return depth;
	}

	// object :: Identifiable implementation
	const Location&
	Identifiable :: getLocation() const {
		return location_;
	}
	value :: Name
	Identifiable :: getName() const {
		return name_;
	}

using manipulator :: space;
using manipulator :: underline;

	void
	Identifiable :: translateName (String& string, const index :: Arity) const
	{
		if (theory_ != NULL) {
			if (theory_->getTheory() != NULL) {
				theory_->getPath()->translate (string);
				string << underline;
			}
			string << Table :: names()->get (name_);
		}
	}
	void
	Identifiable :: replicateName (String& string) const
	{
		if ((theory_ != NULL) && (name_ != Table :: defaultName())) {
			string << Table :: names()->get (name_) << space;
		}
	}

	mdl :: Theory*
	Identifiable :: getTheory() {
		return theory_;
	}
	mdl :: Identificator*
	Identifiable :: getIdentificator() {
		return identificator_;
	}
	const mdl :: Theory*
	Identifiable :: getTheory() const {
		return theory_;
	}
	const mdl :: Identificator*
	Identifiable :: getIdentificator() const {
		return identificator_;
	}

	// object :: Verifiable implementation
	void
	Identifiable :: mine (String& string) const
	{
		if (name_ != value :: undefined :: NAME) {
			string << "name=\"" << Table :: names()->get (name_) << "\" ";
		}
		if ((identificator_ != NULL) &&
			(identificator_->getName() != value :: undefined :: NAME) &&
			(theory_ != NULL)) {
			string << "identifier=\"";
			string << *theory_->getPath() << "." << *identificator_ << "\" ";
		}
		location_.showAttributes (string);
	}

	// object :: Buildable implementation
	void
	Identifiable :: build()
	{
		try {
			theory_->checkUnused (name_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}

	// object :: Writable implementation
	bool
	Identifiable :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Identifiable :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Identifiable :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	Size_t
	Identifiable :: getSizeOf() const {
		return sizeof (Identifiable);
	}
	Size_t
	Identifiable :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (identificator_);
		return volume;
	}

	/****************************
	 *		Protected members
	 ****************************/
}
}

#endif /*MDL_FORM_IDENTIFIABLE_CPP_*/
