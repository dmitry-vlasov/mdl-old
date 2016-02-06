/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Volume.cpp                                  */
/* Description:     volume counters                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm_Mm.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Volume :: Volume (const Mm* const mm) :
	parser_ (0),
	source_ (0),
	target_ (0),
	sizeof_ (0),
	names_ (0),
	math_ (0),
	auxiliary_ (0),

	used_ (0),
	allocated_ (0),
	delta_ (0),

	calculated_ (false),
	mm_ (mm) {
	}
	Volume :: ~ Volume() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Volume :: commitSuicide() {
		delete this;
	}
	Size_t
	Volume :: getVolume() const {
		return 0;
	}
	Size_t
	Volume :: getSizeOf() const {
		return sizeof (Volume);
	}
	void
	Volume :: show (String& string) const
	{
		const_cast<Volume* const>(this)->calculate();

		if (Config :: showVolume()) {
			showVolume (string);
		}
		if (Config :: showMemoryBalance() || delta_ != 0) {
			showBalance (string);
		}
		if (Config :: showMemory()) {
			Memory :: show (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Volume :: calculate()
	{
		if (calculated_) {
			return;
		}
		parser_ = getAggregateVolume (mm_->parser_);
		source_ = getAggregateVolume (mm_->source_);
		target_ = getAggregateVolume (mm_->target_);
		if (mm_ != NULL) {
			sizeof_ = mm_->getSizeOf();
		}

		names_ = Table :: getVolume();;
		math_ = Math :: getVolume();
		auxiliary_ = Corrector :: getVolume();

		ast :: source :: Assertion :: staticVolumeCounted_ = false;
		ast :: source :: Proof :: staticVolumeCounted_ = false;
		ast :: target :: Block :: staticVolumeCounted_ = false;
		ast :: target :: Constant :: staticVolumeCounted_ = false;

		used_ =
			Memory :: getUsedVolume() +
			getAggregateVolume (mm_) +
			Config :: getVolume() +
			Object :: getStringVolume() +
			names_ +
			math_ +
			auxiliary_;
		allocated_ = Memory :: getAllocatedVolume();
		delta_ =
			static_cast<Ptrdiff_t> (allocated_) -
			static_cast<Ptrdiff_t> (used_);
		calculated_ = true;
	}
	void
	Volume :: showVolume (String& string) const
	{
		string << "memory usage summary: " << endLine;
		string << "-------------------------" << endLine;
		string << memory :: UsageMessage (used_, used_, "total volume") << endLine;
		if (!Config :: extractAxioms()) {
			string << memory :: UsageMessage (used_, math_, "math volume") << endLine;
			string << memory :: UsageMessage (used_, names_, "names volume") << endLine;
			string << memory :: UsageMessage (used_, parser_, "parser volume") << endLine;
			string << memory :: UsageMessage (used_, source_, "source volume") << endLine;
			string << memory :: UsageMessage (used_, target_, "target volume") << endLine;
			string << memory :: UsageMessage (used_, sizeof_, "sizeof volume") << endLine;
		}
		string << endLine;
	}
	void
	Volume :: showBalance (String& string) const
	{
		string << "Memory balance (must be 0):" << endLine;
		string << "-------------------------------" << endLine;
		string << "delta:" << tab << delta_ << " = ";
		string << allocated_ << " (allocated) - " << used_ << " (used) " << endLine;
		string << endLine;
	}
}
}


