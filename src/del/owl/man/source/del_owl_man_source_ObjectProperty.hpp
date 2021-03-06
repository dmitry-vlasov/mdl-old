/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_ObjectProperty.hpp                    */
/* Description:     manchester OWL object property source                    */
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

class ObjectProperty :
	public Writable,
	public Scalar<ObjectProperty> {
public :
	ObjectProperty
	(
		const Location&,
		const String&,
		const String&,
		const Annotations*
	);
	ObjectProperty (const Symbol&);
	virtual ~ ObjectProperty();

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String name_;
	const String characteristics_;
	const source :: Annotations* annotations_;
};

}
}
}
}


