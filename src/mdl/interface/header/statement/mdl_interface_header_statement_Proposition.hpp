/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Proposition.hpp           */
/* Description:     abstract interface for proposition statement             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_STATEMENT_PROPOSITION_HPP_
#define MDL_INTERFACE_HEADER_STATEMENT_PROPOSITION_HPP_

#include "mdl/interface/header/statement/mdl_interface_header_statement_Statement.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Proposition : virtual public Statement {
public :
	Proposition();
	virtual ~ Proposition();

	void setSortedIndex (const index :: Assertion);
	index :: Assertion getSortedIndex() const;

	virtual const Location& getLocation() const = 0;
	virtual index :: Assertion getSourceIndex() const = 0;
	virtual index :: Assertion getTargetIndex() const = 0;

	virtual void incRate (const bool sign = true) = 0;
	// the number of places in proofs, where the given proposition was used
	virtual value :: Integer getRate (const bool sign = true) const = 0;

	virtual Experience* getExperience() = 0;
	virtual evaluation :: Function* getEvaluation (const value :: Name) = 0;
	virtual const Experience* getExperience() const = 0;
	virtual const evaluation :: Function* getEvaluation (const value :: Name) const = 0;

private :
	index :: Assertion sortedIndex_;
};

	bool operator < (const Proposition&, const Proposition&);
	bool operator <= (const Proposition&, const Proposition&);
	bool operator > (const Proposition&, const Proposition&);
	bool operator >= (const Proposition&, const Proposition&);
	bool operator == (const Proposition&, const Proposition&);

	int compareByRate (Proposition*, Proposition*);
	int compareByExpSize (Proposition*, Proposition*);
}
}
}
}

#endif /*MDL_INTERFACE_HEADER_STATEMENT_PROPOSITION_HPP_*/
