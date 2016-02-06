/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Volume.cpp                                 */
/* Description:     volume counters                                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/smm_Smm.hpp"

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Volume :: Volume (const Smm* const smm) :
	parser_ (0),
	source_ (0),
	sizeof_ (0),
	math_ (0),
	table_ (0),
	stack_ (0),

	used_ (0),
	allocated_ (0),
	delta_ (0),

	calculated_ (false),
	smm_ (smm) {
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
		parser_ = getAggregateVolume (smm_->parser_);
		source_ = getAggregateVolume (smm_->source_);
		if (smm_ != NULL) {
			sizeof_ = smm_->getSizeOf();
		}

		math_ = Math :: getVolume();
		table_ = Table :: getVolume();
		stack_ = 0;
		stack_ += getAggregateVolume (source :: Proof :: stack_);
		stack_ += getAggregateVolume (source :: Proof :: substitution_);

		used_ =
			Memory :: getUsedVolume() +
			getAggregateVolume (smm_) +
			Config :: getVolume() +
			object :: Object :: getStringVolume() +
			math_ + table_ + stack_;

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
		string << memory :: UsageMessage (used_, math_, "math volume") << endLine;
		string << memory :: UsageMessage (used_, table_, "table volume") << endLine;
		string << memory :: UsageMessage (used_, stack_, "stack volume") << endLine;
		string << memory :: UsageMessage (used_, parser_, "parser volume") << endLine;
		string << memory :: UsageMessage (used_, source_, "source volume") << endLine;
		string << memory :: UsageMessage (used_, sizeof_, "sizeof volume") << endLine;
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


