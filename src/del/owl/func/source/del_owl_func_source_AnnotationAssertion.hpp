/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_AnnotationAssertion.hpp              */
/* Description:     functional OWL2 annotation assertion source              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class AnnotationAssertion :
	public Writable,
	public Scalar<AnnotationAssertion> {
public :
	AnnotationAssertion
	(
		const Location&,
		const String&,
		const String&,
		const String&
	);
	AnnotationAssertion (const AnnotationAssertion&);
	virtual ~ AnnotationAssertion();

	const String& getProperty() const;
	const String& getSubject() const;
	const String& getValue() const;

	bool relatesTo (const del :: Symbol&) const;
	const AnnotationAssertion* clone() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String property_;
	const String subject_;
	const String value_;
	mutable Symbol symbol_;
};

}
}
}
}


