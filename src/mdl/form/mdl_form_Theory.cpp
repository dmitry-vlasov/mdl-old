/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Theory.cpp                                      */
/* Description:     theory class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_THEORY_CPP_
#define MDL_FORM_THEORY_CPP_

#include "smm/lexer/smm_lexer_Token.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theory :: Theory () :
	form :: Identifiable (),
	path_ (new form :: Identificator()),
	formMap_ (INITIAL_FORM_MAP_CAPACITY),
	components_ (INITIAL_COMPONENTS_CAPACITY) {
	}
	inline
	Theory :: Theory
	(
		const Location& location,
		const mdl :: Comments* comments,
		const value :: Name name,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	path_ (NULL),
	formMap_ (INITIAL_FORM_MAP_CAPACITY),
	components_ (INITIAL_COMPONENTS_CAPACITY)
	{
		try {
			theory_->checkUnused (name_);
			const index :: Theory
				thisIndex = Math :: theories()->add (this);
			theory_->addName (thisIndex, name_);
			theory_->addComponent (this);

			mdl :: Identificator*
				theoryPath = theory_->getPath();
			path_ = new form :: Identificator (theoryPath);
			mdl :: Identificator* path = path_;
			while (path->getNext() != NULL) {
				path = path->getNext();
			}
			path->setNext (new form :: Identificator (name_));
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	Theory :: ~ Theory() {
		deleteAggregateObject (path_);
	}

using nstd :: manipulator :: endLine;
using nstd :: manipulator :: iterate;
using nstd :: manipulator :: tab;

	// mdl :: Theory implementation
	void
	Theory :: checkUnused (const value :: Name name) const
	{
		if (formMap_.find (name) != index :: undefined :: FORM) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "name " << Table :: names()->get (name) << " is already used." << endLine;
			throw error;
		}
		if (theory_ != NULL) {
			theory_->checkUnused (name);
		}
	}
	index :: Form
	Theory :: checkUsed (const mdl :: Identificator* identificator) const
	{
		const index :: Form
			index = getIndexUp (identificator);
		if (index == index :: undefined :: FORM) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "unknown identificator " << *identificator << endLine;
			throw error;
		}
		return index;
	}
	void
	Theory :: addComponent (object :: Verifiable* component) {
		components_.add (component);
	}
	void
	Theory :: addName (const index :: Form index, const value :: Name name) {
		formMap_.add (name, index);
	}
	index :: Form
	Theory :: getIndex (const mdl :: Identificator* identificator) const {
		return getIndexUp (identificator);
	}
	mdl :: Identificator*
	Theory :: getPath() {
		return path_;
	}
	const mdl :: Identificator*
	Theory :: getPath() const {
		return path_;
	}

	// object :: Buildable implementation
	void
	Theory :: build() {
	}

using nstd :: manipulator :: space;

	// object :: Verifiable implementation
	void
	Theory :: mine (String& string) const
	{
		value :: Integer depth = Identifiable :: getDepth();
		if (Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) && !isRoot()) {
			string << iterate << depth << tab;
			string << "<theory ";
			Identifiable :: mine (string);
			string << ">" << endLine;
		}
		if (!Config :: getMiningOptions().getValue (Config :: MINE_OUTLINE)) {
			for (value :: Integer i = 0; i < components_.getSize(); ++ i){
				const object :: Verifiable*
					component = components_.getValue (i);
				component->mine (string);
			}
		}
		if (Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) && !isRoot()) {
			string << iterate << depth << tab;
			string << "</theory>" << endLine;
		}
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	Theory :: translate (String& string) const
	{
		if (theory_ != NULL) {
			if (!Config :: removeComments() && (comments_ != NULL)) {
				string << location_.getIndent();
				comments_->translate (string);
				string << endLine;
			}
			string << location_.getIndent() << :: smm :: Token :: commentBegin_ << space;
			string << Token :: theory_ << space;
			form :: Identifiable :: translateName (string);
			string << space << :: smm :: Token :: commentEnd_ << endLine << endLine;
		}
	}
	void
	Theory :: replicate (String& string) const
	{
		if (theory_ != NULL) {
			if (!Config :: removeComments() && (comments_ != NULL)) {
				string << location_.getIndent();
				comments_->replicate (string);
				string << endLine;
			}
			string << location_.getIndent() << Token :: theory_ << space;
			form :: Identifiable :: replicateName (string);
			string << Token :: semicolon_ << endLine;
			string << endLine;
		} else {
			string << "<root theory>";
		}
	}
	bool
	Theory :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Theory :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Theory :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Theory :: commitSuicide() {
		delete this;
	}
	Size_t
	Theory :: getVolume() const
	{
		Size_t volume = 0;
		volume += Identifiable :: getVolume();
		volume += formMap_.getVolume();
		volume += getAggregateVolume (path_);
		volume += components_.getVolume();
		return volume;
	}
	Size_t
	Theory :: getSizeOf() const {
		return sizeof (Theory);
	}

	/****************************
	 *		Private members
	 ****************************/

	// mdl :: Theory implementation
	index :: Form
	Theory :: getIndexUp (const mdl :: Identificator* identificator) const
	{
		const value :: Name
			name = identificator->getName();
		const index :: Form
			nameIndex = formMap_.find (name);

		if (nameIndex == index :: undefined :: FORM) {
			if (theory_ != NULL) {
				return theory_->getIndexUp (identificator);
			} else {
				return index :: undefined :: FORM;
			}
		} else {
			if (identificator->getNext() == NULL) {
				return nameIndex;
			} else {
				const mdl :: Theory*
					theory = Math :: theories()->get (nameIndex);
				if (theory != NULL) {
					return theory->getIndexDown (identificator->getNext());
				} else {
					return index :: undefined :: FORM;
				}
			}
		}
	}
	index :: Form
	Theory :: getIndexDown (const mdl :: Identificator* identificator) const
	{
		const value :: Name
			name = identificator->getName();
		const index :: Form
			nameIndex = formMap_.find (name);

		if (nameIndex == index :: undefined :: FORM) {
			return index :: undefined :: FORM;
		} else {
			if (identificator->getNext() == NULL) {
				return nameIndex;
			} else {
				const mdl :: Theory* const
					theory = Math :: theories()->get (nameIndex);
				if (theory != NULL) {
					return theory->getIndexDown (identificator->getNext());
				} else {
					return index :: undefined :: FORM;
				}
			}
		}
	}
	bool
	Theory :: isRoot() const {
		return (Identifiable :: theory_ == NULL);
	}
}
}

#endif /*MDL_FORM_THEORY_CPP_*/
