/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_run_Boxed.cpp                                 */
/* Description:     main prover class using boxed memory                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_RUN_BOXED_CPP_
#define MDL_PROVER_RUN_BOXED_CPP_

namespace mdl {
namespace prover {
namespace run {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Boxed :: Boxed (Format& format, Format& subFormat, mdl :: proof :: Question* question) :
	format_ (format),
	subFormat_ (subFormat),
	question_ (question),
	tree_ (NULL),
	data_ (NULL) {
	}
	Boxed :: ~ Boxed()
	{
		deleteAggregateObject (tree_);
		deleteAggregateObject (data_);
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			deleteAggregateObject (question_);
 		}
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	// prover :: Run implementation
	bool
	Boxed :: prove (const Time timeLimit)
	{
		// prepare the battlefield
		Memory :: boxed().setFast (Config :: fastBoxedMemory());
 		Memory :: boxed().clear (Config :: clearBoxedMemory());
 		Memory :: pile().memorizeState();
 		Expression_ :: clearCounter();
 		bool isProved = false;
 		assert (tree_ == NULL);
 		tree_ = new Tree_ (format_, subFormat_, question_);
 		tree_->init();
 		isProved = tree_->prove (timeLimit);
 		data_ = tree_->getData();
 		tree_->confirm();
 		if (Config :: deleteBoxedTree()) {
 			tree_->commitSuicide();
 		}
		tree_ = NULL;
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
 			deleteAggregateObject (question_);
 		}
		#ifdef DEBUG_PROVER_RUN_BOXED_MEMORY
		volume_.verify();
 		#endif
		#ifdef DEBUG_RUN_BOXED_MEMORY_LEAKS
		Memory :: boxed().map().show (std :: cout, true);
 		#endif

		// bury all the dead heroes ...
		Memory :: boxed().clear();
		Memory :: pile().recallState();
		return isProved;
	}
	void
	Boxed :: start (String& message)
	{
		// prepare the battlefield
		Memory :: boxed().setFast (Config :: fastBoxedMemory());
		Memory :: boxed().clear (Config :: clearBoxedMemory());
 		Memory :: pile().memorizeState();
 		Expression_ :: clearCounter();
 		assert (tree_ == NULL);
 		tree_ = new Tree_ (format_, subFormat_, question_);
 		tree_->init();
 		tree_->start (message);
	}
	void
	Boxed :: grow()
	{
		assert (tree_ != NULL);
		tree_->grow();
	}
	void
	Boxed :: stop()
	{
		assert (tree_ != NULL);
		data_ = tree_->getData();
 		tree_->stop();
 		if (Config :: deleteBoxedTree()) {
 			tree_->commitSuicide();
 		}
 		tree_ = NULL;
 		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
 			deleteAggregateObject (question_);
 		}
 		// bury all the dead heroes ...
 		Memory :: boxed().clear();
		Memory :: pile().recallState();
	}
	void
	Boxed :: info (String& string)
	{
		assert (tree_ != NULL);
		tree_->info (string);
	}
	void
	Boxed :: confirm()
	{
		assert (tree_ != NULL);
		tree_->confirm();
	}
	bool
	Boxed :: isProved()
	{
		assert (tree_ != NULL);
		return tree_->isProved();
	}
	void
	Boxed :: showVolume (String& string) const
	{
		assert (tree_ != NULL);
		tree_->showVolume (string);
	}
	void
	Boxed :: showTiming (String& string) const
	{
		assert (tree_ != NULL);
		tree_->showTiming (string);
	}
	Data*
	Boxed :: getData() const
	{
		if (data_ == NULL) {
			data_ = tree_->getData();
		}
		if (data_ != NULL) {
			return new Data (*data_);
		} else {
			return new Data();
		}
	}

using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Boxed :: commitSuicide() {
		delete this;
	}
	Size_t
	Boxed :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (tree_);
		volume += getAggregateVolume (data_);
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			volume += getAggregateVolume (question_);
 		}
		return volume;
	}
	Size_t
	Boxed :: getSizeOf() const {
		return sizeof (Boxed);
	}
	void
	Boxed :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_PROVER_RUN_BOXED_CPP_*/
