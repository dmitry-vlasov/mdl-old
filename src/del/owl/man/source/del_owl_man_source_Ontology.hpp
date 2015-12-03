/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Ontology.hpp                          */
/* Description:     manchester OWL ontology source                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_ONTOLOGY_HPP_
#define DEL_OWL_MAN_SOURCE_ONTOLOGY_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Ontology :
	public Writable,
	public Scalar<Ontology> {
public :
	Ontology (const Location&, const String&);
	Ontology (const String&);
	virtual ~ Ontology();

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String contents_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_ONTOLOGY_HPP_*/
