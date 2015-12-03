/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Definition.hpp                  */
/* Description:     definition formula class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_DEFINITION_HPP_
#define DEL_SOURCE_FORMULA_EQUIV_DEFINITION_HPP_

#include "del/source/formula/equiv/del_source_formula_equiv_Equivalence.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

class Definition :
	public Equivalence,
	public Scalar<Definition> {
public :
	Definition
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL
	);
	Definition (const Definition&);
	virtual ~ Definition();

	const del :: Term* getDefiendum() const;
	const del :: Term* getDefiniens() const;

	// del :: Formula interface
	virtual bool normalize (del :: Theory*) const;
	virtual Kind getKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	virtual const char* suffix() const;
};

}
}
}
}

#endif /*DEL_SOURCE_FORMULA_EQUIV_DEFINITION_HPP_*/
