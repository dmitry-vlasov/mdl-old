/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Dot.hpp                                   */
/* Description:     a dot: an index of a point, ordered by a FRiS function   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace lexp {

class Dot :
	public object :: Object,
	public Scalar<Dot> {
public :
	Dot();
	Dot
	(
		const value :: Integer index,
		const value :: Real fris
	);
	Dot (const Dot&);
	virtual ~ Dot();

	const vector :: Integer* getIndexes() const;
	value :: Real getFRiS() const;
	void addIndex (const value :: Integer);
	void setFRiS (const value :: Real);

	void operator = (const Dot&);
	bool operator == (const Dot&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_INDEXES_CAPACITY = 4
	};
	vector :: Integer* indexes_;
	value :: Real fris_;
};

	bool
	operator < (const Dot&, const Dot&);
	bool
	operator <= (const Dot&, const Dot&);
	bool
	operator > (const Dot&, const Dot&);
	bool
	operator >= (const Dot&, const Dot&);
}
}
}


