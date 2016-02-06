/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Iterator.hpp            */
/* Description:     symbol array iterator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Iterator :
	public Object,
	public Scalar<Iterator> {
public :
	Iterator (vector :: Symbol&, const del :: Signature*);
	Iterator (const Iterator&);
	virtual ~ Iterator();

	bool isTrivial() const;
	const Symbol& getSymbol (const value :: Integer) const;
	bool operator ++();

	// object :: Object interface
	virtual void commitSuicide();
	virtual void show (String&) const;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	bool increment (const value :: Integer = 0);
	void realizeSigns();

	value :: Integer dimension_;
	vector :: Symbol symbolArray_;
	const del :: Signature* delta_;

	vector :: value :: Integer inDelta_;
	vector :: Bool signs_;
};

}
}
}
}
}


