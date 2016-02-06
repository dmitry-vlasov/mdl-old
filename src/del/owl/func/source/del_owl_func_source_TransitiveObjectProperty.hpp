/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_TransitiveObjectProperty.hpp         */
/* Description:     functional OWL2 transitive object property               */
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

class TransitiveObjectProperty :
	public Writable,
	public Scalar<TransitiveObjectProperty> {
public :
	TransitiveObjectProperty (const String&);
	TransitiveObjectProperty (const Location&, const String&);
	virtual ~ TransitiveObjectProperty();

	const String& getString() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String string_;
};

}
}
}
}


