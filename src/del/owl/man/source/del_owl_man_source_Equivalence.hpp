/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Equivalence.hpp                       */
/* Description:     manchester OWL equivalence class source                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_EQUIVALENCE_HPP_
#define DEL_OWL_MAN_SOURCE_EQUIVALENCE_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Equivalence :
	public Writable,
	public Scalar<Equivalence> {
public :
	Equivalence (const Location&, const Class*);
	Equivalence (const Class*);
	virtual ~ Equivalence();

	void addToTheory (del :: Theory*) const;
	void addTerm (const del :: Term*);

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const Class* class_;
	del :: vector :: Term terms_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_EQUIVALENCE_HPP_*/
