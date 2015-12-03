/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Volume.cpp                                 */
/* Description:     class for program data volume counters                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_VOLUME_CPP_
#define DEL_AUXILIARY_VOLUME_CPP_

#include "del/del_Del.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	Volume :: Volume (const Del* const del) :
	parser_ (0),
	source_ (0),
	target_ (0),
	sizeof_ (0),
	names_ (0),
	math_ (0),

	model_ (0),
	variables_ (0),
	conceptMap_ (0),
	relationMap_ (0),
	statistics_ (0),

	used_ (0),
	allocated_ (0),
	delta_ (0),

	calculated_ (false),
	del_ (del) {
	}
	Volume :: ~ Volume() {
	}

	void
	Volume :: countModel (Model* model)
	{
		model_ =
			model_< model->getVolume() ?
			model->getVolume() :
			model_;
		/*variables_ =
			variables_< model->getVariablesVolume() ?
			model->getVariablesVolume() :
			variables_;*/
		conceptMap_ =
			conceptMap_< model->predicates().getVolume() ?
			model->predicates().getVolume() :
			conceptMap_;
		relationMap_ =
			relationMap_ < model->relations().getVolume() ?
			model->relations().getVolume() :
			relationMap_;
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
		if (Config :: showMemoryBalance() || (delta_ != 0)) {
			showBalance (string);
		}
		if (Config :: showMemory()) {
			Memory :: show (cout);
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
		parser_ = getAggregateVolume (del_->parser_);
		source_ = getAggregateVolume (del_->source_);
		if (del_ != NULL) {
			sizeof_ = del_->getSizeOf();
		}

		names_ = Table :: getVolume();;
		math_ = Math :: getVolume();

		used_ =
			Memory :: getUsedVolume() +
			getAggregateVolume (del_) +
			Config :: getVolume() +
			Object :: getStringVolume();
			names_ +
			math_ +
			//model_ + variables_ + conceptMap_ + relationMap_ +
			statistics_;
		allocated_ = Memory :: getAllocatedVolume();
		delta_ =
			static_cast<Ptrdiff_t> (allocated_) -
			static_cast<Ptrdiff_t> (used_);
		calculated_ = true;
	}
	inline void
	Volume :: showVolume (String& string) const
	{
		string << "memory usage summary: " << endLine;
		string << "-------------------------" << endLine;
		string << memory :: UsageMessage (used_, used_, "total volume") << endLine;
		string << memory :: UsageMessage (used_, math_, "math volume") << endLine;
		string << memory :: UsageMessage (used_, names_, "names volume") << endLine;
		string << memory :: UsageMessage (used_, parser_, "parser volume") << endLine;
		string << memory :: UsageMessage (used_, source_, "source volume") << endLine;
		string << endLine;
		if (model_ > 0) {
			string << "max model:" << tab; memory :: Unit :: show (string, model_); string << endLine;
			string << "-----------" << endLine;
			string << "concept map:" << tab; memory :: Unit :: show (string, conceptMap_); string << endLine;
			string << "relation map:" << tab; memory :: Unit :: show (string, relationMap_); string << endLine;
			string << "variables:" << tab; memory :: Unit :: show (string, variables_); string << endLine;
			string << endLine;
		}
	}
	inline void
	Volume :: showBalance (String& string) const
	{
		string << "memory balance (must be 0):" << endLine;
		string << "-------------------------------" << endLine;
		string << "delta:" << tab << delta_ << " = ";
		string << allocated_ << " (allocated) - " << used_ << " (used) " << endLine;
		string << endLine;
	}
}
}

#endif /*DEL_AUXILIARY_VOLUME_CPP_*/
