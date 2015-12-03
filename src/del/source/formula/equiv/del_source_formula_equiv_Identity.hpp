/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Identity.hpp                    */
/* Description:     identity formula class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_IDENTITY_HPP_
#define DEL_SOURCE_FORMULA_EQUIV_IDENTITY_HPP_

#include "del/source/formula/equiv/del_source_formula_equiv_Equivalence.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

class Identity :
	public Equivalence,
	public Scalar<Identity> {
public :
	Identity
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Identity (const Identity&);
	virtual ~ Identity();

	static del :: Formula* create
	(
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);

	// del :: Formula interface
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool);
	virtual bool isNormal() const;
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

#endif /*DEL_SOURCE_FORMULA_EQUIV_IDENTITY_HPP_*/
