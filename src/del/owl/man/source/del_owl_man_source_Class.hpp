/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Class.hpp                             */
/* Description:     manchester OWL class source                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_CLASS_HPP_
#define DEL_OWL_MAN_SOURCE_CLASS_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Class :
	public Writable,
	public Scalar<Class> {
public :
	Class (const Location&, const String&);
	Class (const Symbol&);
	virtual ~ Class();

	void addToTheory (del :: Theory*) const;

	value :: Variable getName() const;
	void addAnnotations (const Annotations*);
	void addSubclass (const Subclass*);
	void addEquivalence (const Equivalence*);

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class Subclass;
	friend class Equivalence;

	const Location location_;
	const value :: Variable name_;

	vector :: Annotations annotationsVector_;
	vector :: Subclass subclassVector_;
	vector :: Equivalence equivalenceVector_;
	enum {
		INITIAL_ANNOTATIONS_VECTOR_CAPACITY = 4,
		INITIAL_SUBCLASS_VECTOR_CAPACITY = 4,
		INITIAL_EQUIVALENCE_VECTOR_CAPACITY = 4
	};

	static const Writable* lastItem_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_CLASS_HPP_*/
