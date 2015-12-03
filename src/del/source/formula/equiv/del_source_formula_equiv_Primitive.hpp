/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Primitive.hpp                  */
/* Description:     definition formula class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_HPP_
#define DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_HPP_

#include "del/source/formula/equiv/del_source_formula_equiv_Equivalence.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

class Primitive :
	public Equivalence,
	public Scalar<Primitive> {
public :
	Primitive
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Primitive (const Primitive&);
	virtual ~ Primitive();

	// del :: Formula interface
	virtual bool isTrue (const del :: Model*) const;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const;
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

#endif /*DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_HPP_*/
