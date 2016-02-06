/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Simple.hpp              */
/* Description:     simple formula of a ⊑ b type                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/formula/subset/normal/del_source_formula_subset_normal_Normal.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Simple :
	public Normal,
	public Scalar<Simple> {
public :
	Simple
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* image = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Simple (const del :: Formula*);
	Simple (const Simple&);
	virtual ~ Simple();

	// del :: Formula interface
	virtual bool isTrue (const del :: Model*) const;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const;
	virtual bool isConnected (const del :: Symbol&) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool);
	virtual bool apply (del :: Model*) const;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const;
	virtual Kind getKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const;

	// object :: Writable interface
	//virtual void replicate (String&) const;
	//virtual void translate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	bool split (del :: Theory*, const del :: Signature*);
	void insertInterpolant (del :: Theory*, const del :: Term*) const;
};

}
}
}
}
}


