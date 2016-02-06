/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_fris_Dot.cpp                                   */
/* Description:     a dot: an index of a point, ordered by a FRiS function   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace study {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Dot :: Dot () :
	indexes_ (NULL),
	fris_ (0) {
	}
	inline
	Dot :: Dot
	(
		const value :: Integer index,
		const value :: Real fris
	) :
	indexes_ (new vector :: Integer (INITIAL_INDEXES_CAPACITY)),
	fris_ (fris) {
		indexes_->add (index);
	}
	inline
	Dot :: Dot (const Dot& dot) :
	indexes_ (new vector :: Integer (*dot.indexes_)),
	fris_ (dot.fris_) {
	}
	Dot :: ~ Dot() {
		deleteAggregateObject (indexes_);
	}

	inline const vector :: Integer*
	Dot :: getIndexes() const {
		return indexes_;
	}
	inline value :: Real
	Dot :: getFRiS() const {
		return fris_;
	}
	inline void
	Dot :: addIndex (const value :: Integer index)
	{
		if (indexes_ == NULL) {
			indexes_ = new vector :: Integer (INITIAL_INDEXES_CAPACITY);
		}
		indexes_->add (index);
	}
	inline void
	Dot :: setFRiS (const value :: Real fris) {
		fris_ = fris;
	}

	inline void
	Dot :: operator = (const Dot& dot)
	{
		if (indexes_ == NULL) {
			if (dot.indexes_ != NULL) {
				indexes_ = new vector :: Integer (*dot.indexes_);
			}
		} else {
			if (dot.indexes_ == NULL) {
				delete indexes_;
				indexes_ = NULL;
			} else {
				indexes_->copy (*dot.indexes_);
			}
		}
		fris_ = dot.fris_;
	}
	inline bool
	Dot :: operator == (const Dot& dot) const {
		return fris_ == dot.fris_;
	}

using manipulator :: endLine;
using manipulator :: tab;

	// object :: Object implementation
	void
	Dot :: commitSuicide() {
		delete this;
	}
	Size_t
	Dot :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (indexes_);
		return volume;
	}
	Size_t
	Dot :: getSizeOf() const {
		return sizeof (Dot);
	}
	void
	Dot :: show (String& string) const
	{
		string << "FRiS = " << fris_ << ", ";
		string << "indexes = [";
		for (value :: Integer i = 0; i < indexes_->getSize(); ++ i) {
			string << indexes_->getValue (i);
			if (i + 1 < indexes_->getSize()) {
				string << ", ";
			}
		}
		string << "]";
	}

	/****************************
	 *		Private members
	 ****************************/

	/********************************
	 *		Overloaded operators
	 ********************************/

	inline bool
	operator < (const Dot& dot_1, const Dot& dot_2) {
		return dot_1.getFRiS() < dot_2.getFRiS();
	}
	inline bool
	operator <= (const Dot& dot_1, const Dot& dot_2) {
		return dot_1.getFRiS() <= dot_2.getFRiS();
	}
	inline bool
	operator > (const Dot& dot_1, const Dot& dot_2) {
		return dot_1.getFRiS() > dot_2.getFRiS();
	}
	inline bool
	operator >= (const Dot& dot_1, const Dot& dot_2) {
		return dot_1.getFRiS() >= dot_2.getFRiS();
	}
}
}
}


