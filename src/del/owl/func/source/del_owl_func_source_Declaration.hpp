/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Declaration.hpp                      */
/* Description:     functional OWL2 declaration source                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_DECLARATION_HPP_
#define DEL_OWL_FUNC_SOURCE_DECLARATION_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class Declaration :
	public Writable,
	public Scalar<Declaration> {
public :
	enum Kind {
		CLASS,
		OBJECT_PROPERTY,
		ANNOTATION_PROPERTY
	};

	Declaration
	(
		const Kind,
		const String&
	);
	Declaration
	(
		const Location&,
		const Kind,
		const String&
	);
	virtual ~ Declaration();

	Kind getKind() const;
	const String& getName() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const Kind   kind_;
	const String name_;
};

}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_DECLARATION_HPP_*/
