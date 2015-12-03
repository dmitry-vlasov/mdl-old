/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Class.cpp                             */
/* Description:     manchester OWL class source                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_CLASS_CPP_
#define DEL_OWL_MAN_SOURCE_CLASS_CPP_

#include "del/owl/man/source/del_owl_man_source.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Class :: Class (const Location& location, const String& nameString) :
	location_ (location),
	name_ (Table :: variables()->add (nameString)),
	annotationsVector_ (INITIAL_ANNOTATIONS_VECTOR_CAPACITY),
	subclassVector_ (INITIAL_SUBCLASS_VECTOR_CAPACITY),
	equivalenceVector_ (INITIAL_EQUIVALENCE_VECTOR_CAPACITY) {
	}
	inline
	Class :: Class (const Symbol& concept) :
	location_ (),
	name_ (concept.getVariable()),
	annotationsVector_ (INITIAL_ANNOTATIONS_VECTOR_CAPACITY),
	subclassVector_ (INITIAL_SUBCLASS_VECTOR_CAPACITY),
	equivalenceVector_ (INITIAL_EQUIVALENCE_VECTOR_CAPACITY) {
	}
	Class :: ~ Class() {
	}

	void
	Class :: addToTheory (del :: Theory* theory) const
	{
		for (value :: Integer i = 0; i < subclassVector_.getSize(); ++ i) {
			const Subclass* const
				subclass = subclassVector_.getValue (i);
			subclass->addToTheory (theory);
		}
		for (value :: Integer i = 0; i < equivalenceVector_.getSize(); ++ i) {
			const Equivalence* const
				equivalence = equivalenceVector_.getValue (i);
			equivalence->addToTheory (theory);
		}
	}

	value :: Variable
	Class :: getName() const {
		return name_;
	}
	void
	Class :: addAnnotations (const Annotations* annotations) {
		annotationsVector_.add (annotations);
	}
	void
	Class :: addSubclass (const Subclass* subclass) {
		subclassVector_.add (subclass);
	}
	void
	Class :: addEquivalence (const Equivalence* equivalence) {
		equivalenceVector_.add (equivalence);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Class :: translate (String& string) const
	{
		if (Config :: commentStuff()) {
			for (value :: Integer i = 0; i < annotationsVector_.getSize(); ++ i) {
				const Annotations* const
					annotations = annotationsVector_.getValue (i);
				annotations->translate (string);
			}
		}
		for (value :: Integer i = 0; i < subclassVector_.getSize(); ++ i) {
			const Subclass* const
				subclass = subclassVector_.getValue (i);
			subclass->translate (string);
		}
		for (value :: Integer i = 0; i < equivalenceVector_.getSize(); ++ i) {
			const Equivalence* const
				equivalence = equivalenceVector_.getValue (i);
			equivalence->translate (string);
		}
	}
	void
	Class :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: class_ << space;
		string << Table :: variables()->get (name_) << endLine;
		for (value :: Integer i = 0; i < annotationsVector_.getSize(); ++ i) {
			const Annotations* const
				annotations = annotationsVector_.getValue (i);
			string << *annotations;
		}
		for (value :: Integer i = 0; i < subclassVector_.getSize(); ++ i) {
			const Subclass* const
				subclass = subclassVector_.getValue (i);
			string << *subclass;
		}
		for (value :: Integer i = 0; i < equivalenceVector_.getSize(); ++ i) {
			const Equivalence* const
				equivalence = equivalenceVector_.getValue (i);
			string << *equivalence;
		}
		string << endLine;
	}

	// object :: Object implementation
	void
	Class :: commitSuicide() {
		delete this;
	}
	Size_t
	Class :: getVolume() const
	{
		Size_t volume = 0;
		volume += annotationsVector_.getVolume();
		volume += subclassVector_.getVolume();
		volume += equivalenceVector_.getVolume();
		return volume;
	}
	Size_t
	Class :: getSizeOf() const {
		return sizeof (Class);
	}

	/****************************
	 *		Private static
	 ****************************/

	const Writable* Class :: lastItem_ = NULL;
}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_CLASS_CPP_*/
