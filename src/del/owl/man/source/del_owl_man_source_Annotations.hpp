/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Annotations.hpp                       */
/* Description:     manchester OWL annotations source                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Annotations :
	public Writable,
	public Scalar<Annotations> {
public :
	Annotations (const Location&);
	virtual ~ Annotations();

	void addAnnotation (const Annotation*);

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	vector :: Annotation annotationVector_;
	enum {
		INITIAL_ANNOTATION_VECTOR_CAPACITY
	};
};

}
}
}
}


