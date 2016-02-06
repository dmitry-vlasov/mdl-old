/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Disjointeds.cpp                          */
/* Description:     disjointed variables restrictions                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disjointeds :: Disjointeds () :
	disjointedVector_ (),
	hardcoded_ (false) {
	}
	inline
	Disjointeds :: Disjointeds
	(
		const vector :: parser :: Disjointed& disjointedVector,
		mdl :: Theory* theory
	) :
	disjointedVector_ (disjointedVector),
	hardcoded_ (true) {
	}
	Disjointeds :: ~ Disjointeds() {
	}

	// mdl :: Disjointeds implementation
	void
	Disjointeds :: check
	(
		const array :: Substitution* substitution,
		const mdl :: Assertion* theorem
	) const
	{
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disjointed = disjointedVector_.getValue (i);
			disjointed->check (substitution, theorem);
		}
	}
	bool
	Disjointeds :: check
	(
		const list :: Substitution* substitution,
		const mdl :: Assertion* assertion
	) const
	{
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disjointed = disjointedVector_.getValue (i);
			if (!disjointed->check (substitution, assertion)) {
				return false;
			}
		}
		return true;
	}
	bool
	Disjointeds :: check (const Symbol& x, const Symbol& y) const
	{
		if (!newPair (x.getLiteral(), y.getLiteral())) {
			return true;
		}
		if (hardcoded_) {
			if (Config :: translate()) {
				return true;
			} else {
				return false;
			}
		} else {
			if (Engine :: get()->getState() == Engine :: CHECKING) {
				mdl :: header :: Disjointed*
					disjointed = new form :: header :: Disjointed
					(
						x.getLiteral(),
						y.getLiteral(),
						NULL
					);
				const_cast<vector :: header :: Disjointed&>(disjointedVector_).add (disjointed);
			}
			return true;
		}
	}

	bool
	Disjointeds :: isMoreRestrictive (const mdl :: Disjointeds* disjointeds) const {
		return disjointeds->isLessRestrictive (this);
	}
	bool
	Disjointeds :: isLessRestrictive (const mdl :: Disjointeds* disjointeds) const
	{
		if (this == NULL) {
			return true;
		}
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disjointed = disjointedVector_.getValue (i);
			if (!isLessRestrictive (disjointed, disjointeds)) {
				return false;
			}
		}
		return true;
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Writable implementation
	void
	Disjointeds :: translate (String& string) const
	{
		if (disjointedVector_.isEmpty()) {
			return;
		}
		if (disjointedVector_.getSize() == 1) {
			const mdl :: header :: Disjointed* const
				disjointed = disjointedVector_.getValue (0);
			if (disjointed->noRestriction()) {
				return;
			}
		}
		string << tab;
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed* const
				disjointed = disjointedVector_.getValue (i);
			disjointed->translate (string);
		}
		string << endLine;
	}
	void
	Disjointeds :: replicate (String& string) const
	{
		if (!hardcoded_ && !Config :: showDisjointeds()) {
			return;
		}
		string << Token :: disjointed_ << space << Token :: openBracket_;
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disjointed = disjointedVector_.getValue (i);
			disjointed->replicate (string);
			if (i < disjointedVector_.getSize() - 1) {
				string << Token :: comma_ << space;
			}
		}
		string << Token :: closeBracket_ << space;
	}

	// object :: Object implementation
	void
	Disjointeds :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjointeds :: getVolume() const {
		return disjointedVector_.getVolume();
	}
	Size_t
	Disjointeds :: getSizeOf() const {
		return sizeof (Disjointeds);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Disjointeds :: newPair (const value :: Literal x, const value :: Literal y) const
	{
		for (index :: Arity i = 0; i < disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disjointed = disjointedVector_.getValue (i);
			if (disjointed->contains (x) && disjointed->contains (y)) {
				return false;
			}
		}
		return true;
	}
	bool
	Disjointeds :: isLessRestrictive
	(
		const mdl :: header :: Disjointed* disj_1,
		const mdl :: Disjointeds* disjointeds
	) const
	{
		if (disjointeds == NULL) {
			return false;
		}
		const Disjointeds*
			dis = dynamic_cast<const Disjointeds*>(disjointeds);
		for (index :: Arity i = 0; i < dis->disjointedVector_.getSize(); ++ i) {
			const mdl :: header :: Disjointed*
				disj_2 = dis->disjointedVector_.getValue (i);
			if (disj_1->isLessRestrictive (disj_2)) {
				return true;
			}
		}
		return false;
	}
}
}
}


